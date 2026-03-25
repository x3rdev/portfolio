//
// Created by nicol on 3/21/2026.
//

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <iostream>

#include "indexer.h"



using asio::ip::tcp;

bool github_request(const std::string& path, std::string* result);

void index(const std::string& profile) {
    std::string profile_query;
    github_request("users/"+profile+"/repos", &profile_query);
    std::cout << profile_query << std::endl;
}

bool github_request(const std::string& path, std::string* result) {
    try {
        asio::io_context io;

        asio::ssl::context ctx(asio::ssl::context::sslv23_client);
        ctx.set_default_verify_paths();

        asio::ssl::stream<tcp::socket> ssl_socket(io, ctx);

        tcp::resolver resolver(io);
        auto endpoints = resolver.resolve("api.github.com", "443");

        asio::connect(ssl_socket.next_layer(), endpoints);

        ssl_socket.handshake(asio::ssl::stream_base::client);

        asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET /" << path << " HTTP/1.1\r\n";
        request_stream << "Host: api.github.com\r\n";
        request_stream << "User-Agent: portfolio\r\n";
        request_stream << "Accept: application/json\r\n";
        request_stream << "Connection: close\r\n\r\n";

        asio::write(ssl_socket, request);

        asio::streambuf response;
        asio::read_until(ssl_socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string http_version;
        unsigned int status_code;
        std::string status_message;

        response_stream >> http_version >> status_code;
        std::getline(response_stream, status_message);

        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            std::cerr << "Invalid response\n";
            return false;
        }

        if (status_code != 200) {
            std::cerr << "GitHub returned status code " << status_code << "\n";
            return false;
        }

        // Read headers
        asio::read_until(ssl_socket, response, "\r\n\r\n");
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            // You can process headers here if needed
        }

        // Read the remaining body
        std::ostringstream body_stream;
        if (response.size() > 0)
            body_stream << &response;

        std::error_code error;
        while (asio::read(ssl_socket, response, asio::transfer_at_least(1), error)) {
            body_stream << &response;
        }
        if (error != asio::error::eof) {
            throw std::system_error(error);
        }

        *result = body_stream.str();
        return true;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }
}