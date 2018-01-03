#pragma once
#include <stack>
#include <iostream>

using std::cout;
using std::stack;

template <class T>
class tree_node {
public:
	tree_node(T value,size_t key) {
		this->value = value;
		this->key = key;
		this->lchild = nullptr;
		this->rchild = nullptr;
		N = 1;
	}
	T value;             /*该节点的值*/
	size_t key;	         /*该节点的值(tree_node.value)在数组中对应的下标*/
	size_t N;	         /*节点计数器,记录以该节点为根节点的子树中的节点总数*/
	tree_node<T>* lchild;/*左孩子*/
	tree_node<T>* rchild;/*右孩子*/
};

template <class T>
class BST {
public:
	BST(T values[], size_t nums,size_t root_pos = 0) {
		root = new tree_node<T>(values[root_pos],root_pos);/*把数组索引当key*/
		this->nums = nums;  
		for (size_t i = 1; i < nums; i++) {
			insert(new tree_node<T>(values[i], i));        /*把数组中的数据都插入到树中*/
		}
	}
	/*向树中插入value*/
	void insert(T value) {
		insert(new tree_node<T>(value),++nums);
	}
	/*查找value对应的索引*/
	int search(T value) {
		/*
			Recursive Edition:
				size_t search(tree_node<T>* root,T value){
					if(root->value == value)
						return root->key;
					else if(root->value > value)
						search(root->lchild,value);
					else
						search(root->rchild,value);
				}
		*/
		tree_node<T>* tmp = root;
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
	/*最大值*/
	T max() {
		tree_node<T>* tmp = root;
		while (tmp->rchild)
			tmp = tmp->rchild;
		return tmp->value;
	}
	/*最小值*/
	T min() {
		tree_node<T>* tmp = root;
		while (tmp->lchild)
			tmp = tmp->lchild;
		return tmp->value;
	}
	/*向下取整*/
	size_t floor(T value) {
		/*
			Recursive Edition:
				size_t floor(T value){
					tree_node<T>* ret = floor(root,value);
					if(ret) return ret->key;
					return root->key;
				}
				tree_node<T>* floor(tree_node<T>* root,T value){
					if(root == nullptr) return T();
					if(root->value == value)
						return root;
					if(root->value < value)
						return floor(root->lchild,value);
					tree_node<T>* n = floor(root->rchild,value);
					if(n)	return n;
					return root;
				}
		*/
		tree_node<T>* tmp = root;
		stack<tree_node<T>*> path_nodes;
		while (tmp) {
			path_nodes.push(tmp);
			if (value > tmp->value)
				tmp = tmp->rchild;
			else if (value <= tmp->value)
				tmp = tmp->lchild;
		}
		//traversal path_nodes,find first node->value <= value
		//if the value is min, ret will be return
		tree_node<T>* ret = path_nodes.top();
		while (!path_nodes.empty()) {
			tree_node<T>* t = path_nodes.top();
			if (t->value < value)
				return t->key;
			path_nodes.pop();
		}
		return ret->key;
	}
	/*向上取整*/
	size_t ceil(T value) {
		//see floor
		tree_node<T>* tmp = root;
		stack<tree_node<T>*> path_nodes;
		while (tmp) {
			path_nodes.push(tmp);
			if (value >= tmp->value)
				tmp = tmp->rchild;
			else if (value < tmp->value)
				tmp = tmp->lchild;
		}
		tree_node<T>* ret = path_nodes.top();
		while (!path_nodes.empty()) {
			tree_node<T>* t = path_nodes.top();
			if (t->value > value)
				return t->key;
			path_nodes.pop();
		}
		return ret->key;
	}
	/*查找树中排名为ranking的值*/
	T select(size_t ranking) {
		/*
		Recursive Edition:
			T select(tree_node<T>* root,size_t ranking) {
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
		tree_node<T>* tmp{root};
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
	/*返回值value在树中的排名*/
	size_t rank(T value) {
		/*
		Recursive Edition:
			size_t rank(tree_node<T>* root,T value){
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
		tree_node<T>* tmp {root};
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
	/*输出排序序列(先序遍历)*/
	void sort() {
		stack<tree_node<T>*> s;
		tree_node<T>* cur = root;
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
	/*返回树的根节点*/
	tree_node<T>* get_root() {
		return root;
	}
	/*释放资源*/
	~BST() {
		//InOrderedTraversal
		stack<tree_node<T>*> s;
		tree_node<T>* cur = root;
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
	/*根*/
	tree_node<T>* root;
	/*树的大小*/
	size_t nums;
private:
	/*插入新节点*/
	void insert(tree_node<T>* node) {
		/*
		Recursive Edition:
		void insert(tree_node<T>* root,tree_node<T>* node){
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
		tree_node<T>* tmp = root;
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
};

//TODO
class AVL {
public:
private:
};