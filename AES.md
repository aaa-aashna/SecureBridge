AES (Rijndael Algorithm)
  Advanced Encryption Standard
  Its a symmetric encryption

1. Start with: 16-byte plaintext block
2. Generate 10 round keys from the 128-bit main key
3. Initial Round:
   - AddRoundKey
4. 9 Main Rounds:
   - SubBytes
   - ShiftRows
   - MixColumns
   - AddRoundKey
5. Final Round:
   - SubBytes
   - ShiftRows
   - AddRoundKey
6. Result: Encrypted ciphertext block (16 bytes)


Step	Purpose
SubBytes	Adds confusion
ShiftRows	Rearranges data
MixColumns	Spreads data across bytes
AddRoundKey	Mixes key with data