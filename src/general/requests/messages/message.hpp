#pragma once
#include "requests/request.hpp"

enum class MessageProperties { Type, Time, Room, Sender, Text, Private };

class Message : public Request {
   public:
    virtual size_t getRoom() const = 0;
};
