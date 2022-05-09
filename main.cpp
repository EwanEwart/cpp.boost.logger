// #define BOOST_ALL_DYN_LINK 1
// #define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp> // boost::log::add_file_log
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

// namespace logging = boost::log;
// namespace src = boost::log::sources;
// namespace sinks = boost::log::sinks;
// namespace keywords = boost::log::keywords;

#include <iostream>

// #include "main.h"

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
    std::clog << "\nTrivial logging: all log records are written into a file" << std::endl;
    std::clog << "Listed in order of severity from lowest to highest\n" << std::endl;

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    // Filtering can also be applied, a bit complicated though
    using namespace boost::log;

    log_init();

    std::clog << "\nThe first two severities won't pass the filter" << std::endl;
    std::clog << "Listed in order of severity from lowest to highest\n" << std::endl;
    
    boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;

    BOOST_LOG_SEV(logger, trivial::trace) << "A trace severity message";
    BOOST_LOG_SEV(logger, trivial::debug) << "A debug severity message";
    BOOST_LOG_SEV(logger, trivial::info) << "An informational severity message";
    BOOST_LOG_SEV(logger, trivial::warning) << "A warning severity message";
    BOOST_LOG_SEV(logger, trivial::error) << "An error severity message";
    BOOST_LOG_SEV(logger, trivial::fatal) << "A fatal severity message";

    return 0;
}
