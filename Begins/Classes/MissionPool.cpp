#include "IncludeForCpp.h"
#include "MissionPool.h"

static MissionPool* pInstance = NULL;

MissionPool* MissionPool::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new MissionPool(xDatabase);
    }
    
	return pInstance;
}


MissionPool::MissionPool(void *data)
{
	_db = (Database*)data;
	_user = new User();
}


MissionPool::~MissionPool(void)
{
	clean(_vMissions);
	clean(_vReminds);

	delete _user;
}


void MissionPool::clean(vector<Mission*> &vec)
{
	for (vector<Mission*>::iterator it = vec.begin() ; it != vec.end(); ++it)
	{
		delete *it;
	}

	vec.clear();
}


void MissionPool::getMission()
{
	clean(_vMissions);
	_db->GetMissions(&_vMissions);
}


bool MissionPool::checkRemind()
{
	//1. 查询是否有任务需要提醒
	clean(_vReminds);
	_db->getReminds(&_vReminds);

	//2. 如果有, 更新提醒
	if (_vReminds.size() != 0)
	{
		//如果在前台, 提醒对话框,
		if (!CCDirector::getInstance()->isPaused())
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(REMIND_MSG, (Ref*)this);
		}

		updateRemind();
        
        return true;
	}
    else
    {
        return false;
    }
}


void MissionPool::updateRemind()
{
	for (unsigned int i = 0; i < _vReminds.size(); i++)
	{
		switch(_vReminds.at(i)->eType)
		{
		case MISSION_NORMAL:
			{
				_db->updateRemindTime(_vReminds.at(i), 0);
			}
			break;
		case MISSION_DAILY:
			{
				_db->updateRemindTime(_vReminds.at(i), 1);
			}
			break;
		default:
			break;
		}
	}
	
}


int MissionPool::getScore()
{
	_user->iScore = _db->getScore();
	return _user->iScore;
}


void MissionPool::handleExpire()
{
	//1. 查询是否有到期任务
	clean(_vExpire);
	_db->getExpire(&_vExpire);

	//2. 如果有, 执行"超时扣分"操作
	if (_vExpire.size() > 0)
	{
		for (unsigned int i = 0; i < _vExpire.size(); i++)
		{
			endMission(i, BY_EXPIRE);
		}
	}
}


void MissionPool::endMission(int idx, ACTION_BY eAction)
{
	Mission *miss;

	if (eAction == BY_MANUAL)
	{
		miss = _vMissions.at(idx);

		//1. 计算得分
		_db->updateScore(miss->_iScore);
	}
	else if (eAction == BY_EXPIRE)
	{
		miss = _vExpire.at(idx);

		//1. 计算得分
		_db->updateScore(miss->_iScore * -1);
	}

	//2. 插入end
	_db->insertMission(miss, "end");

	//3. 更新mission
	if (miss->eType == MISSION_NORMAL)
	{
		_db->deleteMission(miss->iMissionID);
	} 
	else if(miss->eType == MISSION_DAILY)
	{
		_db->updateExpireTime(miss, 1);
	}
}
