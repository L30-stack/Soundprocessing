#include <iostream>
#include <cstring>

#define ABS_PATH "C:\\Users\\leona\\CLionProjects\\Soundprocessing\\WAV_2MB.wav"

//Wav Header
struct wav_header_t {
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
};

void Plotter() {
    FILE *gnuplotPipe = _popen("gnuplot -persist", "w");
    char *plotCommand[] = {"set title \"WAV_130KB.wav\"", "set xlabel \"Time\"", "set ylabel \"Amplitude\"",
                           "plot 'C:\\Users\\leona\\CLionProjects\\Soundprocessing\\cmake-build-debug\\WAV_130KB.tmp'"};


    for (auto &i: plotCommand) {
        fprintf(gnuplotPipe, "%s\n", i);
        printf("%s\n", i);
    }
}

void WavReader(const char *fileName) {

    FILE *fin = fopen(fileName, "rb");

    if (fin == nullptr) {
        printf("Error opening file\n");
        return;
    }
    wav_header_t header{};
    //Read WAV header
    fread(&header, sizeof(wav_header_t), 1, fin);
    for (int i = 0; i < 5; i++) {
        printf("%i ", (int) header.chunkID[i]);
    }

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

    //Read data
    unsigned long dataSize = header.subchunk2Size;
    //Number of samples
    int sample_size = header.bitsPerSample / 8;
    int samples_count = header.subchunk2Size * 8 / header.bitsPerSample;
    printf("Samples count = %i\n", samples_count);

    auto *value = new short int[samples_count];
    memset(value, 0, sizeof(short int) * samples_count);


    FILE *fout = fopen("WAV_130KB.tmp", "w");
    //Reading data
    short int max;
    short int min;
    for (int i = 0; i < samples_count; i++) {
        fread(value + i, sample_size, 1, fin);
        fprintf(fout, "%i %i\n", i, value[i]);
        if (i == 0) {
            max = value[0];
            min = value[0];
        }
        if (value[i] > max) {
            max = value[i];
        }
        if (value[i] < min) {
            min = value[i];
        }
    }
    printf("Max = %i\n", max);
    printf("Min = %i\n", min);

    fclose(fin);
    fclose(fout);
}

int main() {
    WavReader(ABS_PATH);
    Plotter();
    return 0;
}