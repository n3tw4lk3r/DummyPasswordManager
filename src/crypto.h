#pragma once

#include <iostream>
#include <string>
#include <random>
#include <algorithm>

enum class type{
    all_letters = 0,
    only_int = 1,
    someone_letters = 2
};

std::string hash(const std::string& input);
std::string encrypt(const std::string& input, const std::string& key);
std::string decrypt(const std::string& input, const std::string& key);
std::string generateRandomPassword(type t = type::someone_letters, size_t length = 30);
std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);
