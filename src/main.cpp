#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // From <boost/beast.hpp>
namespace http = beast::http;       // From <boost/beast/http.hpp>
namespace json = boost::json;
namespace net = boost::asio;        // From <boost/asio.hpp>
using tcp = net::ip::tcp;           // From <boost/asio/ip/tcp.hpp>

void http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
    acceptor.async_accept(socket, [&](boost::system::error_code ec) {
        if (!ec) {
            beast::flat_buffer buffer;

            http::request<http::string_body> req;
            http::read(socket, buffer, req);


            // check the request target 
            if (req.target() == "/api/status") {
                json::object response = {
                    {"status", "running"},
                    {"timestamp", json::string(std::to_string(std::time(nullptr)))},
                    {"version", "0.1.0"}
                };

                http::response<http::string_body> res{
                    http::status::ok, req.version()
                };
                res.set(http::field::server, "Beast");
                res.set(http::field::content_type, "application/json");
                res.body() = json::serialize(response);
                res.prepare_payload();
                http::write(socket, res);
            } else {
                http::response<http::string_body> res{
                    http::status::ok, req.version()
                };
                res.set(http::field::server, "Beast");
                res.set(http::field::content_type, "text/html");
                res.body() = "<html><body><h1>Welcome to Blogging Software!</h1></body></html>";
                res.prepare_payload();

                http::write(socket, res);
            }
        }

        socket.shutdown(tcp::socket::shutdown_send, ec);
    });
}

int main() {
    try {
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};
        tcp::socket socket{ioc};

        std::cout << "Server is running on http://localhost:8080" << std::endl;

        http_server(acceptor, socket);
        ioc.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
