#include "rb_tree.h"
#include <windows.h>
#include <iostream>
#include <queue>

#define SWAP(a, b) \
  {                \
    bool temp = a; \
    a = b;         \
    b = temp;      \
  }

TreeNode::TreeNode(int val) {
  this->val_ = val;
  this->left_child_ = NULL;
  this->right_child_ = NULL;
}

TreeNode::~TreeNode() {}

RedBlackTree::RedBlackTree() {
  root_ = NULL;
  count_ = 0;
}

RedBlackTree::~RedBlackTree() {
  std::queue<TreeNode *> queue;

  queue.push(this->root_);
  while (!queue.empty()) {
    TreeNode *temp = queue.front();
    queue.pop();

    if (temp->left_child_) queue.push(temp->left_child_);
    if (temp->right_child_) queue.push(temp->right_child_);

    delete temp;
  }

  return;
}

void RedBlackTree::Insert(int val) {
  TreeNode *new_node = new TreeNode(val);
  TreeNode *parent = this->root_;
  this->count_++;

  if (!parent) {
    this->root_ = new_node;
    new_node->color_ = BLACK;
    new_node->parent_ = new_node;
    return;
  }

  while (true) {
    if (val < parent->val_) {
      // if given value is less than the value of the current parent node
      if (parent->left_child_) {
        parent = parent->left_child_;
      } else {
        parent->left_child_ = new_node;
        new_node->color_ = RED;
        new_node->parent_ = parent;

        _InsertColorCheck(new_node);
        return;
      }
    } else {
      // if given value is more than the value of the current parent node
      if (parent->right_child_) {
        parent = parent->right_child_;
      } else {
        parent->right_child_ = new_node;
        new_node->color_ = RED;
        new_node->parent_ = parent;

        _InsertColorCheck(new_node);
        return;
      }
    }
  }
}

void RedBlackTree::Delete(int val) {
  TreeNode *parent = this->root_;

  while (parent) {
    if (parent->val_ == val) {
      break;
    } else if (val < parent->val_) {
      parent = parent->left_child_;
    } else {
      parent = parent->right_child_;
    }
  }

  if (!parent) return;

  this->count_--;
  RedBlackTree::_Delete(parent);

  return;
}

void RedBlackTree::_Delete(TreeNode *node) {
  if (this->count_ == 0) {
    delete this->root_;
    this->root_ = NULL;
    return;
  }

  if (node->left_child_ && node->right_child_) {
    TreeNode *temp;

    for (temp = node->right_child_; temp->left_child_; temp = temp->left_child_)
      ;

    node->val_ = temp->val_;
    _Delete(temp);

    return;
  }

  // if node has a child or no children
  TreeNode *parent = node->parent_;
  TreeNode *child = node->left_child_ ? node->left_child_ : node->right_child_;
  bool is_left_child = node == parent->left_child_;

  if (node == parent) {
    this->root_ = child;
    if (child) child->parent_ = child;
  } else if (node == parent->left_child_) {
    parent->left_child_ = child;
    if (child) child->parent_ = parent;
  } else {
    parent->right_child_ = child;
    if (child) child->parent_ = parent;
  }

  if (node->color_ == BLACK) {
    if (child && child->color_ == RED) {
      child->color_ = BLACK;
    } else {
      // if (node->color_ == BLACK)
      // and if (child->color_ == BLACK)
      // problem in the number of black nodes, need to be reconstruct the three
      _DeleteColorCheck(child, parent, is_left_child);
    }
  }

  delete node;
  return;
}

void RedBlackTree::Print() {
  std::queue<TreeNode *> queue;
  int count = 1, next_count = 0;

  if (!this->root_) return;
  queue.push(this->root_);

  // BFS
  while (!queue.empty()) {
    TreeNode *temp = queue.front();
    queue.pop();

    // set font color with the color of the node
    if (temp == NULL) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    } else if (temp->color_ == RED) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    } else {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    }

    if (temp) {
      printf("%4d\t", temp->val_);
    } else {
      printf("NULL\t");
    }
    count--;

    if (temp) {
      queue.push(temp->left_child_);
      next_count++;

      queue.push(temp->right_child_);
      next_count++;
    }

    // when all nodes in the current level are printed
    if (count == 0) {
      std::cout << std::endl;
      count = next_count;
      next_count = 0;
    }
  }

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
  std::cout << std::endl;
  return;
}

void RedBlackTree::_InsertColorCheck(TreeNode *node) {
  TreeNode *parent = node->parent_, *grand_parent = node->parent_->parent_,
           *uncle;

  if (parent->color_ == RED) {
    // Two reds in a row
    uncle = grand_parent->right_child_ == parent ? grand_parent->left_child_
                                                 : grand_parent->right_child_;
    if (uncle && uncle->color_ == RED) {
      parent->color_ = uncle->color_ = BLACK;
      grand_parent->color_ = RED;

      if (grand_parent == this->root_) {
        grand_parent->color_ = BLACK;
      } else {
        _InsertColorCheck(grand_parent);
      }
    } else {
      // if uncle->color_ == BLACK
      // and if the parent node is the left child of the grand parent node
      if (parent == grand_parent->left_child_) {
        // and node is the right child of parent node
        if (node == parent->right_child_) {
          _RotateLeft(parent);
          _RotateRight(grand_parent);
          grand_parent->color_ = RED;
          node->color_ = BLACK;
        } else {
          _RotateRight(grand_parent);
          grand_parent->color_ = RED;
          parent->color_ = BLACK;
        }
      } else {
        // and if the parent node is the right child of the grand parent node
        // and node is the left child of parent node
        if (node == parent->left_child_) {
          _RotateRight(parent);
          _RotateLeft(grand_parent);
          grand_parent->color_ = RED;
          node->color_ = BLACK;
        } else {
          _RotateLeft(grand_parent);
          grand_parent->color_ = RED;
          parent->color_ = BLACK;
        }
      }
    }
  }

  return;
}

