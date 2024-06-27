#ifndef GPP_H
#define GPP_H

typedef struct Valuef {
    int first;   
    int second;  
} Valuef;

typedef struct function {
    char id[33];
    char exp[333];   
} function;


Valuef addV(Valuef v1, Valuef v2);
Valuef subV(Valuef v1, Valuef v2);
Valuef multV(Valuef v1, Valuef v2);
Valuef divV(Valuef v1, Valuef v2);
Valuef valuefConverter(char * str);
Valuef valuef_create(int num, int denom);
Valuef tempValuefCreator(int a, int b);
#endif
