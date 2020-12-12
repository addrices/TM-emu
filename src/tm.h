#include "util.h"
#include "global.h"
#include "error.h"
#include "delta.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#pragma once
extern bool d_flag, v_flag;

class TM{
private:
    vector<string> Q;   //state
    bool Qflag;         //if states has initial
    vector<char> S;     //input symbol table
    bool Sflag;         //if S has initial
    vector<char> G;     //tape symbol table
    bool Gflag;         //if G has initial
    string q0;          //initial state
    bool Q0flag;        //if q0 has initial
    char B;             //blank symbol
    bool Bflag;         //if blank symbol initial
    vector<string> F;   //final state
    bool Fflag;         //if final state has initial
    int TapeNum;        //TapeNum
    bool Nflag;         //if final 
    vector<delta> deltas; //transform func
    vector<vector<char>> tapes;
    int step;
    string NowState;
    vector<int> point;
    vector<int> vector_p;
    void SetQ(string line,int LineNum){
        if(Qflag == true){
            LOGF("[Line %d],State has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'Q' || line[2] != '=' || line[3] != '{' || line[line.length()-1] != '}'){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,4);
        TempStr = TempStr.erase(line.length()-1,1);
        Q = split(TempStr,",");
        Qflag = true;
        return;
    }
    void SetS(string line,int LineNum){
        if(Sflag == true){
            LOGF("[Line %d],input symbol table has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'S' || line[2] != '=' || line[3] != '{' || line[line.length()-1] != '}'){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,4);
        TempStr = TempStr.erase(line.length()-1,1);
        vector<string> S_str = split(TempStr,",");
        for(int i = 0;i < S_str.size();i++){
            S.push_back(S_str[i][0]);
        }
        Sflag = true;
        return;
    }
    void SetG(string line,int LineNum){
        if(Gflag == true){
            LOGF("[Line %d],tape symbol table has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'G' || line[2] != '=' || line[3] != '{' || line[line.length()-1] != '}'){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,4);
        TempStr = TempStr.erase(line.length()-1,1);
        vector<string> G_str = split(TempStr,",");
        for(int i = 0;i < G_str.size();i++){
            G.push_back(G_str[i][0]);
        }
        Gflag = true;
        return;
    }
    void Setq0(string line,int LineNum){
        if(Q0flag == true){
            LOGF("[Line %d],tape symbol table has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'q' || line[2] != '0' || line[3] != '='){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,4);
        q0 = TempStr;
        Q0flag = true;
        return;
    }
    void SetB(string line,int LineNum){
        if(Bflag == true){
            LOGF("[Line %d],blank symbol has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'B' || line[2] != '='){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,3);
        if(TempStr.length() != 1){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);            
        }
        B = TempStr[0];
        if(B == ' ' || B == ',' || B == ';' || B == '{' || B == '}' || B == '*'){
            LOGF("[Line %d],B symbol not support",LineNum);
            exit(0);
        }
        Bflag = true;
        return;
    }
    void SetF(string line,int LineNum){
        if(Fflag == true){
            LOGF("[Line %d],Final state has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'F' || line[2] != '=' || line[3] != '{' || line[line.length()-1] != '}'){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,4);
        TempStr = TempStr.erase(line.length()-1,1);
        F = split(TempStr,",");
        Fflag = true;
        return;
    }
    void SetN(string line,int LineNum){
        if(Nflag == true){
            LOGF("[Line %d],blank symbol has initial",LineNum);
            exit(0);
        }
        if(line[0] != '#' || line[1] != 'N' || line[2] != '='){
            LOGF("[Line %d],Syntax error",LineNum);
            exit(0);
        }
        string TempStr = line.erase(0,3);
        for(int i = 0;i < TempStr.length();i++){
            if(TempStr[i] > '9' || TempStr[i] < '0'){
                LOGF("[Line %d],only need num man",LineNum);
                exit(0);
            }
        }
        TapeNum = atoi(TempStr.c_str());
        Nflag = true;
        return;
    }
    bool load(char* tm){
        Qflag = false;
        Sflag = false;
        Gflag = false;
        Q0flag = false;
        Bflag = false;
        Fflag = false;
        TapeNum = 0;
        Nflag = false;

        ifstream in;
        in.open(tm,ios::in);
        if(!in.is_open()){
            LOGF("NO FILE %s!!!",tm);
            exit(0);
        }
        string buffer;
        int line = 0;
        while(!in.eof()){
            getline(in,buffer);
            LOGD_DEBUG("line %d %s",line,buffer.c_str());
            
            //erase blank in line head and tail
            erase_ht_blank(buffer);

            //erase comment
            erase_xlast(buffer,";");

            //empty line or comment line
            if(buffer.empty()){
                line++;
                continue;
            }

            if(buffer[0] == '#'){
                erase_blank(buffer);
                switch(buffer[1]){
                    case 'Q':SetQ(buffer,line);break;
                    case 'S':SetS(buffer,line);break;
                    case 'G':SetG(buffer,line);break;
                    case 'q':Setq0(buffer,line);break;
                    case 'B':SetB(buffer,line);break;
                    case 'F':SetF(buffer,line);break;
                    case 'N':SetN(buffer,line);break;
                    default: LOGF("[Line %d],# set error",line);
                }
            } else {
                deltas.push_back(delta(buffer,TapeNum,line));
            }
            line++;
        }
        in.close();
//initial tape
        for(int i = 0;i < TapeNum;i++){
            vector<char> a;
            tapes.push_back(a);
        }
        return true;
    }
public:
    TM(char* tm){
        LOGI_DEBUG("tm begin loading %s",tm);
        load(tm);
    };
    bool print_tape(){
        cout << "Step   : " << step << endl;
        for(int i = 0;i < TapeNum;i++){
            cout << "Index" << i << " : ";
            bool begin_empty = false;
            for(int j = 0;j < tapes[i].size();j++){
                if(begin_empty == false && tapes[i][j] != B && j < point[i]){
                    begin_empty == true;
                }
                if(begin_empty == true){
                    cout << j << " "; 
                }
            }
            cout << endl;
            begin_empty = false;
            for(int j = 0;j < tapes[i].size();j++){
                if(begin_empty == false && tapes[i][j] != B && j < point[i]){
                    begin_empty == true;
                }
                if(begin_empty == true){
                    if(j > 99)
                        cout << tapes[i][j] << "   "; 
                    else if(j > 9)
                        cout << tapes[i][j] << "  ";
                    else
                        cout << tapes[i][j] << " ";
                }
            }
            cout << endl;
            begin_empty = false;
            for(int j = 0;j < tapes[i].size();j++){
                if(begin_empty == false && tapes[i][j] != B && j < point[i]){
                    begin_empty == true;
                }
                if(begin_empty == true){
                    if(j == point[i])
                        cout << "^";
                    if(j > 99)
                        cout << "  "; 
                    else if(j > 9)
                        cout << " ";
                    else
                        cout << "";
                }
            }
            cout << endl;
        }
        cout << "---------------------------------------------" << endl;
    }
    bool run(string input){
        NowState = q0;
        step = 0;
        for(int i = 0;i < TapeNum;i++){
            point.push_back(0);
            vector_p.push_back(0);
            vector<char> tape;
            tapes.push_back(tape);
            for(int j = 0;j < input.length();j++){
                tapes[i].push_back(input[j]);
            }
        }
        //check input
        for(int i = 0;i < input.length();i++){
            if(find(S.begin(),S.end(),input[i]) != S.end()){
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: '" << input[i] <<"' was not declared in the set of input symbols" << endl;
                cerr << "input: " << input << endl;
                string a  = "       ";
                for(int j = 0;j < i;j++)
                    a += " ";
                a += "^";
                cerr << a << endl;
                exit(0);
            }
        }
        //begin runing
        while(find(F.begin(),F.end(),NowState) != F.end()){
            extern bool v_flag;
            for(int i = 0;i < deltas.size();i++){
                vector<char> NowTape;
                print_tape();
                for(int j = 0;j < TapeNum;j++)
                    NowTape.push_back(tapes[j][i]);
                if(deltas[i].isMe(NowState,NowTape)){
                    vector<char> NewSymbol = deltas[i].getNewSymbol();
                    string NewState = deltas[i].getNewState();
                    vector<char> Direct = deltas[i].getDirect(); 
                    for(int j = 0;j < TapeNum;j++){
                        tapes[j][vector_p[j]] = NewSymbol[j];
                        switch(Direct[j]){
                            case 'l': point[j] = point[j]-1; 
                                      if(vector_p[j] == 0){
                                          tapes[i].insert(tapes[i].begin(),B);
                                      }else{
                                          vector_p[j] = vector_p[j]-1;
                                      } break;
                            case 'r': point[j] = point[j]+1;
                            case '*': break;
                            default: LOGF("error direct"); break;
                        }
                    }
                    NowState = NewState;
                }
            }
        }
    }
};