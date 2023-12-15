//Эта программа изменяет АЧХ WAV-файлов
#include "struckt.h"


int main()
{
    FILE *fp;
    char name[256];
    struct WAVHEADER header;

    scanf("%s", name);
    printf("name = %s\n", name);
    fp = fopen(name, "rb");

    fread(&header, sizeof(struct WAVHEADER), 1, fp);

    if (mist(fp) == 0)
        return 0;

    print(fp);
    fclose(fp);
    return 0;
}
