#include "password_decoder.h"
std::map<name_of_group, group_of_passwords> decode(std::string toDecode_) {
    std::map<name_of_group, group_of_passwords> groups;
    int l = 1, r, num;
    bool in_group = false;
    std::string group_key, key;
    std::function<std::string()> get_string = [&]() {
        std::string st;
        r = l + 1;
        while (toDecode_[r] != ':') ++r;
        num = stoi(toDecode_.substr(l, r - l));
        st = toDecode_.substr(r + 1, num);
        l = r + num + 1;
        return st;
    };
    while (l < toDecode_.size() - 1) {
        if (toDecode_[l] == 'e') {
            in_group = false;
            ++l;
            continue;
        }
        if (in_group) {
            key = get_string();
        }
        else {
            group_key = get_string();
            in_group = true;
        }
        if (toDecode_[l] == 'd') {
            ++l;
        }
        else {
            groups[group_key][key] = get_string();
        }
    }
    return groups;
}

std::string encode (std::map<name_of_group, group_of_passwords>& groups) {
    std::string ans;
    ans += 'd';
    for(auto& x: groups) {
        ans += std::to_string(x.first.size()) + ':' + x.first + 'd';
        for(auto& y: x.second) {
            ans += std::to_string(y.first.size()) + ':' + y.first;
            ans += std::to_string(y.second.size()) + ':' + y.second;
        }
        ans +='e';
    }
    ans += 'e';
    return ans;
}
