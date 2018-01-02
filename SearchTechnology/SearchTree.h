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
		N = 1;
	}
	T value;
	size_t key;
	size_t N;	//�ڵ������,��¼�Ըýڵ�Ϊ���ڵ�������еĽڵ�����
	Node<T>* lchild;
	Node<T>* rchild;
};

template <class T>
class BST {
public:
	BST(T values[], size_t nums,size_t root_pos = 0) {
		root = new Node<T>(values[root_pos],root_pos);
		this->nums = nums;
		for (size_t i = 1; i < nums; i++) {
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
		/*
		Recursive Edition:
			T select(Node<T>* root,size_t ranking) {
			if (root == nullptr)
				return T();
			size_t left_size = 0;
			if(root->lchild)
				left_size = root->lchild->N;
			if (left_size == ranking - 1)
				return root->value;
			else if (left_size >= ranking)
				select(root->lchild, ranking);
			else
				select(root->rchild, ranking - left_size - 1);
		}
		*/
		Node<T>* tmp{root};
		size_t left_size{0};
		while (tmp) {
			left_size = 0;
			if (tmp->lchild)
				left_size = tmp->lchild->N;
			if (left_size == ranking - 1)
				return tmp->value;
			else if (left_size < ranking) {
				tmp = tmp->rchild;
				ranking = ranking - left_size - 1;
			}
			else
				tmp = tmp->lchild;
		}
		return T();
	}
	size_t rank(T value) {
		/*
		Recursive Edition:
			size_t rank(Node<T>* root,T value){
				if(root == nullptr)
					return 0;
				}else if(root->value == value){
					if(root->lchild)
						return root->lchild->N;
					return 1;
				}else if(root->value < value){
					if(root->lchild)
						return 1 + root->lchild->N +rank(root->rchild,value);
					return 1 + rank(root->rchild,value);
				}else
					rank(root->lchild,value);
			}		
		*/
		Node<T>* tmp {root};
		size_t ret = 0;	
		while (tmp) {
			if (tmp->value == value) {
				if (tmp->lchild)
					return ret + tmp->lchild->N + 1;
				return ret + 1;
			}
			else if (tmp->value < value) {
				if (tmp->lchild)
					ret = ret + tmp->lchild->N + 1;
				else
					ret++;
				tmp = tmp->rchild;
			}
			else
				tmp = tmp->lchild;
		}
		return 0;//0 stands for not-find
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