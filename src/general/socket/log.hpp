#pragma once

#include <memory>
#include <ostream>

class Logger {
   public:
    virtual ~Logger() = default;

    static std::ostream& log();
    static std::ostream& err();

   protected:
    virtual std::ostream& getLogStream() = 0;
    virtual std::ostream& getErrorStream() = 0;

    static std::shared_ptr<Logger> instance;
};
