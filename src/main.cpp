#include <opendht.h>
#include <vector>
#include <libavcodec/avcodec.h>

dht::DhtRunner node;

void initNode() {
    // Launch on a new thread, using a
    // generated RSA key pair, and listen on port 4222.
    node.run(4222, dht::crypto::generateIdentity(), true);

    std::cout << "OpenDHT Node " << node.getNodeInfo().node_id << "\n";

    // Join the network through any running node,
    // here using a known bootstrap node.
    node.bootstrap("0.0.0.0", "53257");
}

int uploadFile(char *path) {
    // Partition, and store a file in the network

    // Divide file into 64 KiB chunks

    // Encode chunks

    // Assign metadata

    // Upload
}

int fileSearch() {
    // TODO
}

int main()
{

    initNode();

    // put some data on the dht
    std::vector<uint8_t> some_data(5, 10);
    node.put("test123", some_data);

    // wait for dht threads to end
    while(1);

    node.join();
    return 0;
}
