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
	T value;             /*�ýڵ��ֵ*/
	size_t key;	         /*�ýڵ��ֵ(tree_node.value)�������ж�Ӧ���±�*/
	size_t N;	         /*�ڵ������,��¼�Ըýڵ�Ϊ���ڵ�������еĽڵ�����*/
	tree_node<T>* lchild;/*����*/
	tree_node<T>* rchild;/*�Һ���*/
};

template <class T>
class BST {
public:
	BST(T values[], size_t nums,size_t root_pos = 0) {
		/*
			����insert������ԭ��,�����õ���u_root����м����!!!!!
		*/
		tree_node<T>* u_root  = new tree_node<T>(values[root_pos], root_pos);/*������������key*/;
		insert(u_root);
		this->root = u_root;
		this->nums = nums;  
		for (size_t i = 0; i < nums; i++) {
			insert(new tree_node<T>(values[i], i));                          /*�������е����ݶ����뵽����*/
		}
	}
	/*�����в���value*/
	void insert(T value) {
		insert(new tree_node<T>(value),++nums);
	}
	/*����value��Ӧ������*/
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
	/*���ֵ*/
	T max() {
		tree_node<T>* tmp = root;
		while (tmp->rchild)
			tmp = tmp->rchild;
		return tmp->value;
	}
	/*��Сֵ*/
	T min() {
		tree_node<T>* tmp = root;
		while (tmp->lchild)
			tmp = tmp->lchild;
		return tmp->value;
	}
	/*����ȡ��*/
	size_t floor(T value) {
		/*
			�ݹ��㷨����(ժ��Algorithm4 P258):
				���������valueС�ڶ��������ڵ�ֵ,��С�ڵ���value��ֵ[floor(value)]һ���ڸ��ڵ����������;
				���������value���ڶ��������ڵ�ֵ,��ô�����������д���С�ڵ���value��ֵʱ,��С�ڵ���value��ֵ[floor(value)]�Ż�����������
				���������value���ڶ��������ڵ�ֵ,��ô���ڵ����floor(value)��ֵ
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
			�㷨����:
				1.���ݸ�����value�Ӹ���ʼ��һ��·��,����·���ϵ�·��������ջ
					1.1����ǰ�ڵ�ֵС��value,������������
					1.2����ǰ�ڵ�ֵ���ڵ���value,������������
					1.3�ظ�1.1,1.2 ֱ����ǰ�ڵ�Ϊ��
				2.��ջ����ʼ����ջ�нڵ�,���ص�һ���ڵ�ֵС��value�Ľڵ�
				3.��2δ����,����value
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
	/*����ȡ��*/
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
	/*������������Ϊranking��ֵ*/
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
			�㷨����:
				1.����Ϊranking˵��������ranking��С�����ļ�
				2.���ڵ�ǰ���ڵ� r,����������СΪk:
					�� k < ranking,��������������Ϊk�Ľڵ�
					�� k > ranking,����������������Ϊ k - ranking - 1�Ľڵ�
					�� k = ranking,����r->value
				3.δ�ҵ����ؿ�
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
	/*����ֵvalue�����е�����*/
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
			�㷨Ҫ��:
				1.�������еĽڵ����� = �ýڵ����������е�����;
				2.�������еĽڵ����� = ���ڵ������ + �ýڵ����������е�����;
				3.���ڵ������ = �������Ĵ�С + 1;
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
	/*�����������(�������)*/
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
	/*�������ĸ��ڵ�*/
	tree_node<T>* get_root() {
		return root;
	}
	/*�ͷ���Դ*/
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
	/*��*/
	tree_node<T>* root;
	/*���Ĵ�С*/
	size_t nums;
private:
	/*�����½ڵ�*/
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