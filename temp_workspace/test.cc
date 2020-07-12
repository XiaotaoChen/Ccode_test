#include <string>
#include <vector>
#include <iostream>
#include "./algorithms.h"
#include "./base_struct.h"

struct point
{
    int x, y;
    point():x(0), y(0){}
    point(int a, int b):x(a), y(b){}
    void print() {
        printf("point:(%d, %d)\n", x, y);
    }
};

/**
 * 路径总和
 * 思路：　dfs求解．刚开始只考虑到一层ｄｆｓ，导致逻辑有点错误．
 * １．　dfs(root->left, target, cnt), dfs(root->right, target , cnt)
 * 然后　dfs(root->left, target - root->val, cnt), 
 *      dfs(root->right, target-root->val, cnt)
 * 该重dfs其实是结果等于target或target-root->val的结果．而不是结果为target的结果．
 * 应该两层dfs. 第一层　
 * dfs(root, sum, cnt), 
 * dfs(root->left, sum, cnt), 
 * dfs(root->right, sum, cnt)
 * 第二层dfs:
 * dfs_two(root->left, sum-root->val, cnt)
 * dfs_two(root->right, sum-root->val, cnt)
 * 
*/
void test_pathsum() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);
    int target = 8;
    int result = algorithms::pathSum(root, target);
    std::cout << "test pathsum result: " << result << std::endl;
}


int main() {
    // point p1 = point(1,2);
    // p1.print();

    test_pathsum();

    return 0;
}
