#include "time_decorator.hpp"

TimeDecorator::TimeDecorator(std::shared_ptr<Message> message)
        : TimeDecorator(message, time(nullptr)) {}

TimeDecorator::TimeDecorator(std::shared_ptr<Message> message, time_t ts)
        : PropertiesDecorator(message), timestamp(ts) {}

std::string TimeDecorator::getQuery() const {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Time)) + Request::separator +
           std::to_string(timestamp);
}

void TimeDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->timeRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}

time_t TimeDecorator::getTimestamp() const {
    return timestamp;
}
