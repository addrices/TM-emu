; L2 language 
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {0,cp1,cp2,cmp1,cmp2,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1,@,=}

; the complete set of tape symbols
#G = {1,@,=,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}

; the number of tapes
#N = 3

; the transition functions

; State 0: start state
0 1__ _1_ rr* cp1
0 @__ ___ r** reject
0 =__ ___ r** reject
0 ___ ___ *** reject

; cp1 cp the first 1 string to 2nd tapes
cp1 1__ _1_ rr* cp1
cp1 ___ ___ *** reject
cp1 @__ ___ rl* cp2
cp1 =__ ___ r** reject

; cp2 cp the second 2 string to 3nd tapes
cp2 11_ _11 r*r cp2
cp2 @1_ ___ r** reject
cp2 =1_ _1_ r*l cmp1
cp2 _1_ ___ l** reject

; cmp1 compare the 1's num and second head right move to left
cmp1 111 _11 rl* cmp1
cmp1 1_1 1__ *rl cmp2
cmp1 __1 ___ *rl cmp2
cmp1 1__ ___ r** reject
cmp1 ___ ___ *** accept
cmp1 _1_ ___ *** accept
cmp1 _1_ ___ *** reject
cmp1 __1 ___ *** reject
cmp1 _11 ___ *** reject
cmp1 11_ ___ r** reject
; it's error when first tape has symbols not 1
cmp1 @1_ ___ r** reject
cmp1 @_1 ___ r** reject
cmp1 @11 ___ r** reject
cmp1 @__ ___ r** reject
cmp1 =1_ ___ r** reject
cmp1 =_1 ___ r** reject
cmp1 =11 ___ r** reject
cmp1 =__ ___ r** reject

; cmp2 compare the 1's num and second head left move to right
cmp2 111 _11 rr* cmp2
cmp2 1_1 1__ *ll cmp1
cmp2 __1 ___ *ll cmp1
cmp2 1__ ___ r** reject
cmp2 ___ ___ *** accept
cmp2 _1_ ___ *** accept
cmp2 _1_ ___ *** reject
cmp2 __1 ___ *** reject
cmp2 _11 ___ *** reject
cmp2 11_ ___ r** reject
cmp2 @1_ ___ r** reject
cmp2 @_1 ___ r** reject
cmp2 @11 ___ r** reject
cmp2 @__ ___ r** reject
cmp2 =1_ ___ r** reject
cmp2 =_1 ___ r** reject
cmp2 =11 ___ r** reject
cmp2 =__ ___ r** reject

; accept state has to input true
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

; state reject : the string has been reject and move to the last char of the string 
; now it's need to clean the string
reject 1__ ___ r** reject
reject @__ ___ r** reject
reject =__ ___ r** reject

; now it's time to input false
reject  ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject