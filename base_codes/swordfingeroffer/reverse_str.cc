#include <string>
#include <vector>

namespace sword_finger_offer
{

std::string reverse_str(std::string& str) {
    if (str.length() < 2) return str;
    std::vector<std::string> vec;
    
    int curr=0;
    for (int i=0; i<str.length(); i++) {
        if (str[i]== ' ') {
            vec.push_back(str.substr(curr, i-curr));
            curr = i+1;
        }
    }
    if (curr!=str.length()) {
        vec.push_back(str.substr(curr));
    }
    int word_num = vec.size();
    std::string result = vec[word_num-1];
    for (int i=word_num-2; i>=0; i--) {
        result = result + (" " + vec[i]);
    }
    return result;
}

} // namespace sword_finger_offer
