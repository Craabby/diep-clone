#define STD2_OPTIONAL_SAFE
#define STD2_VECTOR_SAFE

#include <polynet.hpp>

int main()
{
    pn::init();
    pn::tcp::Client testClient;
    testClient.connect("127.0.0.1", 60006);
    uint32_t oldPacketIndex = 0;
    while (true)
    {
        if (testClient.is_valid()) // always false
            continue;
        char output[8];
        testClient.recv(output, 8);
        uint32_t packetIndex = *(uint32_t *)output;
        uint32_t packetSize = *(uint32_t *)&output[4];

        if (packetIndex != oldPacketIndex)
        {
            oldPacketIndex = packetIndex;
            char *data = new char[packetSize];
            testClient.recv(data, packetSize);
            for (uint32_t i = 0; i < packetSize; i++)
                std::cout << data[i];
            std::cout << std::endl;
            delete[] data;
        }
    }
}
