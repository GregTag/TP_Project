#include "time_decorator.hpp"

TimeDecorator::TimeDecorator(std::shared_ptr<Message> message)
        : TimeDecorator(message, time(nullptr)) {}

TimeDecorator::TimeDecorator(std::shared_ptr<Message> message, time_t ts)
        : PropertiesDecorator(message), timestamp(ts) {}

std::string TimeDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Time)) + Request::separator +
           std::to_string(timestamp);
}
