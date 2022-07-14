#include "Wave.h"
#include <iostream>
#include <cstring>

Wave::~Wave() {
    fclose(file);
    fclose(outFile);
}

Wave::Wave(const char *fileName) {
    file = fopen(fileName, "rb");
    if (file == nullptr) {
        std::cout << "File not found" << std::endl;
        exit(1);
    }
    fread(&header, sizeof(HEADER), 1, file);
}

HEADER Wave::getHeader() {
    return header;
}

void Wave::printHeader() {
    printf("WAV File Header read:\n\n");
    printf("File Type                 |   %c%c%c%c\n", header.chunkID[0], header.chunkID[1], header.chunkID[2],
           header.chunkID[3]);
    printf("File Size                 |   %ld\n", header.chunkSize);
    printf("WAV Marker                |   %c%c%c%c\n", header.format[0], header.format[1], header.format[2],
           header.format[3]);
    printf("Format Name               |   %c%c%c\n", header.subchunk1ID[0], header.subchunk1ID[1],
           header.subchunk1ID[2]);
    printf("Format Length             |   %ld\n", header.subchunk1Size);
    printf("Format Type               |   %hd\n", header.audioFormat);
    printf("Number of Channels        |   %hd\n", header.numChannels);
    printf("Sample Rate               |   %ld\n", header.sampleRate);
    printf("Sample Rate * Bits        \n "
           "per Sample * Channels/8  |   %ld\n", header.byteRate);
    printf("Number of Channels        \n"
           " * Channels / 8.1         |   %hd\n", header.blockAlign);
    printf("Bits per Sample:          |   %hd\n", header.bitsPerSample);
    printf("Data Marker               |   %c%c%c%c\n", header.subchunk2ID[0], header.subchunk2ID[1],
           header.subchunk2ID[2], header.subchunk2ID[3]);
    printf("Data Length               |   %ld\n", header.subchunk2Size);
    printf("\n");
}

int Wave::setHeader(HEADER _header) {
    if (_header.chunkID[0] != 'R' || _header.chunkID[1] != 'I' || _header.chunkID[2] != 'F' ||
        _header.chunkID[3] != 'F') {
        std::cout << "Invalid ChunkID" << std::endl;
        return 1;
    }
    if (_header.format[0] != 'W' || _header.format[1] != 'A' || _header.format[2] != 'V' || _header.format[3] != 'E') {
        std::cout << "Invalid Format" << std::endl;
        return 1;
    }
    if (_header.subchunk1ID[0] != 'f' || _header.subchunk1ID[1] != 'm' || _header.subchunk1ID[2] != 't' ||
        _header.subchunk1ID[3] != ' ') {
        std::cout << "Invalid Subchunk1ID" << std::endl;
        return 1;
    }
    if (_header.subchunk2ID[0] != 'd' || _header.subchunk2ID[1] != 'a' || _header.subchunk2ID[2] != 't' ||
        _header.subchunk2ID[3] != 'a') {
        std::cout << "Invalid Subchunk2ID" << std::endl;
        return 1;
    }
    if (_header.byteRate != _header.sampleRate * _header.numChannels * _header.bitsPerSample / 8) {
        std::cout << "Invalid ByteRate" << std::endl;
        return 1;
    }
    if (_header.blockAlign != _header.numChannels * _header.bitsPerSample / 8) {
        std::cout << "Invalid BlockAlign" << std::endl;
        return 1;
    }
    if (_header.bitsPerSample != 8 && _header.bitsPerSample != 16) {
        std::cout << "Invalid BitsPerSample" << std::endl;
        return 1;
    }
    header = _header;
    return 0;
}

int Wave::getData(const char *fileName) {
    outFile = fopen(fileName, "w");
    int sample_size = header.bitsPerSample / 8;
    unsigned int samples_count = header.subchunk2Size / sample_size;
    auto *value = new short int[samples_count];
    memset(value, 0, sizeof(short int) * samples_count);
    for (int i = 0; i < samples_count; i++) {
        fread(value + i, sizeof(short int), samples_count, file);
        fprintf(outFile, "%d\n", value[i]);
    }
    fclose(outFile);
    delete[] value;
    return 0;
}

int Wave::getPlottableData(const char *fileName) {
    outFile = fopen(fileName, "w");
    int sample_size = header.bitsPerSample / 8;
    unsigned int samples_count = header.subchunk2Size / sample_size;
    auto *value = new short int[samples_count];
    memset(value, 0, sizeof(short int) * samples_count);
    for (int i = 0; i < samples_count; i++) {
        fread(value + i, sizeof(short int), samples_count, file);
        fprintf(outFile, "%d %d\n", i, value[i]);
    }
    fclose(outFile);
    delete[] value;
    return 0;
}
