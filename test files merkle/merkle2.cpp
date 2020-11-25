//merkle.cpp
#include <bitcoin/bitcoin.hpp>
// Merkle Root Hash
bc::hash_digest create_merkle(bc::hash_list& merkle)
{
    // Stop if hash list is empty or contains one element
    if (merkle.empty())
    return bc::null_hash;
    else if (merkle.size() == 1)
    return merkle[0];
    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1)
    {
        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0)
        merkle.push_back(merkle.back());
        // List size is now even.
        assert(merkle.size() % 2 == 0);
        // New hash list.
        bc::hash_list new_merkle;
        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
            decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            // Add this to the new list.
            new_merkle.push_back(new_root);
        }
        // This is the new list.
        merkle = new_merkle;
        // DEBUG output -------------------------------------
        std::cout << "Current merkle hash list:" << std::endl;
        for (const auto& hash: merkle)
        std::cout << " " << bc::encode_base16(hash) << std::endl;
        std::cout << std::endl;
        // --------------------------------------------------
    }
    // Finally we end up with a single item.
    return merkle[0];
}
int main()
{
    // Transactions hashes from a block (#1000) to reproduce the same merkle root
    bc::hash_list tx_hashes{{
        bc::hash_literal("fe28050b93faea61fa88c4c630f0e1f0a1c24d0082dd0e10d369e13212128f33"),
    }};
    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    std::cout << "Merkle Root Hash: " << bc::encode_base16(merkle_root) << std::endl;
    std::cout << "Merkle Root Hash-2: " << bc::encode_hash(merkle_root) << std::endl;
    // Merkle root hash   -> 338f121232e169d3100edd82004dc2a1f0e1f030c6c488fa61eafa930b0528fe
    // Merkle root hash-2 -> fe28050b93faea61fa88c4c630f0e1f0a1c24d0082dd0e10d369e13212128f33

    return 0;
}
