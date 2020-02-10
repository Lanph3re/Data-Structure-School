#ifndef __RB_TREE_H
#define __RB_TREE_H
#define RED true
#define BLACK false

class TreeNode {
 public:
  TreeNode(int val);
  ~TreeNode();

 private:
  int val_;
  bool color_;
  TreeNode *parent_, *left_child_, *right_child_;
  friend class RedBlackTree;
};

class RedBlackTree {
 public:
  RedBlackTree();
  ~RedBlackTree();
  void Insert(int val);
  void Delete(int val);
  void Print();

 private:
  TreeNode *root_;
  int count_;
  void _Delete(TreeNode *node);
  void _InsertColorCheck(TreeNode *node);
  void _DeleteColorCheck(TreeNode *node, TreeNode *parent, bool is_left_child);
  void _RotateLeft(TreeNode *node);
  void _RotateRight(TreeNode *right);
};

#endif