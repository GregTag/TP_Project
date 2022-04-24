#include "client_connection.hpp"

ClientConnection::ClientConnection(size_t id, std::shared_ptr<Socket> socket,
                                   std::weak_ptr<Server> server)
        : ServersideHandler(socket), id(id), server(server) {}

void ClientConnection::destroy() {
    if (server.expired()) {
        Logger::err() << "No server?" << std::endl;
        return;
    }

    for (auto& [id, room] : rooms) {
        if (room.expired()) continue;
        room.lock()->leave(sharedFromThis());
    }

    server.lock()->eraseConnection(id);
}

void ClientConnection::onSignUp(std::shared_ptr<SignUpRequest> request) {
    auto account = AccountsDatabase::getInstance()->createAccount(
            request->getAccount()->getName(), request->getAccount()->getPasswordHash(),
            AccountsDatabase::getInstance()->loadAccount(0)->getAvailableRooms());
    if (!account) {
        sendError("Authorization denied: account with same name is already exists.");
    } else {
        setAccount(account);
        request->setAccount(account);
        sendRequest(request);
    }
}

void ClientConnection::onSignIn(std::shared_ptr<SignInRequest> request) {
    auto account =
            AccountsDatabase::getInstance()->findAccountByName(request->getAccount()->getName());
    if (!account) {
        sendError("Authorization denied: account does not exists.");
    } else if (account->getPasswordHash() != request->getAccount()->getPasswordHash()) {
        sendError("Authorization denied: wrong password.");
    } else {
        setAccount(account);
        request->setAccount(account);
        sendRequest(request);
    }
}

void ClientConnection::onMessage(std::shared_ptr<Message> request) {
    switch (request->getType()) {
        case MessageTypes::Join:
            joinEvent(request);
            break;
        case MessageTypes::Leave:
            leaveEvent(request);
            break;
        default:
            break;
    }
}

void ClientConnection::onPrivateMessage(std::shared_ptr<PrivateDecorator> request) {}

void ClientConnection::sendError(const std::string& text) {
    sendRequest(getCreator()->createErrorMessage(text));
}

std::shared_ptr<Room> ClientConnection::getRoom(size_t room_id) {
    auto found = rooms.find(room_id);
    if (found == rooms.end()) return nullptr;
    return found->second.lock();
}

void ClientConnection::joinEvent(std::shared_ptr<Message> request) {
    if (!getAccount()->getAvailableRooms().count(request->getRoom())) {
        sendError("Wrong room for join.");
        return;
    }
    if (rooms.count(request->getRoom())) {
        sendError("Already joined to room.");
        return;
    }
    auto room = server.lock()->getOrCreateRoom(request->getRoom());
    room->join(sharedFromThis());
    rooms.emplace(request->getRoom(), room);
    room->broadcast(request);
}

void ClientConnection::leaveEvent(std::shared_ptr<Message> request) {
    auto room = getRoom(request->getRoom());
    if (!room) {
        sendError("Wrong room for leaving.");
        return;
    }

    room->broadcast(request);
    room->leave(sharedFromThis());
    rooms.erase(request->getRoom());
}

// std::unordered_map<size_t, std::weak_ptr<Room>>& ServersideHandler::getRooms() {
//     return rooms;
// }

// void ServersideHandler::onMessage(std::shared_ptr<Message> msg) {
//     if (msg->getType() == MessageTypes::Join) {
//         Logger::log() << "New member in room " << msg->getRoom() << std::endl;
//         // But we have no rooms yet
//     } else {
//         getRoom(msg->getRoom())->broadcast(msg);
//     }
// }

// void ServersideHandler::onPrivateMessage(std::shared_ptr<PrivateDecorator> msg) {
//     getRoom(msg->getRoom())->getClient(msg->getAddressee())->sendRequest(msg);
// }
