#include "util.h"
#include "init.h"
#include "global.h"
#include "tm.h"
#include "error.h"

int main(int argc,char *argv[]){
    init_machine(argc,argv);
    extern bool h_flag;
    extern char* input;
    extern char* tm;
    if(h_flag == true){
        help();
        return 0;
    }
    try{
        TM myTM(tm);
    } catch (MyException e){
        e.printme();
        return 0;
    }
    
    return 0;
}