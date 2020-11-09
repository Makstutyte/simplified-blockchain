# simplified-blockchain

Self-made blockchain version v0.1, 
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
* Generates a block with hundred transactions and adds it to the blockchain

### Generated block contains:
* Block header
  * Previous Block Hash
  * Timestamp
  * Version - version of the data structure used for the blocks (for example "first")
  * Merkel Root Hash - NOT COMPLETED
  * Nonce - a random number that has been used for a hash of the required complexity (defined by the number of consecutive zeros at the beginning)
  * Difficulty Target - defines numbers of previously mentioned zeros
  
The provided version is in need for improvement by adding merkel root.

* v0.1 four block generation lasted 29.5812 s
* v0.2 four block generation lasted 2061.76 s
