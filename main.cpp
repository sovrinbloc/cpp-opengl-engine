#include <iostream>
#include "engineTester/MainGameLoop.h"
//#include "renderEngine/ObjLoader.h"
int main() {
    std::cout << "GL Started!" << std::endl;
    MainGameLoop::main();
    return 0;
}
