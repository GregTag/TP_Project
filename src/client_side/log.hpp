#pragma once
#include <fstream>

#include "socket/log.hpp"

class DebugLogger : public Logger {
   public:
    ~DebugLogger();

    static void initialize(const std::string& path_to_log_file);

   protected:
    std::ostream& getLogStream() override;
    std::ostream& getErrorStream() override;

   private:
    DebugLogger(const std::string&);

    std::fstream file;
};
