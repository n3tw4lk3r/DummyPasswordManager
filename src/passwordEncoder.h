#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <string>

using password = std::string;
using name_of_group = std::string;
using group_of_passwords = std::map<std::string, std::string>;

std::map<name_of_group, group_of_passwords> decode(std::string toDecode_);
std::string encode(std::map<name_of_group, group_of_passwords>& groups);
