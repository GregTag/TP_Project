#pragma once
#include "requests/request.hpp"

enum class MessageProperties { Type, Time, Room, Sender, Text, Private };

enum class MessageTypes { Chat, Info, Error, Join, Leave, UserList, History };

class Message : public Request {
   public:
    virtual ~Message() = default;

    virtual size_t getRoom() const = 0;
    virtual MessageTypes getType() const = 0;
};
