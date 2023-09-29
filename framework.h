#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <chrono>
#include <string>
#include <format>
#include <regex>
#include <fstream>
#include <filesystem>
#include <map>
#include <mutex>
#include <condition_variable>
#include <cstdlib>

#include <boost/algorithm/string.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/steady_timer.hpp>

#include <boost/lockfree/spsc_queue.hpp>

template<typename T>
using co_async = boost::asio::awaitable<T>;

#include "plugin.h"
#include "utils.h"
#include "log.h"
#include "config.h"
#include "console.h"
#include "hooks.h"
#include "server.h"
#include "app.h"
