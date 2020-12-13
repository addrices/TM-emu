#pragma once
#include "global.h"
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
extern char* input;         //turing machine's input string 
extern char* tm;            //turing machine file
extern bool h_flag;         //if need help
extern bool v_flag;         //if need verbose
extern bool d_flag;         //if need debug


int init_machine(int argc,char *argv[]){
    input = argv[argc-1];
    tm = argv[argc-2];
    h_flag = false;
    v_flag = false;
    d_flag = false;
    int option_index = 0;

    static struct option table[] = {
        {"help",no_argument,NULL,'h'},
        {"verbose",no_argument,NULL,'v'},
        {"debug",no_argument,NULL,'d'}
    };

    int ch;
    while((ch = getopt_long(argc,argv,"hvd",table,&option_index))!= -1)
    {
        switch(ch)
        {
            case 'h': h_flag = true; break;
            case 'v': v_flag = true; break;
            case 'd': d_flag = true; break;
            default: LOGF("no config"); exit(0);
        }
    }
    return 0;
}