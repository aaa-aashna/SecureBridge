#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;
using namespace std;

void EncryptFile(const string& inFilename, const string& outFilename, const string& password) {
    AutoSeededRandomPool prng;

    // Step 1: Generate Salt and IV
    byte salt[16], iv[AES::BLOCKSIZE];
    prng.GenerateBlock(salt, sizeof(salt));
    prng.GenerateBlock(iv, sizeof(iv));

    // Step 2: Derive key from password using PBKDF2
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf2;
    pbkdf2.DeriveKey(key, key.size(), 0, (byte*)password.data(), password.size(), salt, sizeof(salt), 10000);

    // Step 3: Encrypt File
    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    FileSource fs(inFilename.c_str(), true,
        new StreamTransformationFilter(encryptor,
            new FileSink(outFilename.c_str())
        )
    );

    // Step 4: Save Salt and IV (prepend to encrypted file)
    ofstream out(outFilename, ios::binary | ios::in | ios::out);
    out.seekp(0, ios::beg);
    out.write((char*)salt, sizeof(salt));
    out.write((char*)iv, sizeof(iv));
    out.close();
}

void DecryptFile(const string& inFilename, const string& outFilename, const string& password) {
    ifstream in(inFilename, ios::binary);

    // Step 1: Read Salt and IV
    byte salt[16], iv[AES::BLOCKSIZE];
    in.read((char*)salt, sizeof(salt));
    in.read((char*)iv, sizeof(iv));

    // Step 2: Derive key
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf2;
    pbkdf2.DeriveKey(key, key.size(), 0, (byte*)password.data(), password.size(), salt, sizeof(salt), 10000);

    // Step 3: Decrypt
    CBC_Mode<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), iv);

    FileSource fs(in, true,
        new StreamTransformationFilter(decryptor,
            new FileSink(outFilename.c_str())
        )
    );
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " <encrypt|decrypt> <input> <output> <password>" << endl;
        return 1;
    }

    string mode = argv[1];
    string inFile = argv[2];
    string outFile = argv[3];
    string password = argv[4];

    if (mode == "encrypt")
        EncryptFile(inFile, outFile, password);
    else if (mode == "decrypt")
        DecryptFile(inFile, outFile, password);
    else
        cout << "Unknown mode: " << mode << endl;

    return 0;
}
