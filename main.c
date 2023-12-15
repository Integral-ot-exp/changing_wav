//Эта программа изменяет АЧХ WAV-файлов
#include "wav_head.h"

int main()
{
    FILE *fp;
    char name[256];

    scanf("%s", name);
    printf("name = %s\n", name);
    fp = fopen(name, "rb");

    if (errors(fp) == false)
        return 0;
    fclose(fp);
    fp = fopen(name, "rb");
    print_wav(fp);
    return 0;
}
