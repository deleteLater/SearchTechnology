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
	T value;		/*节点值*/
	size_t key;		/*value的索引*/
	H_Node<T>* next;/*指向下一节点*/
};

template <class T>
class Hash_Table {
public:
	/*建立哈希表*/
	Hash_Table(T value[], size_t nums,size_t scale = DEFAULT) {
		hash = new H_Node<T>*[scale] {nullptr};
		this->scale = scale;
		for (size_t i = 0; i < nums; i++) {
			insert(value[i],i);
		}
	}
	/*向表中插入新节点*/
	void insert(T value,size_t key) {
		/*头插法*/
		size_t hashV = M_JSHash(value);
		hash[hashV] = new H_Node<T>(value, key, hash[hashV]);
	}
	/*查找value在树中的索引*/
	int search(T value) {
		H_Node<T>* tmp = hash[M_JSHash(value)];
		while (tmp) {
			if (tmp->value == value)
				return tmp->key;
			tmp = tmp->next;
		}
		return -1;
	}
	/*哈希函数*/
	size_t M_JSHash(T& value)
	{
		size_t hash = 1315423911;//Only SB know why this number
		hash ^= ((hash << 5) + value + (hash >> 2));
		return hash % scale;
	}
	/*释放资源*/
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
	H_Node<T>** hash;/*哈希表头指针*/
	size_t scale;    /*哈希表的大小(范围)*/
};