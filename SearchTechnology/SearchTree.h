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
		/*
			由于insert函数的原因,必须用到用u_root这个中间变量!!!!!
		*/
		tree_node<T>* u_root  = new tree_node<T>(values[root_pos], root_pos);/*把数组索引当key*/;
		insert(u_root);
		this->root = u_root;
		this->nums = nums;  
		for (size_t i = 0; i < nums; i++) {
			insert(new tree_node<T>(values[i], i));                          /*把数组中的数据都插入到树中*/
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
			递归算法描述(摘自Algorithm4 P258):
				如果给定的value小于二叉树根节点值,则小于等于value的值[floor(value)]一定在根节点的左子树中;
				如果给定的value大于二叉树根节点值,那么仅在右子树中存在小于等于value的值时,则小于等于value的值[floor(value)]才会在右子树中
				如果给定的value等于二叉树根节点值,那么根节点就是floor(value)的值
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
		/*
			算法描述:
				1.根据给定的value从根开始找一条路径,并将路径上的路径依次入栈
					1.1若当前节点值小于value,往右子树查找
					1.2若当前节点值大于等于value,往左子树查找
					1.3重复1.1,1.2 直到当前节点为空
				2.从栈顶开始遍历栈中节点,返回第一个节点值小于value的节点
				3.若2未结束,返回value
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
		/*
			算法描述:
				1.排名为ranking说明树中有ranking个小于它的键
				2.对于当前根节点 r,其左子树大小为k:
					若 k < ranking,往左子树找排名为k的节点
					若 k > ranking,往右子树中找排名为 k - ranking - 1的节点
					若 k = ranking,返回r->value
				3.未找到返回空
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
		/*
			算法要点:
				1.左子树中的节点排名 = 该节点在左子树中的排名;
				2.右子树中的节点排名 = 根节点的排名 + 该节点在右子树中的排名;
				3.根节点的排名 = 左子树的大小 + 1;
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
		return 0;//0 stands for no such value in tree
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