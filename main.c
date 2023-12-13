//Эта программа изменяет АЧХ WAV-файлов
#include <stdio.h>
#include <stdint.h>


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
    int32_t chunkSize;

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
    int32_t subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    int16_t audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    int16_t numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    int32_t sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    int32_t byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    int16_t blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    int16_t bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    int8_t subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    int32_t subchunk2Size;

    // Далее следуют непосредственно Wav данные.
};

int main()
{
    FILE *fp;

    char name;
    scanf("%s", &name);
    fp = fopen(&name, "rb");
    if (fp == NULL)
    {
        printf("Failed open file, error");
        return 0;
    }
    struct WAVHEADER header;

    fread(&header, sizeof(struct WAVHEADER), 1, fp);

    // Выводим полученные данные
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Channels: %d\n", header.numChannels);
    printf("Bits per sample: %d\n", header.bitsPerSample);
    printf("chunkSize: %d byte\n", header.chunkSize);

    // Посчитаем длительность воспроизведения в секундах
    int DurationSeconds = header.chunkSize / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int DurationMinutes = DurationSeconds / 60;
    DurationSeconds = DurationSeconds - (DurationMinutes * 60);
    printf("Duration: %02d:%02d\n", DurationMinutes, DurationSeconds);

    return 0;
}
