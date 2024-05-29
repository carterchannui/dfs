#include <opendht.h>
#include <vector>
#include <memory>
#include <numeric>
#include <iostream>
#include <libavcodec/avcodec.h>
#include <openssl/sha.h>

dht::DhtRunner node;
const size_t CHUNK_SIZE = 64000; // ~64KiB

std::vector<std::vector<uint8_t>> partition_video(const std::string& filename) {
    std::string ffmpeg_command = "ffmpeg -i " + filename + " -vcodec libx264 " + "encoded_" + filename;
    std::system(ffmpeg_command.c_str()); // Encode file using H264 codec

    std::ifstream file("encoded_" + filename, std::ios::binary);
    std::vector<std::vector<uint8_t>> chunks;

    if (file.is_open()) {
        while (!file.eof()) {
            std::vector<uint8_t> chunk(CHUNK_SIZE);
            file.read(reinterpret_cast<char*>(chunk.data()), CHUNK_SIZE);
            chunk.resize(file.gcount()); // Resize to actual data read
            if (!chunk.empty()) {
                chunks.push_back(chunk);
            }
        }
        file.close();
    }

    return chunks;
}

dht::InfoHash compute_content_hash(const std::vector<uint8_t>& data) {
    return dht::InfoHash::get(data);
}

std::vector<dht::InfoHash> create_file_key(const std::vector<std::vector<uint8_t>>& chunks) {
    std::vector<dht::InfoHash> file_key;

    for (const auto& chunk : chunks) {
        file_key.push_back(compute_content_hash(chunk));
    }

    return file_key;
}

void upload_chunks(dht::DhtRunner& node, const std::vector<std::vector<uint8_t>>& chunks) {
    size_t total_chunks = chunks.size();
    size_t uploaded_chunks = 0;

    for (const auto& chunk : chunks) {
        dht::InfoHash hash = compute_content_hash(chunk);
        node.put(hash, chunk);
        
        // Update and print progress
        uploaded_chunks++;
        std::cout << "Uploaded " << uploaded_chunks << " of " << total_chunks << " chunks (" 
                  << (uploaded_chunks * 100 / total_chunks) << "%)" << std::endl;
    }
}

std::vector<uint8_t> retrieve_chunk(dht::DhtRunner& node, const dht::InfoHash& hash) {
    std::vector<uint8_t> chunk;
    auto future_values = node.get(hash);

    // Wait for the future to complete
    auto values = future_values.get();

    if (!values.empty()) {
        chunk = values[0]->data;
    }

    return chunk;
}

std::vector<std::vector<uint8_t>> retrieve_video(dht::DhtRunner& node, const std::vector<dht::InfoHash>& file_key) {
    std::vector<std::vector<uint8_t>> chunks;
    size_t total_chunks = file_key.size();
    size_t retrieved_chunks = 0;

    for (const auto& hash : file_key) {
        chunks.push_back(retrieve_chunk(node, hash));

        // Update and print progress
        retrieved_chunks++;
        std::cout << "Retrieved " << retrieved_chunks << " of " << total_chunks << " chunks (" 
                  << (retrieved_chunks * 100 / total_chunks) << "%)" << std::endl;
    }

    return chunks;
}

int main(int argc, char* argv[])
{
    
    dht::DhtRunner node;
    node.run(4222, dht::crypto::generateIdentity(), true);
    node.bootstrap("0.0.0.0", argv[1]);

    std::string filename = "video_file.mp4";
    auto chunks = partition_video(filename);
    auto file_key = create_file_key(chunks);

    // Upload chunks
    upload_chunks(node, chunks);

    // Retrieve chunks
    auto retrieved_chunks = retrieve_video(node, file_key);

    printf("Retrieved\n");

    // Combine chunks into a single file
    std::ofstream out_file("retrieved_video.mp4", std::ios::binary);
    for (const auto& chunk : retrieved_chunks) {
        out_file.write(reinterpret_cast<const char*>(chunk.data()), chunk.size());
    }

    out_file.close();

    node.join();
    return 0;
}
