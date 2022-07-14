//
// Created by leona on 13.07.2022.
//
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
} wav_header_t;