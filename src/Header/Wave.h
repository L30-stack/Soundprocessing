#ifndef SOUNDPROCESSING_WAVE_H
#define SOUNDPROCESSING_WAVE_H
#include <iostream>

typedef struct {
    unsigned char chunkID[4];
    unsigned int chunkSize;
    unsigned char format[4];
    unsigned char subchunk1ID[4];
    unsigned int subchunk1Size;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    unsigned char subchunk2ID[4];
    unsigned int subchunk2Size;
} HEADER;

class Wave
{
private:
    FILE *file{};
    FILE *outFile{};
    static HEADER header;

public:
    explicit Wave(const char *fileName);
    ~Wave();
    static HEADER getHeader();
    static int setHeader(HEADER _header);
    static void printHeader();
    int getData(const char *fileName);
    int getPlottableData(const char *fileName);
};


#endif //SOUNDPROCESSING_WAVE_H
