#pragma once
#include "request_handlers/server_handler.hpp"
#include "requests/authorization/sign_in_request.hpp"
#include "requests/authorization/sign_up_request.hpp"
#include "requests/messages/message.hpp"
#include "requests/messages/private_decorator.hpp"
#include "room.hpp"
#include "server.hpp"

class ClientConnection : public ServersideHandler {
   public:
    ClientConnection(size_t, std::shared_ptr<Socket>, std::weak_ptr<Server>);
    virtual ~ClientConnection();

    std::shared_ptr<Room> getRoom(size_t room_id);

    void destroy() override;
    void onSignUp(std::shared_ptr<SignUpRequest>) override;
    void onSignIn(std::shared_ptr<SignInRequest>) override;
    void onMessage(std::shared_ptr<Message>) override;
    void onPrivateMessage(std::shared_ptr<PrivateDecorator>) override;

   private:
    const size_t id;
    std::weak_ptr<Server> server;
    std::unordered_map<size_t, std::weak_ptr<Room>> rooms;
};
