#include <stdio.h>
#include "webplot.h"

int main()
{
    int i=100;
    while(i--)
        plot("titre","%i %i",i,i);

    return 0;
}
