#include "struckt.h"
bool riff_check(FILE*);
bool wave_check(FILE*);
bool fmt_check(FILE*);
bool data_check(FILE*);

bool mist(FILE* fp)
{
    if (fp == NULL)
        {
            printf("Failed open file, error");
            return false;
        }
    if(riff_check(fp) == false)
        return false;
 return true;
}

bool riff_check(FILE* fp)
{
    if (header.chunkId[0] == 0x52 && header.chunkId[1] == 0x49 && header.chunkId[2] == 0x46 && header.chunkId[3] == 0x46)
        {
            return true;
        }
        else
        {
            return false;
        }
}
