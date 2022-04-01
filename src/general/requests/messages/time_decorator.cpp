#include "time_decorator.hpp"

TimeDecorator::TimeDecorator(std::shared_ptr<Message> message)
        : PropertiesDecorator(message), timestamp(time(nullptr)) {}

std::string TimeDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Time)) + Request::separator +
           std::to_string(timestamp);
}
