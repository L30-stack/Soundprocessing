//
// Created by leona on 14.07.2022.
//

#ifndef SOUNDPROCESSING_PLOTTER_H
#define SOUNDPROCESSING_PLOTTER_H


#include <cstdio>

class Plotter {
private:
    static FILE *gnuplotPipe;
public:
    Plotter();

    ~Plotter();

    static void plot(const char *fileName);
};


#endif //SOUNDPROCESSING_PLOTTER_H
