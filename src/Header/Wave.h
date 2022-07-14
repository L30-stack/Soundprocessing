#include <iostream>
#include "struct_Header.h"

class Wav
{
    private:
        FILE *file;

    public:
        Wav(const char *fileName);
        ~Wav();
};