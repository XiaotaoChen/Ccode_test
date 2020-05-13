#include <sstream>
#include <string>
#include <iostream>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void serialize_dfs(TreeNode* root, std::string& oss) {
    if (root == nullptr) {
        oss += '#';
        return;
    }
    oss += std::to_string(int(root->val));
    serialize_dfs(root->left, oss);
    serialize_dfs(root->right, oss);
}

std::string serialize(TreeNode* root) {
    std::string oss="";
    serialize_dfs(root, oss);
    return oss;
}

void deserialize_dfs(std::string& oss, TreeNode** root, int& idx) {
    idx++;
    if (idx> oss.length()) return;
    if (oss[idx-1] == '#' ) {
        *root = nullptr;
        return;
    }
    *root = new TreeNode(oss[idx-1]-'0');
    deserialize_dfs(oss, &((*root)->left), idx);
    deserialize_dfs(oss, &((*root)->right), idx);
}

TreeNode* deserialize(std::string& oss) {
    TreeNode* root = nullptr;
    int idx = 0;
    deserialize_dfs(oss, &root, idx);
    return root;
}

void print_bst(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->val << " ";
    print_bst(root->left);
    print_bst(root->right);
}


void serialize_ss(TreeNode* root, std::ostream& oss) {
    if (root == nullptr) {
        oss << "#,";
        return;
    }
    oss << int(root->val) << ',';
    serialize_ss(root->left, oss);
    serialize_ss(root->right, oss);
}

bool ReadStream(std::istream& stream, int* number)
{
    if(stream.eof())
        return false;

    char buffer[32];
    buffer[0] = '\0';

    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }

    bool isNumeric = false;
    if(i > 0 && buffer[0] != '#')
    {
        *number = std::atoi(buffer);
        isNumeric = true;
    }

    return isNumeric;
}

void deserialize_ss(TreeNode** root, std::istream& iss) {
    int number;
    if (ReadStream(iss, &number)) {
        *root = new TreeNode(number);
        deserialize_ss(&((*root)->left), iss);
        deserialize_ss(&((*root)->right), iss);
    }
}


} // namespace sword_finger_offer
