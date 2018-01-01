#pragma once
#include <stack>
#include <iostream>

using std::cout;
using std::stack;

template <class T>
class Node {
public:
	Node(T value,size_t key) {
		this->value = value;
		this->lchild = nullptr;
		this->rchild = nullptr;
		this->key = key;
	}
	T value;
	size_t key;
	Node<T>* lchild;
	Node<T>* rchild;
};

template <class T>
class BST {
public:
	BST(T values[], size_t nums) {
		root = new Node<T>(values[0],0);
		this->nums = nums;
		for (int i = 1; i < nums; i++) {
			insert(new Node<T>(values[i], i));
		}
	}
	void insert(Node<T>* node) {
		/*
			Recursive Edition:
			void insert(Node<T>* root,Node<T>* node){
				if(!root)
					root = node;
				else if(node->value > root->value)
					insert(root->rchild,node);
				else if(node->value < root->value)
					insert(root->lchild,node);
			}
		*/
		Node<T>* tmp = root;
		while (tmp) {
			if (node->value > tmp->value) {
				if (!tmp->rchild) {
					tmp->rchild = node;
					break;
				}
				else tmp = tmp->rchild;
			}
			else if (node->value < tmp->value) {
				if (!tmp->lchild) {
					tmp->lchild = node;
					break;
				}
				else tmp = tmp->lchild;
			}
			else {
				delete node;	//delete repeated node
				return;
			}
		}
	}
	void insert(T value) {
		insert(new Node<T>(value),++nums);
	}
	int search(T value) {
		/*
			Recursive Edition:
				size_t search(Node<T>* root,T value){
					if(root->value == value)
						return root->key;
					else if(root->value > value)
						search(root->lchild,value);
					else
						search(root->rchild,value);
				}
		*/
		Node<T>* tmp = root;
		while (tmp) {
			if (value == tmp->value)
				return tmp->key;
			else if (value > tmp->value)
				tmp = tmp->rchild;
			else
				tmp = tmp->lchild;
		}
		return -1;
	}
	void InOrderedTraversal() {
		stack<Node<T>*> s;
		Node<T>* cur = root;
		while (cur || !s.empty()) {
			while (cur) {
				s.push(cur);
				cur = cur->lchild;
			}
			if (!s.empty()) {
				cur = s.top()->rchild;
				cout << s.top()->value;
				s.pop();
			}
		}
	}
	~BST() {
		//InOrderedTraversal
		stack<Node<T>*> s;
		Node<T>* cur = root;
		while (cur || !s.empty()) {
			while (cur) {
				s.push(cur);
				cur = cur->lchild;
			}
			if (!s.empty()) {
				cur = s.top()->rchild;
				delete s.top();
				s.pop();
			}
		}
	}
private:
	Node<T>* root;
	size_t nums;
};

class AVL {
public:
private:
};