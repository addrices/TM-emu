#pragma once
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#define LOGI(format, ...) \
    printf("\33[1;34m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LOGD(format, ...) \
    printf("\33[1;33m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LOGF(format, ...) \
    printf("\33[1;31m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LOGI_DEBUG(format,...) \
    if(d_flag == true) LOGI(format,## __VA_ARGS__)

#define LOGD_DEBUG(format,...) \
    if(d_flag == true) LOGD(format,## __VA_ARGS__)

#define LOGF_DEBUG(format,...) \
    if(d_flag == true) LOGF(format,## __VA_ARGS__)



void help(){
    printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
    printf("[-h|--help] print help infomation\n");
    printf("[-v|--verbose] \n");
    return;
}


vector<string> split(const string& str, const string& pattern)
{
    vector<string> ret;
    if(pattern.empty()) return ret;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos)
    {
        if(start!=index)
            ret.push_back(str.substr(start,index-start));
        start=index+1;
        index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        ret.push_back(str.substr(start));
    return ret;
}

void erase_blank(string& str){
    for(int i = 0;i < str.length();i++){
        if(str[i] == ' '){
            str.erase(i,1);
            i--;
        }
    }
    return;
}