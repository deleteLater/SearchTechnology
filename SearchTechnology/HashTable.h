#pragma once
#define DEFAULT 16

template <class T>
class H_Node {
public:
	H_Node() {}
	H_Node(T value, size_t key,H_Node<T>* next = nullptr) {
		this->value = value;
		this->key = key;
		this->next = next;
	}
	T value;		/*�ڵ�ֵ*/
	size_t key;		/*value������*/
	H_Node<T>* next;/*ָ����һ�ڵ�*/
};

template <class T>
class Hash_Table {
public:
	/*������ϣ��*/
	Hash_Table(T value[], size_t nums,size_t scale = DEFAULT) {
		hash = new H_Node<T>*[scale] {nullptr};
		this->scale = scale;
		for (size_t i = 0; i < nums; i++) {
			insert(value[i],i);
		}
	}
	/*����в����½ڵ�*/
	void insert(T value,size_t key) {
		/*ͷ�巨*/
		size_t hashV = M_JSHash(value);
		hash[hashV] = new H_Node<T>(value, key, hash[hashV]);
	}
	/*����value�����е�����*/
	int search(T value) {
		H_Node<T>* tmp = hash[M_JSHash(value)];
		while (tmp) {
			if (tmp->value == value)
				return tmp->key;
			tmp = tmp->next;
		}
		return -1;
	}
	/*��ϣ����*/
	size_t M_JSHash(T& value)
	{
		size_t hash = 1315423911;//Only SB know why this number
		hash ^= ((hash << 5) + value + (hash >> 2));
		return hash % scale;
	}
	/*�ͷ���Դ*/
	~Hash_Table() {
		for (size_t i = 0; i < scale; i++) {
			H_Node<T>* tmp = hash[i];
			H_Node<T>* head = tmp;
			while (head) {
				head = tmp->next;
				delete tmp;
				tmp = head;
			}
		}
		delete[]hash;
	}
private:
	H_Node<T>** hash;/*��ϣ��ͷָ��*/
	size_t scale;    /*��ϣ��Ĵ�С(��Χ)*/
};