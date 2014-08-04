#pragma once
#include "IncludeForHeader.h"


string itostr(int i);
string getString(char *sz);
Button* initUIButton(int tag, SEL_TouchEvent selector, Layout* root, Ref* target);

Time getCurrentTime();
Time str2MTime(const string &str);
Time str2MTimeForDB(const string &str);
string getShowTime(Time &mtime);