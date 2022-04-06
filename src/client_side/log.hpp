#pragma once
#include <fstream>

#include "socket/log.hpp"

class DebugLogger : public Logger {
   public:
    static void initialize(std::string path_to_log_file);

   protected:
    std::ostream& getLogStream() override;
    std::ostream& getErrorStream() override;

   private:
    DebugLogger(std::string);

    std::fstream file;
};
