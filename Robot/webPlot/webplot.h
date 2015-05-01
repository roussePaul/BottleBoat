#ifndef H_WEBPLOT
#define H_WEBPLOT

#ifndef DISABLE_PLOT
#define PLOT(a,b, ...) plot(a,b,##__VA_ARGS__)
#define CLEARPLOT(a) clearPlot(a)
#else
#define PLOT(a,b, ...) 
#define CLEARPLOT(a)
#endif

void plot(char* title, char* data, ...);
void clearPlot(char* title);

#endif
