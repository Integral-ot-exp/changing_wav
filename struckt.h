#ifndef STRUCKT_H_INCLUDED
#define STRUCKT_H_INCLUDED


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool mist(FILE*);
void print(FILE*);


// ���������, ����������� ��������� WAV �����.
struct WAVHEADER
{
    // WAV-������ ���������� � RIFF-���������:

    // �������� ������� "RIFF" � ASCII ���������
    // (0x52494646 � big-endian �������������)
    uint8_t chunkId[4];

    // 36 + subchunk2Size, ��� ����� �����:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // ��� ���������� ������ �������, ������� � ���� �������.
    // ����� ������, ��� ������ ����� - 8, �� ����,
    // ��������� ���� chunkId � chunkSize.
    uint32_t chunkSize;

    // �������� ������� "WAVE"
    // (0x57415645 � big-endian �������������)
    uint8_t format[4];

    // ������ "WAVE" ������� �� ���� ����������: "fmt " � "data":
    // ���������� "fmt " ��������� ������ �������� ������:

    // �������� ������� "fmt "
    // (0x666d7420 � big-endian �������������)
    uint8_t subchunk1Id[4];

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
    uint8_t subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // ���������� ���� � ������� ������.
    uint32_t subchunk2Size;

    // ����� ������� ��������������� Wav ������.
};
#endif // STRUCKT_H_INCLUDED
