;This is L1 language L1={a^ib^ja^ib^j|i,j>0}
;true: aaabbbaabb
#Q = {0,acp,bcp,cmp,mv,accept,accept2,accept3,accept4,halt_accept,mid_reject,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,t,r,u,e,f,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}

; the number of tapes
#N = 2

; the transition functions
; state 0: start state if empty reject
0 a_ aa rr acp
0 b_ b_ ** mid_reject
0 __ __ ** reject

; state acp and bcp: copy half string(a^ib^i) to 2nd tape
; state acp : copy (a^i) to 2nd tape
acp a_ aa rr acp
acp b_ bb rr bcp
acp __ __ l* reject

; state bcp : copy (b^i) to 2nd tape
bcp b_ bb rr bcp
bcp a_ a_ *l mv
bcp __ __ l* reject 

; state mv : mv 2nd tape to begin
mv ab ab *l mv
mv aa aa *l mv
mv a_ a_ *r cmp

; state cmp : cmp the second half of 1nd tape and 2nd tape's first half 
cmp aa aa rr cmp
cmp bb bb rr cmp
cmp ab a_ r* mid_reject
cmp ba b_ r* mid_reject
cmp a_ a_ r* mid_reject
cmp b_ b_ r* mid_reject
cmp _a __ l* reject
cmp _b __ l* reject
cmp __ __ l* accept

; state accept : now it's need to clean the string
accept a_ __ l* accept
accept b_ __ l* accept

; now it's time to input true
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; state mid_reject : the string has been reject, 
; now it's need to move to the last char of the string to clean 
mid_reject a_ a_ r* mid_reject
mid_reject b_ b_ r* mid_reject
mid_reject __ __ l* reject

; state reject : the string has been reject and move to the last char of the string 
; now it's need to clean the string
reject a_ __ l* reject
reject b_ __ l* reject

; now it's time to input false
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject

