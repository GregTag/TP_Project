#pragma once
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <fstream>
#include <iostream>

#include "socket/log.hpp"

class ServerLogger : public Logger {
   public:
    virtual ~ServerLogger();
    static void initialize(const std::string& path_to_log_file);

   protected:
    std::ostream& getLogStream() override;
    std::ostream& getErrorStream() override;

   private:
    using Device = boost::iostreams::tee_device<std::ostream, std::ofstream>;
    ServerLogger(const std::string&);

    std::ofstream file;
    Device device;
    boost::iostreams::stream<Device> stream;
};
