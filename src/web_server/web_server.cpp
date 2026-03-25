//
// Created by nicol on 3/21/2026.
//

#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

using asio::ip::tcp;

std::string build_response(const std::string& body, const std::string& content_type = "text/html");
std::string handle_request(const std::string& request);
bool load_file(const std::string& path, std::string& contents);

void web_server_loop(const std::atomic_bool& web_server_active) {
    try {
        asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
        acceptor.non_blocking(true);

        std::cout << "Server running on http://localhost:8080\n";

        while (web_server_active.load()) {
            std::error_code ec;
            tcp::socket socket(io);

            acceptor.accept(socket, ec);
            if (ec == asio::error::would_block || ec == asio::error::try_again) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }
            if (ec) {
                continue;
            }

            std::array<char, 4096> buffer{};
            size_t bytes_read = socket.read_some(asio::buffer(buffer), ec);
            if (ec && ec != asio::error::eof) {
                continue;
            }

            std::string request(buffer.data(), bytes_read);
            std::string response = handle_request(request);

            asio::write(socket, asio::buffer(response), ec);
            socket.shutdown(tcp::socket::shutdown_both, ec);
            socket.close(ec);
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}

std::string build_response(const std::string& body, const std::string& content_type) {
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: " << content_type << "\r\n";
    response << "Content-Length: " << body.size() << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << body;
    return response.str();
}

bool load_file(const std::string& path, std::string& contents) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return false;
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    contents = buffer.str();
    return true;
}

std::string handle_request(const std::string& request) {
    const auto line_end = request.find("\r\n");
    const std::string request_line = request.substr(0, line_end);

    std::istringstream parser(request_line);
    std::string method;
    std::string target;
    parser >> method >> target;

    if (method != "GET") {
        return build_response("<h1>405 Method Not Allowed</h1>");
    }

    std::string file_path;
    std::string content_type = "text/html";
    if (target == "/" || target == "/index.html") {
        file_path = "../resources/index.html";
        content_type = "text/html";
    } else if (target == "/styles.css") {
        file_path = "../resources/styles.css";
        content_type = "text/css";
    } else if (target == "/app.js") {
        file_path = "../resources/app.js";
        content_type = "application/javascript";
    } else {
        return build_response("<h1>404 Not Found</h1>");
    }

    std::string body;
    if (!load_file(file_path, body)) {
        return build_response("<h1>404 Not Found</h1>");
    }

    return build_response(body, content_type);
}