void RedBlackTree::_DeleteColorCheck(TreeNode *node, TreeNode *parent,
                                     bool is_left_child) {
  TreeNode *uncle = is_left_child ? parent->right_child_ : parent->left_child_;
  bool is_parent_red = parent->color_ == RED;
  bool is_uncle_red = uncle ? uncle->color_ == RED : false;
  bool is_left_red =
      uncle ? uncle->left_child_ ? uncle->left_child_->color_ == RED : false
            : false;  // color of the left child of the uncle node
  bool is_right_red =
      uncle ? uncle->right_child_ ? uncle->right_child_->color_ == RED : false
            : false;  // color of the right child of the uncle node

  // case1: parent->color_ == RED
  //        and the color of the uncle node and its children is black
  if (is_parent_red && !is_uncle_red && !is_left_red && !is_right_red) {
    parent->color_ = BLACK;
    if (uncle) uncle->color_ = RED;
    return;
  }

  // case2: parent->color_ == BLACK
  //        and the color of the uncle node and its children is black
  if (!is_parent_red && !is_uncle_red && !is_left_red && !is_right_red) {
    if (uncle) uncle->color_ = RED;
    if (parent != this->root_)
      _DeleteColorCheck(parent, parent->parent_,
                        parent == parent->parent_->left_child_);
    return;
  }

  if (is_left_child) {
    // case3: uncle->color_ == BLACK
    //        and the color of its right child is RED
    if (!is_uncle_red && is_right_red) {
      _RotateLeft(parent);
      SWAP(parent->color_, uncle->color_);
      uncle->right_child_->color_ = BLACK;
      return;
    }

    // case4: uncle->color_ == BLACK
    //        and the color of its left child is RED, right child BLACK
    if (!is_uncle_red && is_left_red && !is_right_red) {
      _RotateRight(uncle);
      if (uncle->left_child_) {
        SWAP(uncle->color_, uncle->left_child_->color_);
      } else {
        uncle->color_ = BLACK;
      }
      _DeleteColorCheck(node, parent, is_left_child);
      return;
    }

    // case5: parent->color_ == BLACK
    //        and the color of the uncle node is RED, both children BLACK
    if (!is_parent_red && is_uncle_red && !is_left_red && !is_left_red) {
      _RotateLeft(parent);
      SWAP(parent->color_, uncle->color_);
      _DeleteColorCheck(node, parent, is_left_child);
      return;
    }
  } else {
    // case3: uncle->color_ == BLACK
    //        and the color of its left child is RED
    if (!is_uncle_red && is_left_red) {
      _RotateRight(parent);
      SWAP(parent->color_, uncle->color_);
      uncle->left_child_->color_ = BLACK;
      return;
    }

    // case4: uncle->color_ == BLACK
    //        and the color of its right child is RED, left child BLACK
    if (!is_uncle_red && is_right_red && !is_left_red) {
      _RotateLeft(uncle);
      if (uncle->right_child_) {
        SWAP(uncle->color_, uncle->right_child_->color_);
      } else {
        uncle->color_ = BLACK;
      }
      _DeleteColorCheck(node, parent, is_left_child);
      return;
    }

    // case5: parent->color_ == BLACK
    //        and the color of the uncle node is RED, both children BLACK
    if (!is_parent_red && is_uncle_red && !is_left_red && !is_left_red) {
      _RotateRight(parent);
      SWAP(parent->color_, uncle->color_);
      _DeleteColorCheck(node, parent, is_left_child);
      return;
    }
  }
}

void RedBlackTree::_RotateLeft(TreeNode *node) {
  //  Concept pic, when node is the left child of the parent node
  //          parent
  //                node
  //                    right_child
  //                left_child
  TreeNode *parent = node->parent_;
  TreeNode *right_child = node->right_child_;
  TreeNode *left_child = right_child->left_child_;

  // if node is the root of the tree
  if (node == node->parent_) {
    this->root_ = right_child;
    right_child->parent_ = right_child;
  } else if (parent->right_child_ == node) {
    parent->right_child_ = right_child;
    right_child->parent_ = parent;
  } else {
    parent->left_child_ = right_child;
    right_child->parent_ = parent;
  }

  node->parent_ = right_child;
  right_child->left_child_ = node;

  if (left_child) left_child->parent_ = node;
  node->right_child_ = left_child;
}

void RedBlackTree::_RotateRight(TreeNode *node) {
  //  Concept pic, when node is the left child of the parent node
  //          parent
  //      node
  //  left_child
  //        right_child
  TreeNode *parent = node->parent_;
  TreeNode *left_child = node->left_child_;
  TreeNode *right_child = left_child->right_child_;

  // if node is the root of the tree
  if (node == node->parent_) {
    this->root_ = left_child;
    left_child->parent_ = left_child;
  } else if (parent->right_child_ == node) {
    parent->right_child_ = left_child;
    left_child->parent_ = parent;
  } else {
    parent->left_child_ = left_child;
    left_child->parent_ = parent;
  }

  node->parent_ = left_child;
  left_child->right_child_ = node;

  if (right_child) right_child->parent_ = node;
  node->left_child_ = right_child;
}
