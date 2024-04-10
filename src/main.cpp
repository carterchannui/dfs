#include <opendht.h>
#include <vector>

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

int uploadFile() {
    // Partition, and store a file in the network
    // Update keyword tables
}

int main()
{

    initNode();

    // put some data on the dht
    std::vector<uint8_t> some_data(5, 10);
    node.put("test123", some_data);

    // node.put("test_image", buffer);

    // put some data on the dht, signed with our generated private key
    // node.putSigned("unique_key_42", some_data);

    // get data from the dht
    // node.get("other_unique_key", [](const std::vector<std::shared_ptr<dht::Value>>& values) {
    //     // Callback called when values are found
    //     for (const auto& value : values)
    //         std::cout << "Found value: " << *value << std::endl;
    //     return true; // return false to stop the search
    // });

    // get file

    // node.get("test_image", [](const std::vector<std::shared_ptr<dht::Value>>& values) {
    //     for (const auto& value : values) {
    //         if (value) {
    //             // Create a binary file
    //             std::ofstream ofile("output_file.jpg", std::ios::binary);

    //             // Write the data from the Value object to the file
    //             ofile.write(reinterpret_cast<const char*>(value->data.data()), value->data.size());

    //             std::cout << "Value saved to 'output_file'" << std::endl;
    //         }
    //     }
    //     return true;
    // });

    // wait for dht threads to end
    while(1);

    node.join();
    return 0;
}
