#include "./src/Header/Wave.h"
#include "./src/Header/Plotter.h"

#define ABS_PATH "C:\\Users\\leona\\CLionProjects\\Soundprocessing\\WAV_2MB.wav"

int main() {
    Wave wave(ABS_PATH);
    wave.getPlottableData(ABS_PATH);
    Plotter::plot(ABS_PATH);
    return 0;
}