//Database 		这个类不参与逻辑处理, 只是简单的sql.

#pragma once

#include "IncludeForHeader.h"

#define xDatabase                  (Database::getInstance())

class Mission;
class Log;

////////////////////////////////////////////////////////////////////////// 查询
enum SQL_TAG
{
	SQL_None		= 0,
	SQL_GetMissions,
	SQL_GetExpire,
	SQL_GetReminds,
};


struct QUERY_P
{
	void *pData;
	void *self;
};


////////////////////////////////////////////////////////////////////////// 占位符

enum MISSION_FIELD
{
	MF_ID = 0,
	MF_TYPE,
	MF_NAME,
	MF_CTIME,
	MF_RTIME,
	MF_STIME,
	MF_SCORE,
};

//////////////////////////////////////////////////////////////////////////

class Database
{
public:
    static Database* getInstance();

	void CreateTable(void);
	void insertMission(int id, int type, const char *name, Time &timeCreate, Time &timeRemind, Time &timeScore, const char * score, char * freq);
    void insertBlob(char * freq, int id);
	void insertMission(Mission *miss, const char *szTableName = "mission");
	void GetMissions(vector<Mission*> *vec);
	void getReminds(vector<Mission*> *vec);
	void CreateUser(void);
	void setScore(int iScore);
	int getScore();
	void getExpire(vector<Mission*> *vec);
    void printError();

	Log *_obLog;

	//////////////////////////////////////////////////////////////////////////
	bool execute(const char* format, ...);
	bool query(SQL_TAG eTag, void* pData, const char* format, ...);
	static int onQuery(void *pData, int argc, char* value[], char* table_name[]);
	void updateScore(int iScore);
	void deleteMission(int id);
	void updateExpireTime(Mission *miss, int iDay);
	void updateRemindTime(Mission *miss, int iDay);
	//////////////////////////////////////////////////////////////////////////
    
private:
    Database();
	~Database(void);
	int			_rc;
	bool		_initialized;
	SQL_TAG		_eTag;
	QUERY_P		_queryP;
};

