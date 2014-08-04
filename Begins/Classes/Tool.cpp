//
//  tool.cpp
//  Begins
//
//  Created by luoxp on 14-7-22.
//
//
#include "IncludeForCpp.h"
#include "Tool.h"

string itostr(int i)
{
	char buf[30];
	sprintf(buf, "%d", i);
    
	return string(buf);
}

string getString(char *sz)
{
	string str;
	if (sz != NULL)
	{
		str = string(sz);
	}
    
	return str;
}

Button* initUIButton(int tag, SEL_TouchEvent selector, Layout* root, Ref* target)
{
    Button* button = static_cast<Button*>(root->getChildByTag(tag));
    
    //CCASSERT(button != nullptr, "error");
    
    button->addTouchEventListener(target, selector);
        
    return button;
}

Time getCurrentTime()
{
	Time mtime;
    
#if 0 //(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	mtime.year = tm->tm_year + 1900;
	mtime.month = tm->tm_mon + 1;
	mtime.day = tm->tm_mday;
	mtime.hour=tm->tm_hour;
	mtime.minute=tm->tm_min;
	mtime.second=tm->tm_sec;
#else
	//struct cc_timeval now;
	//CCTime::gettimeofdayCocos2d(&now, NULL);
	//struct tm *tm;
    
	//const time_t * t = (const time_t *)now.tv_sec;
    
	//tm = localtime(t);
	//mtime.year = tm->tm_year + 1900;
	//mtime.month = tm->tm_mon + 1;
	//mtime.day = tm->tm_mday;
	//mtime.hour=tm->tm_hour;
	//mtime.minute=tm->tm_min;
	//mtime.second=tm->tm_sec;
	//long millSecond= now.tv_sec * 1000 + now.tv_usec / 1000;
    
	unsigned long long timestamp = time(NULL);
	struct tm *ptm = localtime((time_t*)&timestamp);
    
	mtime.year = ptm->tm_year + 1900;
	mtime.month = ptm->tm_mon + 1;
	mtime.day = ptm->tm_mday;
	mtime.hour = ptm->tm_hour;
	mtime.minute = ptm->tm_min;
	mtime.second = ptm->tm_sec;
	//return (now.tv_sec * 1000 + now.tv_usec / 1000);
#endif
    
	//////////////////////////////////////////////////////////////////////////
	char temp[30];
    
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d",
            mtime.year, mtime.month, mtime.day, mtime.hour, mtime.minute, mtime.second);
    
	mtime.str = string(temp);
    
	return mtime;
}

Time str2MTime(const string &str)
{
	char buf[5];
    
	Time mtime;
    
	if (str.length() < 8)
	{
		mtime.str = string("null");
		return mtime;
	}
	
	buf[0] = str[0];
	buf[1] = str[1];
	buf[2] = NULL;
	
	mtime.year = 2014;
	mtime.month = atoi(buf);
    
	buf[0] = str[2];
	buf[1] = str[3];
	mtime.day = atoi(buf);
    
	buf[0] = str[4];
	buf[1] = str[5];
	mtime.hour = atoi(buf);
    
	buf[0] = str[6];
	buf[1] = str[7];
	mtime.minute = atoi(buf);
    
	mtime.second = 0;
    
	char temp[30];
    
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d",
            mtime.year, mtime.month, mtime.day, mtime.hour, mtime.minute, mtime.second);
    
	mtime.str = string(temp);
    
	return mtime;
}

Time str2MTimeForDB(const string &str)
{
	char buf[5];
    
	Time mtime;
    
	if (str.length() < 8)
	{
		mtime.str = string("null");
		return mtime;
	}
	
	buf[0] = str[5];
	buf[1] = str[6];
	buf[2] = NULL;
	
	mtime.year = 2014;
	mtime.month = atoi(buf);
    
	buf[0] = str[8];
	buf[1] = str[9];
	mtime.day = atoi(buf);
    
	buf[0] = str[11];
	buf[1] = str[12];
	mtime.hour = atoi(buf);
    
	buf[0] = str[14];
	buf[1] = str[15];
	mtime.minute = atoi(buf);
    
	mtime.second = 0;
    
	return mtime;
}

string getShowTime(Time &mtime)
{
    char temp[30];
    
	sprintf(temp, "%02d-%02d",
            mtime.month, mtime.day);
    
	return string(temp);
}
