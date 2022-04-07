#pragma once
#include "abstract_handler.hpp"
#include "renderer.hpp"

class ClientsideHandler : public AbstractClientHandler {
   public:
    ClientsideHandler(std::shared_ptr<Socket>, std::shared_ptr<MessageRenderer>);
    virtual ~ClientsideHandler() = default;

    void receive(std::shared_ptr<Request>) override;

    void signIn(const std::string& name, const std::string& password);
    void signUp(const std::string& name, const std::string& password);

    std::string getHistory(size_t);
    std::shared_ptr<std::vector<std::pair<size_t, std::string>>> getUsers(size_t room);
    std::shared_ptr<MessageRenderer> getRenderer();

    void send(size_t room, const std::string& text);
    void sendPrivate(size_t room, size_t user, const std::string& text);

   protected:
    std::shared_ptr<MessageRenderer> renderer;
};
