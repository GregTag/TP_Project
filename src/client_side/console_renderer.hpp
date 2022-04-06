#pragma once
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "client_handlers/client_handler.hpp"
#include "requests/request_creators.hpp"

class ConsoleRenderer : public MessageRenderer {
   public:
    ConsoleRenderer() = default;

    void reset();

    void baseMessageRender(std::shared_ptr<Message>) override;
    void timeRender(std::shared_ptr<Message>) override;
    void roomRender(std::shared_ptr<Message>) override;
    void senderRender(std::shared_ptr<Message>) override;
    void textRender(std::shared_ptr<Message>) override;
    void privateRender(std::shared_ptr<Message>) override;

   private:
    std::string time;
    std::string room;
    std::string sender;
    std::string text;
    bool is_private;
};