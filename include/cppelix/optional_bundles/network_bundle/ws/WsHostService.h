#pragma once

#ifdef USE_BOOST_BEAST

#include <cppelix/optional_bundles/network_bundle/IHostService.h>
#include <cppelix/optional_bundles/logging_bundle/Logger.h>
#include <cppelix/optional_bundles/network_bundle/ws/WsConnectionService.h>
#include <cppelix/optional_bundles/network_bundle/ws/WsEvents.h>
#include <thread>
#include <boost/beast.hpp>
#include <boost/asio/spawn.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace Cppelix {
    class WsHostService final : public IHostService, public Service {
    public:
        WsHostService(DependencyRegister &reg, CppelixProperties props);
        ~WsHostService() final = default;

        bool start() final;
        bool stop() final;

        void addDependencyInstance(ILogger *logger);
        void removeDependencyInstance(ILogger *logger);

        Generator<bool> handleEvent(NewWsConnectionEvent const * const evt);

        void setPriority(uint64_t priority) final;
        uint64_t getPriority() final;

    private:
        void fail(beast::error_code, char const* what);
        void listen(tcp::endpoint endpoint, net::yield_context yield);

        std::unique_ptr<net::io_context> _wsContext{};
        std::atomic<uint64_t> _priority{INTERNAL_EVENT_PRIORITY};
        std::atomic<bool> _quit{};
        std::thread _listenThread{};
        ILogger *_logger{nullptr};
        std::vector<WsConnectionService*> _connections{};
        std::unique_ptr<EventHandlerRegistration> _eventRegistration{};
    };
}

#endif