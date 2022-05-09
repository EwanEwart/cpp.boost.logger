// #define BOOST_ALL_DYN_LINK 1
// #define BOOST_LOG_DYN_LINK 1

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp> // boost::log::add_file_log
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
// #include <boost/log/core.hpp>
// #include <boost/log/expressions.hpp>
// #include <boost/log/sinks/text_file_backend.hpp>
// #include <boost/log/sources/record_ostream.hpp>
// #include <boost/log/sources/basic_logger.hpp>
// #include <boost/log/sources/logger.hpp>

// namespace logging = boost::log;
// namespace src = boost::log::sources;
// namespace sinks = boost::log::sinks;
// namespace keywords = boost::log::keywords;

#include <iostream>

// #include "main.h"

/* Set up global logger */
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(wslogger_t, boost::log::sources::wseverity_logger<boost::log::trivial::severity_level>)

void log_init()
{
    /* Initialise a logging sink that stores log records into a text file. */
    boost::log::add_file_log
    (
        /* Note: Named Parameters */
        // file name pattern
        boost::log::keywords::file_name = "sample_%5N.log"

        // rotate files every 10 MiB
        ,  boost::log::keywords::rotation_size = 10 * 1024 * 1024
        
        // log record format
        , boost::log::keywords::format = "[%TimeStamp%]: %Message%"
        
        // or at midnight
        , boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0)
    );

    // Filter
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
    // Don't forget ...
    boost::log::add_common_attributes();
}

int main(int argc, char* argv[])
{
    std::wclog << L"\nTrivial logging: all log records are written into a file" << std::endl;
    std::wclog << L"Listed in order of severity from lowest to highest\n" << std::endl;

    BOOST_LOG_TRIVIAL(trace)    << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug)    << "A debug severity message";
    BOOST_LOG_TRIVIAL(info)     << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning)  << "A warning severity message";
    BOOST_LOG_TRIVIAL(error)    << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal)    << "A fatal severity message";

    // Filtering can also be applied, a bit complicated though
    using namespace boost::log;

    log_init();

    std::wclog << L"\nThe first two severities won't pass the filter" << std::endl;
    std::wclog << L"Listed in order of severity from lowest to highest\n" << std::endl;
    
    // ctor logger
    // boost::log::sources::wseverity_logger<boost::log::trivial::severity_level> wslogger
    // (
    //     /*default severity level*/
    //     boost::log::keywords::severity = boost::log::trivial::severity_level::info
    // );

    auto wslogger = wslogger_t::get();

    BOOST_LOG_SEV(wslogger, trivial::trace)   << L"A trace severity message";
    BOOST_LOG_SEV(wslogger, trivial::debug)   << L"A debug severity message";

    // explicit severity
    BOOST_LOG_SEV(wslogger, trivial::info)    << L"An informational severity message";

    // implicit severity
    // BOOST_LOG(wslogger)                       << L"An informational severity message, default severity by ctor";
    
    BOOST_LOG_SEV(wslogger, trivial::warning) << L"A warning severity message";
    BOOST_LOG_SEV(wslogger, trivial::error)   << L"An error severity message";
    BOOST_LOG_SEV(wslogger, trivial::fatal)   << L"A fatal severity message";

    return 0;
}
