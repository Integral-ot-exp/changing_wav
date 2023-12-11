//��� ��������� �������� ��� WAV-������
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <math.h>
#include <stdint.h>

#define EOF (-1)
//#define BUF_SIZE 1024
#define OPEN_MAX 20 /* max ����� ������������ �������� ������ */
typedef struct iobuf
{
    int cnt; /* ���������� ���������� �������� */
    char *ptr; /* ������� ���������� ������� */
    char *base; /* ����� ������ */
    int flag; /* ����� ������� */
    int fd; /* ���������� ����� */
} wavfile;
extern FILE iob[OPEN_MAX];
enum _flags {
_READ =01, /* ���� ������ �� ������ */
_WRITE = 02, /* ���� ������ �� ������ */
_UNBUF = 04, /* ���� �� ������������ */
_EOF = 010, /* � ������ ����� ���������� EOF */
_ERR = 020 /* � ������ ����� ����������� ������ */
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
// ���������, ����������� ��������� WAV �����.
struct WAVHEADER
{
    // WAV-������ ���������� � RIFF-���������:

    // �������� ������� "RIFF" � ASCII ���������
    // (0x52494646 � big-endian �������������)
    int8_t chunkId[4];

    // 36 + subchunk2Size, ��� ����� �����:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // ��� ���������� ������ �������, ������� � ���� �������.
    // ����� ������, ��� ������ ����� - 8, �� ����,
    // ��������� ���� chunkId � chunkSize.
    uint32_t chunkSize;

    // �������� ������� "WAVE"
    // (0x57415645 � big-endian �������������)
    int8_t format[4];

    // ������ "WAVE" ������� �� ���� ����������: "fmt " � "data":
    // ���������� "fmt " ��������� ������ �������� ������:

    // �������� ������� "fmt "
    // (0x666d7420 � big-endian �������������)
    int8_t subchunk1Id[4];

    // 16 ��� ������� PCM.
    // ��� ���������� ������ ����������, ������� � ���� �������.
    uint32_t subchunk1Size;

    // ����� ������, ������ ������ ����� �������� ����� http://audiocoding.ru/wav_formats.txt
    // ��� PCM = 1 (�� ����, �������� �����������).
    // ��������, ������������ �� 1, ���������� ��������� ������ ������.
    uint16_t audioFormat;

    // ���������� �������. ���� = 1, ������ = 2 � �.�.
    uint16_t numChannels;

    // ������� �������������. 8000 ��, 44100 �� � �.�.
    uint32_t sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    uint32_t byteRate;

    // numChannels * bitsPerSample/8
    // ���������� ���� ��� ������ ������, ������� ��� ������.
    uint16_t blockAlign;

    // ��� ���������� "��������" ��� �������� ��������. 8 ���, 16 ��� � �.�.
    uint16_t bitsPerSample;

    // ���������� "data" �������� �����-������ � �� ������.

    // �������� ������� "data"
    // (0x64617461 � big-endian �������������)
    int8_t subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // ���������� ���� � ������� ������.
    uint32_t subchunk2Size;

    // ����� ������� ��������������� Wav ������.
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

    // ������� ���������� ������
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Channels: %d\n", header.numChannels);
    printf("Bits per sample: %d\n", header.bitsPerSample);
/*
    // ��������� ������������ ��������������� � ��������
    float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    printf("Duration: %02d:%02.f\n", iDurationMinutes, fDurationSeconds);
*/
    fclose("prob.wav");
    _getch();
    return 0;
}
