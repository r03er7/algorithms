#include "szablon.h"
/*
In gcc/g++ fread_unlocked() is even faster.
Can be made faster in non-object-oriented fashion with macros instead of functions.
In contest, who cares dynamic allocation?
*/
struct FastRead {
    char *buff, *ptr;
    FastRead(int size) {
        buff = new char[size];
        ptr = buff;
        fread(buff, 1, size, stdin);
    }
    ~FastRead() {
        delete[] buff;
    }
    int nextInt() {
        int ret = 0;
        while(*ptr < '0' || *ptr > '9') ptr++;
        do {
            ret = ret * 10 + *ptr++ - '0';
        } while(*ptr >= '0' && *ptr <= '9');
        return ret;
    }
};
/*
Usage: Just create an instance of it at the start of the block of
which you want to measure running time. Reliable up to millisecond
scale. You don't need to do anything else, even works with freopen.
*/
class TimeTracker {
    clock_t start, end;
public:
    TimeTracker() {
        start = clock();
    }
    ~TimeTracker() {
        end = clock();
        fprintf(stderr, "%.3lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
};
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
int main() {
    READ("in.txt");
    WRITE("out.txt");
    //FastRead sth(1000);
    //int a=sth.nextInt();
    {
        TimeTracker sth;
        REP(i,1000000) {
            printf("%d ",i);
        }
    }
    return 0;
}
