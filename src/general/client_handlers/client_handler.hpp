#pragma once
#include "abstract_handler.hpp"

class ClientsideHandler : public AbstractClientHandler,
                          std::enable_shared_from_this<ClientsideHandler> {
   public:
    ClientsideHandler(std::shared_ptr<Socket>);
    virtual ~ClientsideHandler() = default;

    void receive(std::shared_ptr<Request>) override;

    void signIn(const std::string& name, const std::string& password);
    void signUp(const std::string& name, const std::string& password);
    std::string getHistory(size_t);
    std::shared_ptr<std::vector<std::pair<size_t, std::string>>> getUsers(size_t room);
    void send(size_t room, const std::string& text);
    void sendPrivate(size_t room, size_t user, const std::string& text);

    virtual void renderMessage(std::shared_ptr<Message>) = 0;
};
