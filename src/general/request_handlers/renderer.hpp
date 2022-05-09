#pragma once
#include <memory>

class Message;

class MessageRenderer {
   public:
    virtual ~MessageRenderer() = default;

    virtual void baseMessageRender(std::shared_ptr<Message>) = 0;
    virtual void timeRender(std::shared_ptr<Message>) = 0;
    virtual void roomRender(std::shared_ptr<Message>) = 0;
    virtual void senderRender(std::shared_ptr<Message>) = 0;
    virtual void textRender(std::shared_ptr<Message>) = 0;
    virtual void privateRender(std::shared_ptr<Message>) = 0;
};
