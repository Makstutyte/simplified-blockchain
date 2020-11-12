# simplified-blockchain

Self-made blockchain version v0.2, 
program written in C++ 

## Installation instructions
To run the program code you need:

1. Download the program code
2. Install the C ++ compiler
 <br />[GCC](https://gcc.gnu.org/)
3. Find the location of the program code (directory) using the command line

### If using Makefile:

4. Compile program code using
   <br /> `make` 
5. Run the program code using
   <br /> `test` 
   
### If not using Makefile:

4. Compile program code using
   <br /> `g++ -c block.cpp` 
   <br /> `g++ -o test block.o` 
5. Run the program code using
   <br /> `test` 

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
  * Merkel Root Hash
  * Nonce - a random number that has been used for a hash of the required complexity (defined by the number of consecutive zeros at the beginning)
  * Difficulty Target - defines numbers of previously mentioned zeros
  

 | Version | Amount of blocks |Time |
| --------------- |  --------------- |--------------- |
| v0.1 | 4 | 18.9175 s |
| v0.2 | 4 | 66.1762 s |
| v0.1 | 10 | 121.395 s |
| v0.2 | 10 | 357.903 s |
