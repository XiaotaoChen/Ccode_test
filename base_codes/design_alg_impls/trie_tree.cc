#include <string>
#include <unordered_set>
#include "../design_algs.h"

namespace design_alg
{
Trie::Trie(): isEnd(false) {
    for (int i=0; i<26; i++) tries[i] = nullptr;
}

void Trie::insert(std::string word) {
    Trie* curr = this;
    for (int i=0; i<word.size(); i++) {
        if (curr->tries[word[i]-'a']== nullptr) {
            curr->tries[word[i]-'a'] = new Trie();
        }
        curr = curr->tries[word[i]-'a'];
    }
    curr->isEnd = true;
}

bool Trie::search(std::string word) {
    Trie* curr = this;
    for (int i=0; i<word.size() && curr != nullptr; i++) {
        curr = curr->tries[word[i]-'a'];
    }
    if (curr==nullptr) return false;
    return curr->isEnd;
}

bool Trie::startsWith(std::string prefix) {
    Trie* curr = this;
    for (int i=0; i<prefix.size() && curr != nullptr; i++) {
        curr = curr->tries[prefix[i]-'a'];
    }
    if (curr==nullptr) return false;
    return true;
}

Trie* Trie::get_trie() {
    return this;
}

bool Trie::is_end() {
    return this->isEnd;
}

Trie** Trie::get_tries() {
    return this->tries;
}


bool Trie::word_dictionary_search(std::string word) {
    Trie* curr = this;
    for (int i=0; i<word.size() && curr != nullptr; i++) {
        if (word[i]!='.') {
            curr = curr->tries[word[i]-'a'];
        }
        else {
            bool isin = false;
            for (int j=0; j<26; j++) {
                if (curr->tries[j]!=nullptr) {
                    isin = curr->tries[j]->word_dictionary_search(word.substr(i+1));
                    if (isin) return true;
                }
            }
            return false;
        }
    }
    if (curr==nullptr) return false;
    return curr->isEnd;
}


} // namespace design_alg
