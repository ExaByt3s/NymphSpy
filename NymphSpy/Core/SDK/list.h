#pragma once

template< typename T >
class list {
private:
	struct Node {
		Node() : m_next(NULL) { }
		Node(const T& value) : m_value(value), m_next(NULL) { }

		T m_value;
		Node* m_next;
	}; Node* m_head;
public:
	class iterator {
	private: Node* m_node;
	public:
		iterator(Node* node) : m_node(node) { }
		void operator++();
		bool operator==(const iterator& var);
		bool operator!=(const iterator& var);

		T get();
	};

public:
	list();
	~list();

	void append(const T& value);
	void remove();

	iterator begin() const;
	iterator end() const;

	size_t size() const;
};

template< typename T >
list< T >::list() : m_head(NULL) { }

template< typename T >
list< T >::~list() { while (m_head) remove(); }

template< typename T >
void list< T >::append(const T& value) {
	if (Node * node = new Node(value)) {
		node->m_next = m_head;
		m_head = node;
	}
}

template< typename T >
void list< T >::remove() {
	if (m_head) {
		Node* n_head = m_head->m_next;
		delete m_head;
		m_head = n_head;
	}
}

template< typename T >
void list< T >::iterator::operator++() {
	if (m_node) m_node = m_node->m_next;
}

template< typename T >
bool list< T >::iterator::operator==(const iterator& var) {
	if (this == &var) {
		return true;
	} return m_node == var.m_node;
}

template< typename T >
bool list< T >::iterator::operator!=(const iterator& var) {
	return !operator==(var);
}

template< typename T >
T list< T >::iterator::get() {
	if (m_node) {
		return m_node->m_value;
	} return T();
}

template< typename T >
typename list< T >::iterator list< T >::begin() const {
	return iterator(m_head);
}

template< typename T >
typename list< T >::iterator list< T >::end() const {
	return iterator(NULL);
}

template< typename T >
size_t list< T >::size() const {
	size_t s = 0;
	for (iterator it = begin(); it != end(); ++it) ++s;
	return s;
}
