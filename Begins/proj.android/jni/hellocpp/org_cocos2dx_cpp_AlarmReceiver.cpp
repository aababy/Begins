#include "IncludeForCpp.h"
#include "org_cocos2dx_cpp_AlarmReceiver.h"

JNIEXPORT jboolean JNICALL Java_org_cocos2dx_cpp_AlarmReceiver_checkMission
  (JNIEnv *, jobject)
{
    unsigned char ret;
    
    //µ÷ÓÃClockµÄcheckMission
    if(xClock->checkMission())
    {
    	ret = 1;
    }
    else
    {
    	ret = 0;
    }
    
    return (jboolean)ret;
}
