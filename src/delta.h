#include "util.h"
#include "global.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
using namespace std;

class delta{
private:
    string OldState;
    vector<char> OldSymbol;
    vector<char> NewSymbol;
    string NewState;
    vector<char> direct;     //l leftmove r rightmove * nomove
    int TapeNum;
public:
//input is initial line, Tape num, LineNum for local syntax error
    delta(string line,int num,int LineNum){
        TapeNum = num;
        vector<string> info = split(line," ");
//make sure info.size == 5
        if(info.size() < 5){
            LOGF("[Line %d], delta need 5 var,but only %d",LineNum,(int)info.size());
            exit(0);
        } else if (info.size() > 5){
            LOGF("[Line %d], delta only need 5 var, but has %d",LineNum,(int)info.size());
            exit(0);
        }

// read delta function's parameters
        OldState = info[0];
        for(int i = 0;i < info[1].length();i++){
            if(info[1][i] == ',' || info[1][i] == ';' || info[1][i] == '{' || info[1][i] == '}' || info[1][i] == ' ' || info[1][i] == '*' || info[1][i] == '_'){
                LOGF("[Line %d],input symbol is error",LineNum);
                exit(0);
            }
            OldSymbol.push_back(info[1][i]);
        }
        for(int i = 0;i < info[2].length();i++){
            if(info[2][i] == ',' || info[2][i] == ';' || info[2][i] == '{' || info[2][i] == '}' || info[2][i] == ' ' || info[2][i] == '*' || info[2][i] == '_'){
                LOGF("[Line %d],output symbol is error",LineNum);
                exit(0);
            }
            NewSymbol.push_back(info[2][i]);
        }
        for(int i = 0;i < info[3].length();i++){
            if(info[3][i] != '*' || info[3][i] != 'l' || info[3][i] != 'r'){
                LOGF("[Line %d],direct's not true",LineNum);
                exit(0);
            }
            direct.push_back(info[3][i]);
        }
        NewState = info[4];

//make sure OldSymbol, NewSymbol and TapeNum equal
        if(OldSymbol.size() != TapeNum){
            LOGF("[Line %d],OldSymbol's num is not equal to TapeNum",LineNum);
            exit(0);
        }
        if(NewSymbol.size() != TapeNum){
            LOGF("[Line %d],NewSymbol's num is not equal to TapeNum",LineNum);
            exit(0);
        }
        if (direct.size() != TapeNum){
            LOGF("[Line %d],direct's num is not equal to TapeNum",LineNum);
            exit(0);
        }
    }
};