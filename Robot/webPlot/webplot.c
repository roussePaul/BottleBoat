#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "webplot.h"

void plot(char* title, char* data, ...)
{
    char path[100];
    char command[1200];
    
    char formatedData[1000];

    va_list args;
    va_start(args,data);
    vsprintf(formatedData,data, args);
    va_end(args);

    sprintf(path, "dat/%s.dat",title);

    sprintf(command, "echo \"%s\" >> %s",formatedData, path);

    system(command);
}


void clearPlot(char* title)
{
    char command[100];
    sprintf(command, "rm dat/%s.dat",title);
    system(command);
}

