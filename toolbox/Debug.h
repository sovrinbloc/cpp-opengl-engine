//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H
#include "quill/Quill.h"

static quill::Logger *getLogger(std::string output="logger.log") {
    quill::enable_console_colours();
    quill::start();
    quill::Handler* file_handler = quill::file_handler("logger.log", "wr");
    quill::Logger *logger = quill::create_logger("debugger", file_handler);
    return logger;
}



#endif //ENGINE_DEBUG_H
