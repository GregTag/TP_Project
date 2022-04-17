#include "console_renderer.hpp"

void ConsoleRenderer::reset() {
    time = "";
    room = "";
    sender = "";
    text = "";
    is_private = false;
}

void ConsoleRenderer::baseMessageRender(std::shared_ptr<Message> msg) {
    MessageTypes type = std::static_pointer_cast<BaseMessage>(msg)->getType();
    std::cout << time;

    if (type == MessageTypes::Error) std::cout << "[ERROR] ";
    if (type == MessageTypes::Info) std::cout << "[INFO] ";
    if (type == MessageTypes::Chat && !room.empty()) {
        if (room == "0")
            std::cout << "[All] ";
        else
            std::cout << "[" << room << "] ";
    }
    if (!sender.empty()) std::cout << sender << " ";

    if (type == MessageTypes::Join || type == MessageTypes::Leave) {
        std::cout << (type == MessageTypes::Join ? "joined." : "leaved.");
    } else {
        if (!text.empty()) std::cout << (is_private ? "[P]: " : ": ") << text;
    }
    std::cout << std::endl;

    reset();
}

// [time] [type|room] sender [P]: text

void ConsoleRenderer::timeRender(std::shared_ptr<Message> msg) {
    time_t timestamp = std::static_pointer_cast<TimeDecorator>(msg)->getTimestamp();
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timestamp), "[%H:%M] ");
    ss >> time;
}

void ConsoleRenderer::roomRender(std::shared_ptr<Message> msg) {
    room = std::to_string(std::static_pointer_cast<RoomDecorator>(msg)->getRoom());
}

void ConsoleRenderer::senderRender(std::shared_ptr<Message> msg) {
    sender = std::static_pointer_cast<SenderDecorator>(msg)->getSender();
}

void ConsoleRenderer::textRender(std::shared_ptr<Message> msg) {
    text += std::static_pointer_cast<TextDecorator>(msg)->getText();
}

void ConsoleRenderer::privateRender(std::shared_ptr<Message> msg) {
    is_private = true;
}
