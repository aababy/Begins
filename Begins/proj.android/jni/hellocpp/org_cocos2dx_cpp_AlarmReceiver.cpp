#include "IncludeForCpp.h"
#include "org_cocos2dx_cpp_AlarmReceiver.h"

JNIEXPORT jboolean JNICALL Java_org_cocos2dx_cpp_AlarmReceiver_checkMission
  (JNIEnv *, jobject)
{
    unsigned char ret = 1;
    
    CCLOG("ok");
    
    return (jboolean)ret;
}