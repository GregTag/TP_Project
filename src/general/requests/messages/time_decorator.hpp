#pragma once
#include "properties_decorator.hpp"
#include "time.h"

class TimeDecorator : public PropertiesDecorator {
   public:
    TimeDecorator(std::shared_ptr<Message> message);
    TimeDecorator(std::shared_ptr<Message> message, time_t ts);
    virtual ~TimeDecorator() = default;

    std::string getQuery() override;

   private:
    time_t timestamp;
};
