#include <iostream>
#include <stdio.h>
#include "pts_reader.h"

int main (int argc, char ** argv) {
    std::string pth = argv[1];
    run_converter(pth);
}