#include <iostream>
#include "engineTester/MainGameLoop.h"

int main(int argc, char *argv[]) {
    std::cout << "GL Started!" << std::endl;
    MainGameLoop::main();
    return 0;
}
