#include "util.h"
#include "init.h"
#include "global.h"
#include "tm.h"
#include "error.h"
using namespace std;
int main(int argc,char *argv[]){
    init_machine(argc,argv);
    extern bool h_flag;
    extern char* input;
    extern char* tm;
    if(h_flag == true){
        help();
        return 0;
    }
    TM myTM(tm);
    string instr = input;
    myTM.run(instr);
    myTM.PrintRes();
    return 0;
}