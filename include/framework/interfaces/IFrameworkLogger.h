#pragma once

#include <fmt/format.h>
#include "../Common.h"
#include "../Service.h"
#include "LogLevel.h"

namespace Cppelix {
    class IFrameworkLogger : virtual public IService {
    public:
        virtual void trace(const char *filename_in, int line_in, const char *funcname_in, std::string_view format_str, fmt::format_args args) = 0;
        virtual void debug(const char *filename_in, int line_in, const char *funcname_in, std::string_view format_str, fmt::format_args args) = 0;
        virtual void info(const char *filename_in, int line_in, const char *funcname_in, std::string_view format_str, fmt::format_args args) = 0;
        virtual void warn(const char *filename_in, int line_in, const char *funcname_in, std::string_view format_str, fmt::format_args args) = 0;
        virtual void error(const char *filename_in, int line_in, const char *funcname_in, std::string_view format_str, fmt::format_args args) = 0;

        virtual void setLogLevel(LogLevel level) = 0;
        [[nodiscard]] virtual LogLevel getLogLevel() const = 0;

        static constexpr InterfaceVersion version = InterfaceVersion{1, 0, 0};
    protected:
        ~IFrameworkLogger() override = default;
    };

#ifndef REMOVE_SOURCE_NAMES_FROM_LOGGING
#define LOG_TRACE(logger, str, ...) if(logger != nullptr) logger->trace(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), str, fmt::make_format_args(__VA_ARGS__))
#define LOG_DEBUG(logger, str, ...) if(logger != nullptr) logger->debug(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), str, fmt::make_format_args(__VA_ARGS__))
#define LOG_INFO(logger, str, ...) if(logger != nullptr) logger->info(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), str, fmt::make_format_args(__VA_ARGS__))
#define LOG_WARN(logger, str, ...) if(logger != nullptr) logger->warn(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), str, fmt::make_format_args(__VA_ARGS__))
#define LOG_ERROR(logger, str, ...) if(logger != nullptr) logger->error(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), str, fmt::make_format_args(__VA_ARGS__))
#else
#define LOG_TRACE(logger, str, ...) if(logger != nullptr) logger->trace(nullptr, 0, nullptr, str, fmt::make_format_args(__VA_ARGS__))
#define LOG_DEBUG(logger, str, ...) if(logger != nullptr) logger->debug(nullptr, 0, nullptr, str, fmt::make_format_args(__VA_ARGS__))
#define LOG_INFO(logger, str, ...) if(logger != nullptr) logger->info(nullptr, 0, nullptr, str, fmt::make_format_args(__VA_ARGS__))
#define LOG_WARN(logger, str, ...) if(logger != nullptr) logger->warn(nullptr, 0, nullptr, str, fmt::make_format_args(__VA_ARGS__))
#define LOG_ERROR(logger, str, ...) if(logger != nullptr) logger->error(nullptr, 0, nullptr, str, fmt::make_format_args(__VA_ARGS__))
#endif
}