#include "struckt.h"

void print(FILE* fp)
{

    // ������� ���������� ������
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Channels: %d\n", header.numChannels);
    printf("Bits per sample: %d\n", header.bitsPerSample);
    printf("chunkSize: %d byte\n", header.chunkSize);

    // ��������� ������������ ��������������� � ��������
    int total = header.chunkSize / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate, secs = total % 60, mins = total / 60;

    printf("Duration: %02d:%02d\n", mins, secs);
}
