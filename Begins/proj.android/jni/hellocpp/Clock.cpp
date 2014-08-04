#include "IncludeForCpp.h"
#include "Clock.h"
#include <thread>           //C++ 11 ���澶�绾跨��
#include <iostream>

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace std;

static Clock* pInstance = NULL;
MissionPool* _pool = NULL;

Clock* Clock::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new Clock(xMissionPool);
    }
    
	return pInstance;
}

Clock::Clock(void* pool)
{
	init(pool);
}


Clock::~Clock(void)
{
}

static void* justAnotherTest(void *arg)   
{   
	int itime;
#if TEST
	itime = 5 * 1000;
#else
	itime = 5 * 1000;
#endif

	do 
	{
		//��ㄨ����������ユ�扮嚎绋�灏�瑕���ц�����浠ｇ��
        std::this_thread::sleep_for(chrono::seconds(55));

		Clock* pTime = (Clock*)arg;

		pTime->timer(1.0f);
	} while (false);

    std::this_thread::sleep_for(chrono::seconds(120));

	return NULL;   
}


bool Clock::init(void* pool)
{
	_pool = (MissionPool*)pool;

#ifdef IN_WINDOWS
	CCDirector::getInstance()->getScheduler()->scheduleSelector(schedule_selector(Clock::timer), this, 15, false);
#else
	pthread_t tid;   
	//pthread_create(&tid, NULL, &justAnotherTest, this);   
#endif

	return true;
}

void Clock::timer(float dt)
{
	CCLOG("update %f", dt);
	_pool->handleRemind();
	_pool->handleExpire();
}

void Clock::startTiming()
{
    JniMethodInfo methodInfo;
    jobject jobj;

    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
    		"org/cocos2dx/cpp/AppActivity", "getActivity", "()Ljava/lang/Object;");

    if (isHave)
    {
        jobj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        
        isHave = JniHelper::getMethodInfo(methodInfo,
        		"org/cocos2dx/cpp/AppActivity", "startTiming", "()V");

    	if(isHave)
    	{
    		methodInfo.env->CallVoidMethod(jobj, methodInfo.methodID);
    	}    	    	
    }

}
