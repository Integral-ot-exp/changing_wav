//��� ��������� �������� ��� WAV-������
#include <stdio.h>
#include <stdint.h>


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
    int32_t chunkSize;

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
    int32_t subchunk1Size;

    // ����� ������, ������ ������ ����� �������� ����� http://audiocoding.ru/wav_formats.txt
    // ��� PCM = 1 (�� ����, �������� �����������).
    // ��������, ������������ �� 1, ���������� ��������� ������ ������.
    int16_t audioFormat;

    // ���������� �������. ���� = 1, ������ = 2 � �.�.
    int16_t numChannels;

    // ������� �������������. 8000 ��, 44100 �� � �.�.
    int32_t sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    int32_t byteRate;

    // numChannels * bitsPerSample/8
    // ���������� ���� ��� ������ ������, ������� ��� ������.
    int16_t blockAlign;

    // ��� ���������� "��������" ��� �������� ��������. 8 ���, 16 ��� � �.�.
    int16_t bitsPerSample;

    // ���������� "data" �������� �����-������ � �� ������.

    // �������� ������� "data"
    // (0x64617461 � big-endian �������������)
    int8_t subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // ���������� ���� � ������� ������.
    int32_t subchunk2Size;

    // ����� ������� ��������������� Wav ������.
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

    // ������� ���������� ������
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Channels: %d\n", header.numChannels);
    printf("Bits per sample: %d\n", header.bitsPerSample);
    printf("chunkSize: %d byte\n", header.chunkSize);

    // ��������� ������������ ��������������� � ��������
    int DurationSeconds = header.chunkSize / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int DurationMinutes = DurationSeconds / 60;
    DurationSeconds = DurationSeconds - (DurationMinutes * 60);
    printf("Duration: %02d:%02d\n", DurationMinutes, DurationSeconds);

    return 0;
}
