#pragma once
#include <unordered_map>

#include "abstract_handler.hpp"

class SignUpRequest;
class SignInRequest;
class PrivateDecorator;

class ServersideHandler : public AbstractHandler {
   public:
    ServersideHandler(std::shared_ptr<Socket>);
    virtual ~ServersideHandler() = default;

    void receive(std::shared_ptr<Request>) override;

    virtual void onSignUp(std::shared_ptr<SignUpRequest>) = 0;
    virtual void onSignIn(std::shared_ptr<SignInRequest>) = 0;
    virtual void onMessage(std::shared_ptr<Message>) = 0;
    virtual void onPrivateMessage(std::shared_ptr<PrivateDecorator>) = 0;
};
