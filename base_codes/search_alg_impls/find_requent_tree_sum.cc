#include <cstdio>
#include <vector>

#include "../search_algs.h"


int search::treeSum(TreeNode* root, std::map<int, int>& freq, int& max_freq, std::vector<int>& max_freq_sum) {
    if (root == nullptr) return 0;
    int left = treeSum(root->left, freq, max_freq, max_freq_sum);
    int right = treeSum(root->right, freq, max_freq, max_freq_sum);
    int curr_sum = left + right + root->val;
    if (freq.find(curr_sum) == freq.end()) {
        freq[curr_sum] = 1;
    }
    else {
        freq[curr_sum] += 1;
    }
    if (max_freq == freq[curr_sum]) {
        max_freq_sum.push_back(curr_sum);
    }
    else if (max_freq < freq[curr_sum]) {
        max_freq = freq[curr_sum];
        max_freq_sum.clear();
        max_freq_sum.push_back(curr_sum);
    }
    return curr_sum;
}

std::vector<int> search::findFrequentTreeSum(TreeNode* root) {
    std::vector<int> result;
    std::map<int, int> freq;
    int max_freq = 0;
    int sum = treeSum(root, freq, max_freq, result);
    return result;
}