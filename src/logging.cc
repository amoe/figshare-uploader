#include <memory>
#include <string>
#include <QMessageLogger>
#include <QString>
#include "logging.hh"

using std::shared_ptr;
using std::make_shared;

// Don't know what this is
void log_init() {
    QString pattern("%{type} - %{message}");
    qSetMessagePattern(pattern);
}

// A horrible mess.
void configureLogging() {
    auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");
    auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);
    auto logger = shared_ptr<spdlog::logger>(new spdlog::logger("multi_sink", {console_sink, file_sink}));
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
    spdlog::warn("this should appear in both console and file");
    spdlog::info("this message should not appear in the console, only in the file");
}
