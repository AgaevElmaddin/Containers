#ifndef RED_BLACK_TREE_ITERATOR_HPP
# define RED_BLACK_TREE_ITERATOR_HPP

#include "iterators_traits.hpp"
#include "Red_Black_Tree.hpp"
#include "conditional.hpp"
#include "map.hpp"

namespace ft
{
	// Red_Black_Tree_Iterator = bidirectional_iterator
	// 1) iterator
	template <class T, class Node_Ptr>
	class Red_Black_Tree_Iterator
	{
		public:
				typedef bidirectional_iterator_tag iterator_category;
				typedef T value_type;
				typedef Node_Ptr node_ptr;
				typedef value_type* pointer;
				typedef value_type& reference;
		private:
				node_ptr ptr; // node_ptr from rbt_node class
		public:
				Red_Black_Tree_Iterator(): ptr(NULL) {}
				Red_Black_Tree_Iterator(node_ptr ptr1) : ptr(ptr1) {}
				Red_Black_Tree_Iterator(const Red_Black_Tree_Iterator& copy)
				{
					this->ptr = copy.ptr;
				}
				virtual ~Red_Black_Tree_Iterator() {}

				Red_Black_Tree_Iterator& operator=(const Red_Black_Tree_Iterator& copy)
				{
					if (*this == copy)
						return (*this);
					this->ptr = copy.ptr;
					return (*this);
				}

				reference operator*() const
				{
					return this->ptr->key;
				}

				pointer operator->() const
				{
					return &this->ptr->key;
				}

				Red_Black_Tree_Iterator& operator++()
				{
					this->ptr = tree_successor(ptr);
					return *this;
				}

				Red_Black_Tree_Iterator& operator++(int)
				{
					Red_Black_Tree_Iterator tmp(*this);
					++(*this);
					return tmp;
				}

				Red_Black_Tree_Iterator& operator--()
				{
					this->ptr = tree_predecessor(ptr);
					return *this;
				}

				Red_Black_Tree_Iterator& operator--(int)
				{
					Red_Black_Tree_Iterator tmp(*this);
					--(*this);
					return tmp;
				}
	};

	// non-member functions
	template <class T, class Node_Ptr1, class Node_Ptr2>
	bool operator==(const Red_Black_Tree_Iterator<T, Node_Ptr1>& it1, const Red_Black_Tree_Iterator<T, Node_Ptr2>& it2)
	{
		return it1.ptr == it2.ptr;
	}

	template <class T, class Node_Ptr1, class Node_Ptr2>
	bool operator!=(const Red_Black_Tree_Iterator<T, Node_Ptr1>& it1, const Red_Black_Tree_Iterator<T, Node_Ptr2>& it2)
	{
		return !(it1 == it2);
	}

	// const iterator
	template <class T, class Node_Ptr>
	class Red_Black_Tree_Const_Iterator
	{
		public:
				typedef bidirectional_iterator_tag iterator_category;
				typedef T value_type;
				typedef Node_Ptr node_ptr;
				typedef value_type* pointer;
				typedef value_type& reference;
		private:
				node_ptr ptr; // node_ptr from rbt_node class
				typedef Red_Black_Tree_Iterator<T, Node_Ptr> non_const_it;
		public:
				Red_Black_Tree_Const_Iterator(): ptr(NULL) {}
				Red_Black_Tree_Const_Iterator(node_ptr ptr1) : ptr(ptr1) {}
				Red_Black_Tree_Const_Iterator(const non_const_it& copy)
				{
					this->ptr = copy.ptr;
				}
				virtual ~Red_Black_Tree_Const_Iterator() {}

				Red_Black_Tree_Const_Iterator& operator=(const non_const_it& copy)
				{
					if (*this == copy)
						return (*this);
					this->ptr = copy.ptr;
					return (*this);
				}

				reference operator*() const
				{
					return this->ptr->key;
				}

				pointer operator->() const
				{
					return &this->ptr->key;
				}

				Red_Black_Tree_Const_Iterator& operator++()
				{
					this->ptr = tree_successor(ptr);
					return *this;
				}

				Red_Black_Tree_Const_Iterator& operator++(int)
				{
					Red_Black_Tree_Const_Iterator tmp(*this);
					++(*this);
					return tmp;
				}

				Red_Black_Tree_Const_Iterator& operator--()
				{
					this->ptr = tree_predecessor(ptr);
					return *this;
				}

				Red_Black_Tree_Const_Iterator& operator--(int)
				{
					Red_Black_Tree_Const_Iterator tmp(*this);
					--(*this);
					return tmp;
				}
	};

	// non-member functions
	template <class T, class Node_Ptr1, class Node_Ptr2>
	bool operator==(const Red_Black_Tree_Const_Iterator<T, Node_Ptr1>& it1, const Red_Black_Tree_Const_Iterator<T, Node_Ptr2>& it2)
	{
		return it1.ptr == it2.ptr;
	}

	template <class T, class Node_Ptr1, class Node_Ptr2>
	bool operator!=(const Red_Black_Tree_Const_Iterator<T, Node_Ptr1>& it1, const Red_Black_Tree_Const_Iterator<T, Node_Ptr2>& it2)
	{
		return !(it1 == it2);
	}
}

#endif