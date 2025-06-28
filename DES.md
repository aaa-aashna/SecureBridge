DES 
     (Data Encryption Standard)
Its a symmetric key algorithm using "block by block" encrytpion 

Symmetric key: Same key is used for both encryption and decryption
Block cipher: Operates on fixed-size chunks (blocks) of data
BLOCK SIZE : 64 BITS 
KEY SIZE   : 48 BITS


HOW IT WORKS 
The data is split into two halves (Left & Right)

Each round:

     Expands the right half from 32 to 48 bits using an expansion function

     XORs it with a 48-bit round key (derived from the main 56-bit key)

     Passes it through S-boxes (Substitution boxes) to shrink it back to 32 bits

     Applies a permutation and then mixes with the left half

     Swaps halves at the end of each round


## DES Round Process 

Initial 64-bit Block
│
▼
Split into Two Halves (Left - 32 bits, Right - 32 bits)
│
▼
For Each of 16 Rounds:
┌─────────────────────────────────────────────────────────────┐
│ │
│ 1. Expand Right half (32 → 48 bits) │
│ 2. XOR with 48-bit Round Key │
│ 3. Pass through 8 S-boxes (48 → 32 bits) │
│ 4. Permute the result (P-box permutation) │
│ 5. XOR with Left half │
│ 6. Swap Left and Right halves │
│ │
└─────────────────────────────────────────────────────────────┘
│
▼
After 16 Rounds → Swap final halves
│
▼
Final Permutation (Inverse of Initial Permutation)
│
▼
Encrypted 64-bit Ciphertext Block



MODES OF OPERATION
  Electronic Codebook
  Cipher Block Chaining 
  Cipher feedback Block
  Output block

         
