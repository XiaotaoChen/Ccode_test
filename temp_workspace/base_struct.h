#ifndef BASE_STRUCT_
#define BASE_STRUCT_ 
 
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

 struct ListNode {
     int val;
     ListNode* next;
     ListNode(): val(0), next(nullptr){}
     ListNode(int x):val(x), next(nullptr){}
     ListNode(int x, ListNode* next):val(x), next(next){}
 };

 #endif