/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:43:21 by matrus            #+#    #+#             */
/*   Updated: 2020/11/09 15:43:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include "allocator.hpp"
#include "iterator.hpp"

template< class T, class Alloc = ft::allocator<T> >
class ft::list {

public:

	/*** INTERNAL TYPES ***/
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

private:

	typedef struct	_s_node
	{
		struct _s_node*	_next;
		struct _s_node*	_prev;
		value_type *	_data;
	}				_t_node;
	_t_node *		_begin_node;
	_t_node *		_end_node;

	typedef typename allocator_type::template rebind<_t_node>::other allocator_rebind;
	allocator_rebind _alloc_rebind;
	allocator_type	 _alloc;

public:

	/*** ITERATORS ***/

	class iterator : public ft::iterator<bidirectional_iterator_tag, value_type> {

//	template<class U, class A>
//	friend class list;
//	friend class const_iterator;

	public:
		iterator() : _ptr( nullptr ) { }
		~iterator() { }

		iterator( iterator const & it ) { *this = it; }
		iterator( _t_node * node ) { this->_ptr = node; }

		iterator & operator=( iterator const & rhs ) {
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		iterator & operator++() { this->_ptr = this->_ptr->_next; return *this; }
		iterator operator++(int) { iterator tmp = *this; this->operator++(); return tmp; }

		bool operator==( iterator const & rhs ) { return this->_ptr == rhs._ptr; }
		bool operator!=( iterator const & rhs ) { return this->_ptr != rhs._ptr; }

		value_type & operator*() { return *this->_ptr->_data; }
		value_type * operator->() { return this->_ptr->_data; }

		iterator & operator--() { this->_ptr = _ptr->_prev; return *this; }
		iterator operator--(int) { iterator tmp = *this; this->operator--(); return tmp; }

		_t_node* getPtr() const { return _ptr; }

	private:
		_t_node* _ptr;
	};

	class const_iterator : public ft::iterator<bidirectional_iterator_tag, value_type>
	{
//	template<class U, class A>
//	friend class list;

	public:
		const_iterator() { this->_ptr = nullptr; }
		~const_iterator() { }

		const_iterator( const_iterator const & it ) { *this = it; }
		const_iterator( iterator const & it ) {
			*this = it;
		}
		const_iterator( _t_node * node ) { this->_ptr = node; }

		const_iterator & operator=( const_iterator const & rhs ) {
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		const_iterator & operator=( iterator const & rhs ) {
			_ptr = rhs.getPtr();
			return *this;
		}

		const_iterator & operator++() { this->_ptr = _ptr->_next; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; this->operator++(); return tmp; }

		bool operator==( const_iterator const & rhs ) { return this->_ptr == rhs._ptr; }
		bool operator!=( const_iterator const & rhs ) { return this->_ptr != rhs._ptr; }

		value_type const & operator*() { return *this->_ptr->_data; }
		value_type const * operator->() { return this->_ptr->_data; }

		const_iterator & operator--() { this->_ptr = _ptr->_prev; return *this; }
		const_iterator operator--(int) { const_iterator tmp = *this; this->operator--(); return tmp; }

		_t_node* getPtr() const { return _ptr; }

	private:
		_t_node *_ptr;
	};

	class reverse_iterator : public ft::iterator<bidirectional_iterator_tag, value_type>
	{
		template<class U, class A> friend class list;
		friend class const_reverse_iterator;

	public:
		reverse_iterator() { this->_ptr = nullptr; }
		~reverse_iterator() { }

		reverse_iterator( reverse_iterator const & it ) { *this = it; }
		reverse_iterator( _t_node * node ) { this->_ptr = node; }

		reverse_iterator & operator=( reverse_iterator const & rhs ) {
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		reverse_iterator & operator++() { this->_ptr = _ptr->_prev; return *this; }
		reverse_iterator operator++(int) { reverse_iterator tmp = *this; this->operator++(); return tmp; }

		bool operator==( reverse_iterator const & rhs ) { return this->_ptr == rhs._ptr; }
		bool operator!=( reverse_iterator const & rhs ) { return this->_ptr != rhs._ptr; }

		value_type & operator*() { return *this->_ptr->_data; }
		value_type * operator->() { return this->_ptr->_data; }

		reverse_iterator & operator--() { this->_ptr = _ptr->_next; return *this; }
		reverse_iterator operator--(int) { reverse_iterator tmp = *this; this->operator--(); return tmp; }

		_t_node* getPtr() const { return _ptr; }

	private:
		_t_node *_ptr;
	};

	class const_reverse_iterator : public ft::iterator<bidirectional_iterator_tag, value_type>
	{
		template<class U, class A> friend class list;

	public:
		const_reverse_iterator() { this->_ptr = nullptr; }
		~const_reverse_iterator() { }

		const_reverse_iterator( const_reverse_iterator const & it ) { *this = it; }
		const_reverse_iterator( reverse_iterator const & it ) { *this = it; }
		const_reverse_iterator( _t_node * node ) { this->_ptr = node; }

		const_reverse_iterator & operator=( const_reverse_iterator const & rhs ) {
			if (this != &rhs)
				_ptr = rhs.getPtr();
			return *this;
		}

		const_reverse_iterator & operator=( reverse_iterator const & rhs ) {
			_ptr = rhs._ptr;
			return *this;
		}

		const_reverse_iterator & operator++() { this->_ptr = _ptr->_prev; return *this; }
		const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; this->operator++(); return tmp; }

		bool operator==( const_reverse_iterator const & rhs ) { return this->_ptr == rhs._ptr; }
		bool operator!=( const_reverse_iterator const & rhs ) { return this->_ptr != rhs._ptr; }

		value_type & operator*() { return *this->_ptr->_data; }
		value_type * operator->() { return this->_ptr->_data; }

		const_reverse_iterator & operator--() { this->_ptr = _ptr->_next; return *this; }
		const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; this->operator--(); return tmp; }

		_t_node* getPtr() const { return _ptr; }

	private:
		_t_node *_ptr;
	};

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	/*** CONSTRUCTION ***/
	explicit list (const allocator_type& alloc = allocator_type()) {
		_end_node = _alloc_rebind.allocate(1);
		_end_node->_next = _end_node;
		_end_node->_prev = _end_node;
		_end_node->_data = alloc.allocate(1);
		_begin_node = _end_node;
		_size = 0;
	}
//	explicit list (size_type n, const value_type& val = value_type(),
//				   const allocator_type& alloc = allocator_type());
//	template <class InputIterator>
//	list (InputIterator first, InputIterator last,
//		  const allocator_type& alloc = allocator_type());
//	list (const list& x);

	/*** DESTRUCTION ***/
	~list() {
		for (; 0 < _size; --_size) {
			_t_node* tmp = _begin_node;
			_begin_node = _begin_node->_next;
			_alloc.destroy(tmp->_data);
			_alloc.deallocate(tmp->_data, 1);
			_alloc_rebind.deallocate(tmp, 1);
		}
		_alloc.deallocate(this->_end_node->_data, 1);
		_alloc_rebind.deallocate(this->_end_node, 1);
	};

	/*** ASSIGNATION ***/
//	list& operator= (const list& x);

	/*** ITERATORS ***/
	iterator begin() { return iterator(_begin_node); }
	const_iterator begin() const { return const_iterator(_begin_node); }
	iterator end() { return iterator(_end_node); }
	const_iterator end() const { return const_iterator(_end_node); }
	reverse_iterator rbegin() { return reverse_iterator(_end_node->_prev); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(_end_node->_prev); }
	reverse_iterator rend() { return reverse_iterator(_begin_node->_prev); }
	const_reverse_iterator rend() const { return const_reverse_iterator(_begin_node->_prev); }

	/*** CAPACITY ***/
	bool empty() const { return this->_begin_node == this->_end_node; };
	size_type size() const { return this->_size; }
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

	/*** ELEMENT ACCESS ***/
	reference front() { return this->_begin_node->_data; };
	const_reference front() const { return this->_begin_node->_data; };
	reference back() { return this->_end_node->_prev->_data; };
	const_reference back() const { return this->_end_node->_prev->_data; };;

	/*** MODIFIERS ***/
//	template <class InputIterator>
//	void assign (InputIterator first, InputIterator last);
//	void assign (size_type n, const value_type& val);

	void push_front (const value_type& val) {
		_t_node *node = _alloc_rebind.allocate(1);
		node->_prev = this->_end_node;
		node->_next = this->_begin_node;
		value_type *data = _alloc.allocate(1);
		_alloc.construct( data, val );
		node->_data = data;
		this->_begin_node->_prev = node;
		this->_begin_node = node;
		_end_node->_next = _begin_node;
		this->_size += 1;
	};
//	void pop_front();
//	void push_back (const value_type& val);
//	void pop_back();

//	iterator insert (iterator position, const value_type& val);
//	void insert (iterator position, size_type n, const value_type& val);
//	template <class InputIterator>
//	void insert (iterator position, InputIterator first, InputIterator last);
//
//	iterator erase (iterator position);
//	iterator erase (iterator first, iterator last);
//
//	void swap (list& x);
//
//	void resize (size_type n, value_type val = value_type());
//
//	void clear();

	/*** OPERATIONS ***/
//	void splice (iterator position, list& x);
//	void splice (iterator position, list& x, iterator i);
//	void splice (iterator position, list& x, iterator first, iterator last);

//	void remove (const value_type& val);

//	template <class Predicate>
//	void remove_if (Predicate pred);

//	void unique();
//	template <class BinaryPredicate>
//	void unique (BinaryPredicate binary_pred);

//	void merge (list& x);
//	template <class Compare>
//	void merge (list& x, Compare comp);

//	void sort();
//	template <class Compare>
//	void sort (Compare comp);

//	void reverse();

private:

	size_type		_size;

};

#endif