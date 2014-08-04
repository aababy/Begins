#include "IncludeForCpp.h"
#include "Clock.h"
#include <iostream>

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace std;

static Clock* pInstance = NULL;
MissionPool* _pool = NULL;

Clock* Clock::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new Clock();
    }
    
	return pInstance;
}

Clock::Clock()
{
	_pool = xMissionPool;
	startTiming();
}


Clock::~Clock(void)
{
}

bool Clock::checkMission()
{
	_pool->handleRemind();
	_pool->handleExpire();

	return true;
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
