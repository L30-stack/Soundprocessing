//
// Created by leona on 14.07.2022.
//

#include <string>
#include "Plotter.h"

Plotter::Plotter() {
    gnuplotPipe = _popen("gnuplot -persist", "w");
}

Plotter::~Plotter() {
    fclose(gnuplotPipe);
}

void Plotter::plot(const char *fileName) {
    std::string command = "plot '" + std::string(fileName) + "' with lines";
    fprintf(gnuplotPipe, "%s\n", command.c_str());
}
