//merkle1.cpp
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
    // Transactions hashes from a block (#95 000) to reproduce the same merkle root
    bc::hash_list tx_hashes{{
        bc::hash_literal("82623ec828f8db0a311202fc65789c93212d641b9986f6a2ea213d4564eb1e0f"),
        bc::hash_literal("3500b0e3452e801e648a0aff1a5a7bd6f2c3f9ce26fd4b1920a391e18d1f9d53"),
    }};
    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    std::cout << "Merkle Root Hash: " << bc::encode_base16(merkle_root) << std::endl;
    std::cout << "Merkle Root Hash-2: " << bc::encode_hash(merkle_root) << std::endl;
    // Merkle root hash   -> bb9f3f5820a7cb932f8799ed933afabd0598ddc6962eb3cdc0249d9a7948ae94
    // Merkle root hash-2 -> 94ae48799a9d24c0cdb32e96c6dd9805bdfa3a93ed99872f93cba720583f9fbb

    return 0;
}
