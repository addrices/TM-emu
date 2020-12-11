#include <string>
#include <stdio.h>
#include <iostream>
#include "util.h"
using namespace std;
#pragma once

class MyException{
private:
    string myinfo;
public:
    MyException(string info){
        myinfo = info;
    }
    void printme(){
        LOGF("%s",myinfo.c_str());
    }
};