// em++ ../Client/src/main.cc ../Client/src/Rendering/Canvas.cc -I../Client/include -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=3 -s MIN_WEBGL_VERSION=2 -s USE_GLFW=3 -o diep-client.html

#include <cstdint>
#include <iostream>
#include <vector>
#include <thread>

#include <Socket/Socket.hh>

int32_t main(int32_t argc, char **argv)
{
    client::Socket socket(
        "ws://localhost:8001/", [](const std::vector<uint8_t> &data)
        {
            std::cout << " > "; 
            std::cout << std::to_string(data.size()) << std::endl;
            for (uint8_t byte : data)
            {
                std::cout << std::to_string(byte) << " ";
            } },
        []()
        {
            std::cout << "socket opened" << std::endl;
        });

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000000000s);
}
