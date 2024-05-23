#include <crypto.h>

std::string hash(const std::string input) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(input));
}

std::string encrypt(const std::string& input, const std::string& key) {
    std::cout << "encrypt called\n";
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
}

std::string decrypt(const std::string& input, const std::string& key) {
    return encrypt(input, key);
}

std::string generateRandomPassword(type t, size_t length) {
    std::string result;
    result.resize(length);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist;
    if (t == type::only_int) {
        dist = std::uniform_int_distribution<int>(static_cast<int>('0'), static_cast<int>('9'));
    } else if (t == type::all_letters){
        dist = std::uniform_int_distribution<int>(static_cast<int>(' '), static_cast<int>('~'));
    } else{
        dist = std::uniform_int_distribution<int>(static_cast<int>('A'), static_cast<int>('}'));
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = static_cast<char>(dist(mt));
    }

    return result;
}

std::string base64_encode(const std::string &in) {

    std::string out;

    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

std::string base64_decode(const std::string &in) {

    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val=0, valb=-8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}
