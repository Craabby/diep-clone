#define STD2_OPTIONAL_SAFE
#define STD2_VECTOR_SAFE

#include <polynet.hpp>
#include <std/cassert.hh>

int main()
{
    pn::init();
    pn::tcp::Client testClient;
    Assert(!testClient.connect("127.0.0.1", 60006));
    uint32_t oldPacketIndex = 0;
    while (true)
    {
        if (!testClient.is_valid())
            continue;
        char output[8];
        Assert(testClient.recv(output, 8));
        uint32_t packetIndex = *(uint32_t *)output;
        uint32_t packetSize = *(uint32_t *)&output[4];

        if (packetIndex != oldPacketIndex)
        {
            oldPacketIndex = packetIndex;
            char *data = new char[packetSize];
            Assert(testClient.recv(data, packetSize));
            for (uint32_t i = 0; i < packetSize; i++)
                std::cout << std::to_string(data[i]) << ' ';
            std::cout << std::endl;
            delete[] data;
        }
    }
}
