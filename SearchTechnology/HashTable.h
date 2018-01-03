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
	T value;
	size_t key;		//H_Node.value's index in array
	H_Node<T>* next;
};

template <class T>
class Hash_Table {
public:
	Hash_Table(T value[], size_t nums,size_t scale = DEFAULT) {
		hash = new H_Node<T>*[scale] {nullptr};
		this->scale = scale;
		for (size_t i = 0; i < nums; i++) {
			insert(value[i],i);
		}
	}
	void insert(T value,size_t key) {
		//hashV stands for index in array
		size_t hashV = M_JSHash(value);
		hash[hashV] = new H_Node<T>(value, key, hash[hashV]);
	}
	int search(T value) {
		H_Node<T>* tmp = hash[M_JSHash(value)];
		while (tmp) {
			if (tmp->value == value)
				return tmp->key;
			tmp = tmp->next;
		}
		return -1;
	}
	~Hash_Table(){
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
	size_t M_JSHash(T& value)
	{
		size_t hash = 1315423911;
		hash ^= ((hash << 5) + value + (hash >> 2));
		return hash % scale;
	}
private:
	H_Node<T>** hash;
	size_t scale;
};