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
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/url/url_view.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

template<typename T>
using co_async = boost::asio::awaitable<T>;

#define DECLARE_EVENT_SINK(ev)																						\
    class ev##Sink : public BSTEventSink<ev> {																		\
    public:																											\
        virtual EventResult ProcessEvent(const ev&, BSTEventSource<ev>*);											\
    };																												\

#define REGISTER_EVENT_SINK(ev)																						\
    static auto _##ev##Sink = ev##Sink();																			\
    GetEventSource<ev>()->RegisterSink(&_##ev##Sink);																\

#define IMPLEMENT_EVENT_SINK_BEGIN(ev)																				\
    EventResult ev##Sink::ProcessEvent(const ev& arEvent, BSTEventSource<ev>* eventSource) {						\

#define IMPLEMENT_EVENT_SINK_END(ev)																				\
        return BSTEventSink<ev>::ProcessEvent(arEvent, eventSource);												\
    }																												\

#define DECLARE_EVENT_SINK2(ev, nm)																					\
    class nm##Sink : public BSTEventSink<ev> {																		\
    public:																											\
        virtual EventResult ProcessEvent(const ev&, BSTEventSource<ev>*);											\
    };																												\

#define REGISTER_EVENT_SINK2(ev, nm)																				\
    static auto _##nm##Sink = nm##Sink();																			\
    GetEventSource<ev>()->RegisterSink(&_##nm##Sink);																\

#define IMPLEMENT_EVENT_SINK_BEGIN2(ev, nm)																			\
    EventResult nm##Sink::ProcessEvent(const ev& arEvent, BSTEventSource<ev>* eventSource) {						\

#define IMPLEMENT_EVENT_SINK_END2(ev, nm)																			\
        return BSTEventSink<ev>::ProcessEvent(arEvent, eventSource);												\
    }																												\

#include "plugin.h"
#include "utils.h"
#include "log.h"
#include "config.h"
#include "console.h"
#include "hooks.h"
#include "server.h"
#include "app.h"
