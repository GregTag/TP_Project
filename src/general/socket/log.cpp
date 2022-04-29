#include "log.hpp"

std::ostream& Logger::log() {
    return instance->getLogStream();
}

std::ostream& Logger::err() {
    return instance->getErrorStream();
}

std::shared_ptr<Logger> Logger::instance(nullptr);
