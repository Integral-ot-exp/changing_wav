//Эта программа изменяет АЧХ WAV-файлов
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <math.h>
#include <stdint.h>

#define EOF (-1)
//#define BUF_SIZE 1024
#define OPEN_MAX 20 /* max число одновременно открытых файлов */
typedef struct iobuf
{
    int cnt; /* количество оставшихся символов */
    char *ptr; /* позиция следующего символа */
    char *base; /* адрес буфера */
    int flag; /* режим доступа */
    int fd; /* дескриптор файла */
} wavfile;
extern FILE iob[OPEN_MAX];
enum _flags {
_READ =01, /* файл открыт на чтение */
_WRITE = 02, /* файл открыт на запись */
_UNBUF = 04, /* файл не буферизуется */
_EOF = 010, /* в данном файле встретился EOF */
_ERR = 020 /* в данном файле встретилась ошибка */
};
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 \
? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)
// Структура, описывающая заголовок WAV файла.
struct WAVHEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    int8_t chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    uint32_t chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    int8_t format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:

    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    int8_t subchunk1Id[4];

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    uint32_t subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    uint16_t audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    uint16_t numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    uint32_t sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    uint32_t byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    uint16_t blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    uint16_t bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    int8_t subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    uint32_t subchunk2Size;

    // Далее следуют непосредственно Wav данные.
};

int main()
{
    FILE *fp;

    //char* name;
    //scanf("%s", name);
    fp = fopen("prob.wav", "rb");
    /*if (fp == NULL)
    {
        printf("Failed open file, error");
        return 0;
    }*/
    struct WAVHEADER header;

    printf("1st step\n");

    fread(&header, sizeof(struct WAVHEADER), 1, "prob.wav");

    printf("2nd step\n");

    // Выводим полученные данные
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Channels: %d\n", header.numChannels);
    printf("Bits per sample: %d\n", header.bitsPerSample);
/*
    // Посчитаем длительность воспроизведения в секундах
    float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    printf("Duration: %02d:%02.f\n", iDurationMinutes, fDurationSeconds);
*/
    fclose("prob.wav");
    _getch();
    return 0;
}
