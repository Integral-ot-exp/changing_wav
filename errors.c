#include "wav_head.h"
bool riff_check(struct WAVHEADER);
bool wave_check(struct WAVHEADER);
bool fmt_check(struct WAVHEADER);
bool data_check(struct WAVHEADER);

bool errors(FILE* fp)
{
    if (fp == NULL)
        {
            printf("Failed open file, error");
            return false;
        }
    struct WAVHEADER header;
    fread(&header, sizeof(struct WAVHEADER), 1, fp);
    if(riff_check(header) == false || wave_check(header) == false || /*fmt_check(header) == false ||*/ data_check(header) == false)
    {
        printf("Failed open file, not WAV");
        return false;
    }
    fclose(fp);
 return true;
}

bool riff_check(struct WAVHEADER header)
{
    return header.chunkId[0] == 0x52 && header.chunkId[1] == 0x49 && header.chunkId[2] == 0x46 && header.chunkId[3] == 0x46;
}

bool wave_check(struct WAVHEADER header)
{
    return header.format[0] == 0x57 && header.format[1] == 0x41 && header.format[2] == 0x56 && header.format[3] == 0x45;
}

bool fmt_check(struct WAVHEADER header)
{
    printf("fmt_check %x %x %x %x", header.subchunk1Id[0], header.subchunk1Id[1], header.subchunk1Id[2], header.subchunk1Id[3]);
    header.subchunk1Id[0] == 0x66 && header.subchunk1Id[1] == 0x6d && header.subchunk1Id[2] == 0x74 && header.subchunk1Id[3] == 0x20;
}

bool data_check(struct WAVHEADER header)
{
    printf("data_check %x %x %x %x", header.subchunk2Id[0], header.subchunk2Id[1], header.subchunk2Id[2], header.subchunk2Id[3]);
    return header.subchunk2Id[0] == 0x64 && header.subchunk2Id[1] == 0x61 && header.subchunk2Id[2] == 0x74 && header.subchunk2Id[3] == 0x61;
}
