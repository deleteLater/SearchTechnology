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
		this->key = key;
		this->lchild = nullptr;
		this->rchild = nullptr;
		N = 0;
	}
	T value;
	size_t key;
	size_t N;	//节点计数器,记录以该节点为根节点的子树中的节点总数
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
		if (search(node->value) != -1) {
			delete node;
			return;
		}
		Node<T>* tmp = root;
		while (tmp) {
			tmp->N++;
			if (node->value > tmp->value) {
				if (!tmp->rchild) {
					tmp->rchild = node;
					return;
				}
				else tmp = tmp->rchild;
			}
			else if (node->value < tmp->value) {
				if (!tmp->lchild) {
					tmp->lchild = node;
					return;
				}
				else tmp = tmp->lchild;
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
	T max() {
		Node<T>* tmp = root;
		while (tmp->rchild)
			tmp = tmp->rchild;
		return tmp->value;
	}
	T min() {
		Node<T>* tmp = root;
		while (tmp->lchild)
			tmp = tmp->lchild;
		return tmp->value;
	}
	T floor(T value) {
		Node<T>* tmp = root;
		while (tmp) {
			if (value > tmp->value)
				tmp = tmp->rchild;
			else if (value < tmp->value)
				tmp = tmp->lchild;
			else {
				if (tmp->lchild)
					return tmp->lchild->value;
				else
					return T();
			}
		}
	}
	T ceil(T value) {
		Node<T>* tmp = root;
		while (tmp) {
			if (value > tmp->value)
				tmp = tmp->rchild;
			else if (value < tmp->value)
				tmp = tmp->lchild;
			else {
				if (tmp->rchild)
					return tmp->rchild->value;
				else
					return T();
			}
		}
	}
	T select(size_t ranking) {

	}
	size_t rank(T value) {

	}
	void sort() {
		InOrderedTraversal();
	}
	Node<T>* get_root() {
		return root;
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
				cout << s.top()->value << ' ';
				s.pop();
			}
		}
	}
};

class AVL {
public:
private:
};