#include <dpp/dpp.h>

#include <fstream>
#include <iostream>

#include "borothy.hpp"

int main() {
    std::fstream file("./BOT_TOKEN");
    if (!file.is_open()) {
        std::cerr << "Could not find file BOT_TOKEN. Exiting..." << std::endl;
        exit(1);
    }

    std::string BOT_TOKEN;
    file >> BOT_TOKEN;

    if (BOT_TOKEN.empty()) {
        std::cerr << "No token found inside file BOT_TOKEN. Exiting..."
                  << std::endl;
        exit(1);
    }

    Borothy borothy(BOT_TOKEN);
    borothy.start();
}
