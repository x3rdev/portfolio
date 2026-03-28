
#include <atomic>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "web_server/web_server.h"

void usage();

int main() {
    std::cout << "Starting Nicolae Ungur portfolio" << std::endl;

    std::atomic_bool web_server_active(true);
    std::thread web_server_thread(&web_server_loop, std::ref(web_server_active));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::unordered_map<std::string, std::string> index_cache;

    std::string input;
    while (true) {
        std::cout << "> " << std::flush;
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
        }
        if (input == "index") {
            // index("x3rdev");
        } else {
            usage();
        }
    }

    web_server_active.store(false);

    if (web_server_thread.joinable()) {
        web_server_thread.join();
    }

    return 0;
}

void usage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "\"index\" - index github user data" << std::endl;
    std::cout << "\"quit\" - exit the program" << std::endl;
}
