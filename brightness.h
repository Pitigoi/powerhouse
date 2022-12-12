#include <stdio.h>

class Bright
{
private:
    char* value;
    int nits;
    int readFromPipe(const char* command, char* str);

public:
    char* getValue();
    int getNits();
    Bright();
    ~Bright();

};