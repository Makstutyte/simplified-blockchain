# simplified-blockchain

Self-made blockchain version v0.3 with implemented Merkle tree function create_merkle() from libbitcoin.  
Program written in C++ 

## Installation instructions
To run the program code you need:

1. Download the program code
2. Install the C ++ compiler
  <br /> `sudo apt-get update`
  <br /> `sudo apt-get install build-essential manpages-dev`
3. Find the location of the program code (directory) using the command line
4. Compile program code using
   <br /> `g++ -std=c++11 -o block block.cpp $(pkg-config --cflags --libs libbitcoin)` 
   
   or
   <br /> `clang++ -std=c++11 -o block block.cpp $(pkg-config --cflags --libs libbitcoin)` 
5. Run the program code using
   <br /> `./block` 


### The written program performs the following actions:
* Generates ~ 1000 network users with three attributes:
  * name
  * public key
  * balance
* Generates a pool of ~ 10,000 new transactions not yet placed in any block, and transactions have four attributes:
  * transaction ID (hash of other transaction fields)
  * sender (users public key)
  * recipient (users public key)
  * sum
* Transaction verification
  * It is secured that the same transaction is not repeated in the same block
  * Balance check: if user A sends a certain amount to user B, but senders balance is less than the amount to be transfered, that transaction is deleted from the transaction pool
  * Transaction hash check: it is checked whether the transaction information hash matches transaction ID, if not - the transaction is deleted from the transaction pool
* Generates five potential block candidates with near hundred transactions
  * When generating potencial block transactions are chosen randomly
* Randomly selects one of the five generated potential block candidates and mines it until if fulfills Proof of Work quality within 5 seconds
* If block is mined - it is added to the blockchain, if not the process is repeated with another randomly chosen potential block
* When block is added used transactions are deleted from transaction pool 

### Generated block contains:
* Block header
  * Previous Block Hash
  * Current Block Hash
  * Timestamp
  * Version - version of the data structure used for the blocks (for example "first")
  * Merkle Root Hash
  * Nonce - a random number that has been used for a hash of the required complexity (defined by the number of consecutive zeros at the beginning)
  * Difficulty Target - defines numbers of previously mentioned zeros
  

 | Version | Amount of blocks |Time |
| --------------- |  --------------- |--------------- |
| v0.1 | 4 | 18.9175 s |
| v0.2 | 4 | 66.1762 s |
| v0.3 | 4 | 85.4312 s |
| v0.1 | 10 | 121.395 s |
| v0.2 | 10 | 357.903 s |
| v0.3 | 10 | 462.1187 s |


### Merkle function test files
* file merkle.cpp calculates merkle root hash from block (#100 000) transactions  
  * output → 6657a9252aacd5c0b2940996ecff952228c3067cc38d4885efb5a4ac4247e9f3
* file merkle1.cpp calculates merkle root hash from block (#95 000) transactions  
  * output → bb9f3f5820a7cb932f8799ed933afabd0598ddc6962eb3cdc0249d9a7948ae94
* file merkle2.cpp calculates merkle root hash from block (#1000) transactions  
  * output → 338f121232e169d3100edd82004dc2a1f0e1f030c6c488fa61eafa930b0528fe
