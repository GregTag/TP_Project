#pragma once
#include "database/accounts_database.hpp"
#include "permissions.hpp"
#include "request_handlers/server_handler.hpp"
#include "room.hpp"
#include "server.hpp"

class ClientConnection : public ServersideHandler {
   public:
    ClientConnection(size_t, std::shared_ptr<Socket>, std::weak_ptr<Server>);
    virtual ~ClientConnection() = default;

    void destroy() override;
    void onSignUp(std::shared_ptr<SignUpRequest>) override;
    void onSignIn(std::shared_ptr<SignInRequest>) override;
    void onMessage(std::shared_ptr<Message>) override;
    void onPrivateMessage(std::shared_ptr<PrivateDecorator>) override;

   private:
    void sendError(const std::string&);
    std::shared_ptr<Room> getRoom(size_t room_id);
    void joinEvent(std::shared_ptr<Message>);
    void leaveEvent(std::shared_ptr<Message>);
    void userListEvent(std::shared_ptr<Message>);
    void historyEvent(std::shared_ptr<Message>);
    void chatEvent(std::shared_ptr<Message>);
    void manageEvent(std::shared_ptr<Message>);

    const size_t id;
    std::weak_ptr<Server> server;
    std::unordered_map<size_t, std::weak_ptr<Room>> rooms;
};
