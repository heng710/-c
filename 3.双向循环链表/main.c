#include<stdio.h>
#include "index.h"

void main(){
    node *egg=center_link();
    input_head(egg,50);
    input_head(egg,40);
    input_head(egg,30);
    input_head(egg,10);
    input_tail(egg,60);
    input_tail(egg,70);
    input_tail(egg,80);
    input_tail(egg,90);

    delect(egg,150);
    input_prinf(egg);
    
    
}