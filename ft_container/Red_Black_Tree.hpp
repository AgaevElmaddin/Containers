#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <algorithm>
#include "Red_Black_Tree_Iterator.hpp"
#include "map.hpp"

// about sentinel nodes (bottom and end): https://kaba.hilvi.org/pastel-1.5.0/pastel/sys/redblacktree/redblacktree.htm

namespace ft
{
	template <class Node_Ptr>
	bool is_null(Node_Ptr node)
	{
		return node == NULL || node->is_bottom_end == 1;
	}

	template <class T>
	class rbt_node // node of red-black tree
	{
		public:
				typedef rbt_node<T>* node_ptr; // pointer to type T
				typedef T value_type; // type of the value

				value_type	value; // value of the node
				node_ptr	left; // left child node
				node_ptr	right; // right child node
				node_ptr	p; // parent node
				bool		is_black; // if is_black == 1 color of the node is black otherwise is red
				bool		is_bottom_end; // check the node in situations end() and rend() when we can't have an access to the content of the node, and attempting to access it results in undefined behavior

				// constructors, destructor and assign operator
				rbt_node(): value(-1), left(NULL), right(NULL), p(NULL), is_black(0), is_bottom_end(0) {} // default constructor
				rbt_node(value_type v, node_ptr l, node_ptr r, node_ptr parent, bool b): //constructor with parameters
						value(v), left(l), right(r), p(parent), is_black(b), is_bottom_end(0) {}
				rbt_node(const rbt_node& copy) // copy constructor
				{
					this->value = copy.value;
					this->left = copy.left;
					this->right = copy.right;
					this->p = copy.p;
					this->is_black = copy.is_black;
					this->is_bottom_end = copy.is_bottom_end;
				}
				~rbt_node() {} // destructor
				rbt_node& operator=(const rbt_node& copy) // assign operator
				{
					this->value = copy.value;
					this->left = copy.left;
					this->right = copy.right;
					this->p = copy.p;
					this->is_black = copy.is_black;
					this->is_bottom_end = copy.is_bottom_end;
					return (*this);
				}
	};

	/* method (tree_is_left_child) returns 1(true) if x is a left child of its parent otherwise 0(false)
	   precondition: x != NULL */
	template <class Node_Ptr>
	bool	tree_is_left_child(Node_Ptr x)
	{
		return x == x->parent->left;
	}

	/* this method finds the smallest key in the tree */
	template <class Node_Ptr>
	Node_Ptr tree_minimum(Node_Ptr x)
	{
		while (is_null(x->left) == 0)
			x = x->left;
		return (x);
	}

	/* this method finds the biggest key in the tree */
	template  <class Node_Ptr>
	Node_Ptr tree_maximum(Node_Ptr x)
	{
		while (is_null(x->right) == 0)
			x = x->right;
		return (x);
	}

	/* return the node, which lies ahead of given node
	example: 15
			/  \
		   6    18
		  / \   / \
		 3   7 17  20
		/ \   \
		2  4   13
		      /
			 9											*/
	template <class Node_Ptr>
	Node_Ptr tree_successor(Node_Ptr x)
	{
		if (x->right != NULL)
			return tree_minimum(x->right);
		Node_Ptr y = x->p;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->p;
		}
		return (y);
	}

	/* return the node, which lies behind of given node */
	template <class Node_Ptr>
	Node_Ptr tree_predecessor(Node_Ptr x)
	{
		if (x->left != NULL)
			return tree_maximum(x->left);
		Node_Ptr y = x->p;
		while (y != NULL && x == y->left)
		{
			x = y;
			y = y->p;
		}
		return (y);
	}

	////////////////////////////RBT Class////////////////////////////
	template <class T, class Compare, class Allocator>
	class Red_Black_Tree
	{
		public:
				typedef T value_type;
				typedef Compare value_compare;
				typedef Allocator allocator_type;
				typedef rbt_node<T> rbt_node;
				typedef typename rbt_node::node_ptr node_ptr;
				// rebind - a structure that enables an allocator for objects of one type to allocate storage for objects of another type
				typedef typename allocator_type::template rebind<rbt_node>::other allocator_node_type;
				typedef Red_Black_Tree_Iterator<T, node_ptr> iterator;
				typedef Red_Black_Tree_Const_Iterator<T, node_ptr> const_iterator;
				typedef typename ft::reverse_iterator<iterator> reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
				typedef typename allocator_type::size_type size_type;
				typedef typename allocator_type::difference_type difference_type;
		private:
				node_ptr T_root; // root of the red-black tree
				value_compare cmp;
				allocator_type alloc;
				allocator_node_type node_alloc; // allocator for node
				node_ptr bottom; // element preceding the first element of the non-reversed vector (sentinel node)
				node_ptr _end; // element folowing the last element (sentinel node).
				size_type _size;
		public:
				// constructors and destructor
				Red_Black_Tree();
				explicit Red_Black_Tree(const value_compare& comp, const allocator_type& allocator);
				Red_Black_Tree(const Red_Black_Tree& copy);
				~Red_Black_Tree();
		private:
				//bool is_null(node_ptr node);
				// link and unlink sentinels from the rbt
				node_ptr link_bottom_node();
				node_ptr link_bottom_node() const;
				void unlink_bottom_node();
				node_ptr link_end_node();
				node_ptr link_end_node() const;
				void unlink_end_node();
				// sentinels
				void	sentinel_end();
				void	sentinel_bottom();
				// rbt methods
				void left_rotate(node_ptr x);
				void right_rotate(node_ptr x);
				void rb_insert(node_ptr z);
				void rb_insert_fixup(node_ptr z);
				void transplant(node_ptr u, node_ptr v);
				void rb_delete(node_ptr z);
				void rb_delete_fixup(node_ptr z);
				template <class, class, class, class> friend class map;
		public:
				// map fuctions
				// iterators
				iterator begin();
				const_iterator begin() const;
				iterator end();
				const_iterator end() const;
				reverse_iterator rbegin();
				const_reverse_iterator rbegin() const;
				reverse_iterator rend();
				const_reverse_iterator rend() const;
				// capacity
				bool empty() const;
				size_type size() const;
				size_type max_size() const;
				// modifiers
				void insert(const value_type& value);
				template <class InputIterator>
				void insert(InputIterator first, InputIterator last);
				void erase(const value_type& value);
				template <class InputIterator>
				void erase(InputIterator it);
				void clear_node(node_ptr z);
				void clear();
				void clear_bottom_end();
				// operations (lookup)
				template <class Key>
				size_type count(const Key& key) const;
				template <class Key>
				iterator find(const Key& key);
				template <class Key>
				const_iterator find(const Key& key) const;
				template <class Key>
				iterator lower_bound(const Key& key);
				template <class Key>
				const_iterator lower_bound(const Key& key) const;
				template <class Key>
				iterator upper_bound(const Key& key);
				template <class Key>
				const_iterator upper_bound(const Key& key) const;
				template <class Key>
				pair<iterator, iterator> equal_range(const Key& key);
				template <class Key>
				pair<const_iterator, const_iterator> equal_range(const Key& key) const;
				void swap(Red_Black_Tree& other);
				// Allocator and value_compare
				allocator_type get_allocator() const;
				value_compare get_value_compare() const;
				// set fuctions
	};
	////////////////////////////RBT Class////////////////////////////

	// template <class T, class Compare, class Allocator>
	// bool Red_Black_Tree<T, Compare, Allocator>::is_null(node_ptr node)
	// {
	// 	return node == NULL || node->is_bottom_end == 1;
	// }

	///////////////link and unlink sentinels from the rbt///////////////////////
	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::node_ptr
	Red_Black_Tree<T, Compare, Allocator>::link_bottom_node()
	{
		if (T_root == NULL)
			return T_root;
		node_ptr min_node = tree_minimum(T_root);
		node_ptr bottom_ptr = min_node->left;
		if (bottom_ptr != NULL)
			return bottom_ptr;
		bottom_ptr = bottom;
		bottom_ptr->p = min_node;
		min_node->left = bottom_ptr;
		return (bottom_ptr);
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::node_ptr
	Red_Black_Tree<T, Compare, Allocator>::link_bottom_node() const
	{
		if (T_root == NULL)
			return T_root;
		node_ptr min_node = tree_minimum(T_root);
		node_ptr bottom_ptr = min_node->left;
		if (bottom_ptr != NULL)
			return bottom_ptr;
		bottom_ptr = bottom;
		bottom_ptr->p = min_node;
		min_node->left = bottom_ptr;
		return (bottom_ptr);
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::unlink_bottom_node()
	{
		if (T_root == NULL)
			return ;
		node_ptr min_node = tree_minimum(T_root);
		node_ptr bottom_ptr = min_node->left;
		if (bottom_ptr == NULL)
			return ;
		bottom_ptr->p = NULL;
		bottom_ptr->left = NULL;
		bottom_ptr->right = NULL;
		min_node->left = NULL;
		bottom_ptr = NULL;
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::node_ptr
	Red_Black_Tree<T, Compare, Allocator>::link_end_node()
	{
		if (T_root == NULL)
			return (T_root);
		node_ptr max_node = tree_maximum(T_root);
		node_ptr _end_ptr = max_node->right;
		if (_end_ptr != NULL)
			return _end_ptr;
		_end_ptr = _end;
		_end_ptr->p = max_node;
		max_node->right = _end_ptr;
		return _end_ptr;
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::node_ptr
	Red_Black_Tree<T, Compare, Allocator>::link_end_node() const
	{
		if (T_root == NULL)
			return (T_root);
		node_ptr max_node = tree_maximum(T_root);
		node_ptr _end_ptr = max_node->right;
		if (_end_ptr != NULL)
			return _end_ptr;
		_end_ptr = _end;
		_end_ptr->p = max_node;
		max_node->right = _end_ptr;
		return _end_ptr;
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::unlink_end_node()
	{
		if (T_root == NULL)
			return ;
		node_ptr max_node = tree_maximum(T_root);
		node_ptr _end_ptr = max_node->right;
		if (_end_ptr == NULL)
			return ;
		_end_ptr->p = NULL;
		_end_ptr->left = NULL;
		_end_ptr->right = NULL;
		max_node->right = NULL;
		_end_ptr = NULL;

	}
	///////////////link and unlink sentinels from the rbt///////////////////////

	////////////////////////////sentinels////////////////////////////

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::sentinel_end() // sentinel node
	{
		_end = node_alloc.allocate(1);
		alloc.construct(&(_end->value), value_type());
		_end->is_black = 1;
		_end->is_bottom_end = 1;
		_end->right = NULL;
		_end->left = NULL;
		//_end->left = _end;
		//_end->right = T_root; // let's T_root is a right child of end
		//T_root->p = _end;
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::sentinel_bottom() // sentinel node
	{
		bottom = node_alloc.allocate(1);
		alloc.construct(&(bottom->value), value_type());
		bottom->is_black = 1;
		bottom->is_bottom_end = 1;
		bottom->right = NULL;
		bottom->left = NULL;
		//bottom->right = bottom;
		//bottom->left = bottom;
	}
	////////////////////////////sentinels////////////////////////////

	////////////////////////////rbt methods////////////////////////////
	/* |										|
	   y		Left-Rotate(T,x)				x
	  / \		<---------------			   / \
	 x   c									  a   y
	/ \			--------------->				 / \
   a   b		Right-Rotate(T,y)				b	c						*/
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::left_rotate(node_ptr x)
	{
		node_ptr y = x->right; 		// 1)Denote the right child y.
		x->right = y->left; 		// 2)Now left child y is right child x.
		if (is_null(y->left) == 0)	// 3)If the left child of y != NULL, then we
			y->left->p = x;			// change the left child y parent to x.
		y->p = x->p;				// 4)Change parent y to parent x.
		if (is_null(x->p) == 1)			// 5) If x was root, then y becomes root.
			T_root = y;
		else if (x == x->p->left)	// 6) If x wasn't the root, then he was either
			x->p->left = y;			// a right or a left child. Making y either
		else						// the right or left child of father x.
			x->p->right = y;
		y->left = x;				// 7) now x is the left child of y.
		x->p = y;					// 8) now y is the parent of x.
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::right_rotate(node_ptr y)
	{
		node_ptr x = y->left;
		y->left = x->right;
		if (is_null(x->right) == 0)
			x->right->p = y;
		x->p = y->p;
		if (is_null(y->p) == 1)
			T_root = x;
		else if (y == y->p->right)
			y->p->right = x;
		else
			y->p->left = x;
		x->right = y;
		y->p = x;
	}

	////////////////////////////insert////////////////////////////
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_insert_fixup(node_ptr z)
	{
		while (z != NULL && z->p != NULL && z->p->is_black == 0)
		{
			if (z->p == z->p->p->left)
			{
				node_ptr y = z->p->p->right; // y is uncle of z
				if (is_null(y) == 0 && y->is_black == 0) // in the first case when uncle is red,
				{
					z->p->is_black = 1; // we colored the parent node of z to black
					y->is_black = 1; // and colored his uncle to black
					z->p->p->is_black = 0; // we colored his grandparent to red in order to keep the property 5 (about a black height)
					z = z->p->p; // and we move z to the grandparent's direction. (O(log(n)))
					/* However, making the grandparent of z red might cause violation of the property 4 there.
					   So, we will do the fixup again on that node. If the parent of z->p->p is also red,
					   violation of property 4 occur. */
				}
				else
				{
					if (z == z->p->right) // In the second case, the uncle of the node z (y) is black
					{					  // and the node z is the right child
						z = z->p;
						left_rotate(z); // We can transform the second case, into the third one by performing left rotation
					} // on the parent of the node z. Since both z and its parent are red, so rotation won't affect the black height.
					z->p->is_black = 1;     // In the second case, the uncle of the node z (y) is black
					z->p->p->is_black = 0;  // and the node z is the left child
					right_rotate(z->p->p);
				}
			}
			else if (z->p == z->p->p->right) // symmetric case
			{
				node_ptr y = z->p->p->left;
				if (is_null(y) == 0 && y->is_black == 0)
				{
					z->p->is_black = 1;
					y->is_black = 1;
					z->p->p->is_black = 0;
					z = z->p->p;
				}
				else
				{
					if (z == z->p->left)
					{
						z = z->p;
						right_rotate(z);
					}
					z->p->is_black = 1;
					z->p->p->is_black = 0;
					left_rotate(z->p->p);
				}
			}
		}
		T_root->is_black = 1; // In order to fix the property 2 and because it might be possible that case
		// 1 led the red node up till root
	}

	/* We can't insert any new node anywhere in a Red-Black-Tree (RBT) because the tree after the
	   insertion of the new node must follow the RBT property.
	   To insert an element, we first search for that element and if the element is not found, then we insert it. */
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_insert(node_ptr z)
	{
		node_ptr y = NULL; // (1) we need to make the last node in the below iteratation the parent of the new node. We use variable y for this.
		node_ptr x = T_root; // We will use a temprorary pointer (x) and go to the place where the node is going to be inserted.
		while (is_null(x) == 0)
		{
			y = x;
			if (z->value < y->value)
				x = x->left;
			else
				x = x->right;
		}
		z->p = y; // (1)
		if (is_null(y) == 1) // When the tree won't have any node, the new node will be the root of the tree and its
			T_root = z; // parent will be NULL. So, initially the value of y is NULL. In this case, the loop (while (x != NULL)) will also not run.
		else if (z->value < y->value)
			y->left = z;
		else
			y->right = z;
		z->left = NULL;
		z->right = NULL;
		z->is_black = 0; // color is red.
		rb_insert_fixup(z);
	}
	////////////////////////////insert////////////////////////////

	/* transplant a subtree rooted at node v in place of the subtree rooted at node u. */
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::transplant(node_ptr u, node_ptr v)
	{
		if (u->p == NULL)
			T_root = v;
		else if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
		if (v == NULL || u == NULL)
			return;
		v->p = u->p;
	}

	////////////////////////////delete////////////////////////////
	/* The violation of the property 5 (change in black height) is our main concern. We are going to
	   deal it with a bit different way. We are going to say that the property 5 has not been violated
	   and the node x which is now occupying y's original position has an "extra black" in it. */
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_delete_fixup(node_ptr x)
	{
		while (x != T_root && x != NULL && x->is_black == 1)
		{
			if (x == x->p->left) // if x is left child of his parent
			{
				node_ptr w = x->p->right; // (w is x's sibling)
				if (w->is_black == 0) // case 1 (w is red)
				{
					w->is_black = 1;
					x->p->is_black = 0;
					left_rotate(x->p);
					w = x->p->right;
				}
				if (w->left->is_black == 1 && w->right->is_black == 1) // case 2 (w is black and its both children are black)
				{
					w->is_black = 0;
					x = x->p;
				}
				else
				{
					if (w->right->is_black == 1) // case 3 (w is black and its right child is black and left child is red)
					{
						w->left->is_black = 1;
						w->is_black = 0;
						right_rotate(w);
						w = x->p->right;
					}
					w->is_black = x->p->is_black; // case 4 (w is black and its right child is red)
					x->p->is_black = 1;
					w->right->is_black = 1;
					left_rotate(x->p);
					x = T_root;
				}
			}
			else // if x is right child of his parent
			{
				node_ptr w = x->p->left;
				if (w->is_black == 0)
				{
					w->is_black = 1;
					x->p->is_black = 0;
					right_rotate(x->p);
					w = x->p->left;
				}
				if (w->right->is_black == 1 && w->left->is_black == 1)
				{
					w->is_black = 0;
					x = x->p;
				}
				else
				{
					if (w->left->is_black == 1)
					{
						w->right->is_black = 1;
						w->is_black = 0;
						left_rotate(w);
						w = x->p->left;
					}
					w->is_black = x->p->is_black;
					x->p->is_black = 1;
					w->left->is_black = 1;
					right_rotate(x->p);
					x = T_root;
				}
			}
		}
		if (x == NULL)
			return ;
		x->is_black = 1; // a) root always is black, b) if x is red we color him to black in order to fix property number 5
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_delete(node_ptr z)
	{
		node_ptr y = z; // let the node to be deleted be y
		bool y_original_color = y->is_black; // save the color of node to be deleted in original color
		node_ptr x; // it will occupy y's original position after its deletion. We need this variable in order to keep in control properties of the red-black tree.
		bool is_allocated = 0;

		if (is_null(z->left) == 1) // first case when the node (z) to be deleted hasn't the left child
		{
			x = z->right; // assign the right child of node to be deleted (z) to x
			transplant(z, z->right); // transplant node to be deleted with x
		}
		else if (is_null(z->right) == 1) // second case when the node (z) to be deleted hasn't the right child
		{
			x = z->left;
			transplant(z, z->left);
		}
		else // third case when the node (z) to be deleted has both the children
		{
			y = tree_minimum(z->right); /* In this case, we can find the smallest element of the right
			subtree (z's successor) of the node to be deleted (element with no left child in the right subtree) and replace
			its content with the node to be deleted. */
			y_original_color = y->is_black; // in order to save the color of the y, which we change in line 387
			x = y->right; // denote x with the right child of y
			if (x == NULL)
			{
				x = node_alloc.allocate(1);
				alloc.construct(&(x->value), value_type());
				x->is_bottom_end = 0;
				is_allocated = 1;
			}
			if (y->p == z) // If z is parent of y,
				x->p = y; // then y is parent of x
			else// Here, we have to put this minimum node (y) in the place of z.
			{
				transplant(y, y->right); // Firstly, we will transplant the right of y to y
				y->right = z->right; // and then take the right subtree of z and make it the right subtree of y.
				y->right->p = y; // And the parent of this right subtree now is y.
			}
			transplant(z, y); // After this, we will transplant y to z. It can also be possible that the minimum node is the direct child of the node z. In that case, we will just transplant y to z.
			y->left = z->left; // After this, we will change the left child of y to the left child of z.
			y->left->p = y; // And the parent of this left child now is y.
			y->is_black = z->is_black; // colored y as original color of z.
		}
		if (y_original_color == 1) // because it breaks the rule number 5, 4 and 2 - we need to fix this since we delete a black node.
			rb_delete_fixup(x);
		if (is_allocated == 1)
		{
			alloc.destroy(&x->value);
			node_alloc.deallocate(x, 1);
			x = NULL;
		}
	}
	////////////////////////////delete////////////////////////////
	////////////////////////////rbt methods////////////////////////////

	////////////////////////////constructors and destructor////////////////////////////
	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::Red_Black_Tree(): cmp(value_compare()), alloc(allocator_type()), T_root(NULL), _size(0)
	{
		sentinel_end();
		sentinel_bottom();
	}

	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::Red_Black_Tree(const value_compare& comp, const allocator_type& allocator):
						T_root(NULL), cmp(comp), alloc(allocator), _size(0)
	{
		sentinel_end();
		sentinel_bottom();
	}

	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::Red_Black_Tree(const Red_Black_Tree& copy): T_root(NULL), cmp(copy.cmp),
						alloc(copy.alloc), _size(0)
	{
		sentinel_end();
		sentinel_bottom();
	}

	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::~Red_Black_Tree()
	{
		clear();
		clear_bottom_end();
	}
	////////////////////////////constructors and destructor////////////////////////////

	////////////////////////////////////iterators/////////////////////////////////////
	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::iterator
	Red_Black_Tree<T, Compare, Allocator>::begin()
	{
		return iterator(_size == 0 ? T_root : tree_minimum(T_root));
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::const_iterator
	Red_Black_Tree<T, Compare, Allocator>::begin() const
	{
		return iterator(_size == 0 ? T_root : tree_minimum(T_root));
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::iterator
	Red_Black_Tree<T, Compare, Allocator>::end()
	{
		return iterator(link_end_node());
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::const_iterator
	Red_Black_Tree<T, Compare, Allocator>::end() const
	{
		return const_iterator(link_end_node());
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::reverse_iterator
	Red_Black_Tree<T, Compare, Allocator>::rbegin()
	{
		return reverse_iterator(end());
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::const_reverse_iterator
	Red_Black_Tree<T, Compare, Allocator>::rbegin() const
	{
		return const_reverse_iterator(end());
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::reverse_iterator
	Red_Black_Tree<T, Compare, Allocator>::rend()
	{
		return reverse_iterator(begin());
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::const_reverse_iterator
	Red_Black_Tree<T, Compare, Allocator>::rend() const
	{
		return const_reverse_iterator(begin());
	}
	////////////////////////////////////iterators/////////////////////////////////////

	////////////////////////////////////capacity/////////////////////////////////////
	template <class T, class Compare, class Allocator>
	bool Red_Black_Tree<T, Compare, Allocator>::empty() const
	{
		return _size == 0;
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::size_type
	Red_Black_Tree<T, Compare, Allocator>::size() const
	{
		return _size;
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::size_type
	Red_Black_Tree<T, Compare, Allocator>::max_size() const
	{
		return alloc.max_size();
	}
	////////////////////////////////////capacity/////////////////////////////////////

	////////////////////////////////////modifiers/////////////////////////////////////

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::insert(const value_type& value)
	{
		node_ptr z = node_alloc.allocate(1);
		z->is_black = 0; // RED
		z->is_bottom_end = 0;
		alloc.construct(&(z->value), value);
		unlink_end_node();
		unlink_bottom_node();
		rb_insert(z);
		_size++;
		link_end_node();
		link_bottom_node();
	}

	template <class T, class Compare, class Allocator>
	template <class InputIterator>
	void Red_Black_Tree<T, Compare, Allocator>::insert(InputIterator first, InputIterator last)
	{
		for(; first != last; ++first)
			insert(*first);
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::erase(const value_type& value)
	{
		if (T_root == NULL)
			return ;
		node_ptr z = T_root;
		unlink_end_node();
		unlink_bottom_node();
		while (z != NULL && z->value != value)
		{
			if (z->value < value)
				z = z->right;
			else
				z = z->left;
		}
		rb_delete(z);
		_size--;
		link_end_node();
		link_bottom_node();
	}

	template <class T, class Compare, class Allocator>
	template <class InputIterator>
	void Red_Black_Tree<T, Compare, Allocator>::erase(InputIterator it)
	{
		if (T_root == NULL)
			return ;
		node_ptr z = T_root;
		value_type value = *it;
		unlink_end_node();
		unlink_bottom_node();
		while (z != NULL && z->value != value)
		{
			if (z->value < value)
				z = z->right;
			else
				z = z->left;
		}
		rb_delete(z);
		_size--;
		link_end_node();
		link_bottom_node();
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::clear_node(node_ptr z)
	{
		if (z == NULL || is_null(z) == 1)
			return ;
		clear_node(z->left);
		clear_node(z->right);
		z->p = NULL;
		z->right = NULL;
		z->left = NULL;
		alloc.destroy(&z->value);
		node_alloc.deallocate(z, 1);
		z = NULL;
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::clear()
	{
		unlink_end_node();
		unlink_bottom_node();
		clear_node(T_root);
		T_root = NULL;
		_size = 0;
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::clear_bottom_end()
	{
		if (bottom != NULL)
		{
			alloc.destroy(&bottom->value);
			node_alloc.deallocate(bottom, 1);
			bottom = NULL;
		}
		if (_end != NULL)
		{
			alloc.destroy(&_end->value);
			node_alloc.deallocate(_end, 1);
			_end = NULL;
		}
	}
	////////////////////////////////////modifiers/////////////////////////////////////

	////////////////////////////////////operations (lookup)/////////////////////////////////////
	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::size_type
	Red_Black_Tree<T, Compare, Allocator>::count(const Key& key) const
	{
		node_ptr tmp = T_root;
		while (tmp != NULL)
		{
			if (cmp(key, tmp->value.first) == 1)
				tmp = tmp->left;
			else if (cmp(tmp->value.first, key) == 1)
				tmp = tmp->right;
			else
				return 1;
		}
		return 0;
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::iterator
	Red_Black_Tree<T, Compare, Allocator>::find(const Key& key)
	{
		iterator it = lower_bound(key);
		if (it != end() && cmp(key, (*it).first) == 0)
			return it;
		return end();
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::const_iterator
	Red_Black_Tree<T, Compare, Allocator>::find(const Key& key) const
	{
		iterator it = lower_bound(key);
		if (it != end() && cmp(key, (*it).first) == 0)
			return it;
		return end();
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	pair<typename Red_Black_Tree<T, Compare, Allocator>::iterator, typename Red_Black_Tree<T, Compare, Allocator>::iterator>
	Red_Black_Tree<T, Compare, Allocator>::equal_range(const Key& key)
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while (tmp != NULL)
		{
			if (cmp(key, tmp->value.first) == 1)
			{
				res = tmp;
				tmp = tmp->left;
			}
			else if (cmp(tmp->value.first, key) == 1)
				tmp = tmp->right;
			else
				return pair<iterator, iterator>(iterator(tmp), iterator(tmp->right != NULL ? tree_minimum(tmp->right) : res));
		}
		return pair<iterator, iterator>(iterator(res), iterator(res));
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	pair<typename Red_Black_Tree<T, Compare, Allocator>::const_iterator, typename Red_Black_Tree<T, Compare, Allocator>::const_iterator>
	Red_Black_Tree<T, Compare, Allocator>::equal_range(const Key& key) const
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while (tmp != NULL)
		{
			if (cmp(key, tmp->value.first) == 1)
			{
				res = tmp;
				tmp = tmp->left;
			}
			else if (cmp(tmp->value.first, key) == 1)
				tmp = tmp->right;
			else
				return pair<const_iterator, const_iterator>(const_iterator(tmp), const_iterator(tmp->right != NULL ? tree_minimum(tmp->right) : res));
		}
		return pair<const_iterator, const_iterator>(const_iterator(res), const_iterator(res));
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::iterator
	Red_Black_Tree<T, Compare, Allocator>::lower_bound(const Key& key)
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while(tmp != NULL)
		{
			if (cmp(tmp->value.first, key) == 0)
			{
				res = tmp;
				tmp = tmp->left;
			}
			else
				tmp = tmp->right;
		}
		return (iterator)(res);
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::const_iterator
	Red_Black_Tree<T, Compare, Allocator>::lower_bound(const Key& key) const
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while (tmp != NULL)
		{
			if (cmp(tmp->value.first, key) == 0) // 0 = false
			{
				res = tmp;
				tmp = tmp->left;
			}
			else
				tmp = tmp->right;
		}
		return (const_iterator)(res);
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::iterator
	Red_Black_Tree<T, Compare, Allocator>::upper_bound(const Key& key)
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while (tmp != NULL)
		{
			if (cmp(key, tmp->value.first) == 1) // 1 = true
			{
				res = tmp;
				tmp = tmp->left;
			}
			else
				tmp = tmp->right;
		}
		return (iterator)(res);
	}

	template <class T, class Compare, class Allocator>
	template <class Key>
	typename Red_Black_Tree<T, Compare, Allocator>::const_iterator
	Red_Black_Tree<T, Compare, Allocator>::upper_bound(const Key& key) const
	{
		node_ptr tmp = T_root;
		node_ptr res = link_end_node();
		while (tmp != NULL)
		{
			if (cmp(key, tmp->value.first) == 1) // 1 = true
			{
				res = tmp;
				tmp = tmp->left;
			}
			else
				tmp = tmp->right;
		}
		return (const_iterator)(res);
	}

	template <class T, class Compare, class Allocator>
	void Red_Black_Tree<T, Compare, Allocator>::swap(Red_Black_Tree& other)
	{
		std::swap(this->T_root, other.T_root);
		std::swap(this->cmp, other.cmp);
		std::swap(this->alloc, other.alloc);
		std::swap(this->node_alloc, other.node_alloc);
		std::swap(this->bottom, other.bottom);
		std::swap(this->_end, other._end);
		std::swap(this->_size, other._size);
	}
	////////////////////////////////////operations (lookup)/////////////////////////////////////

	////////////////////////////allocator and value_compare/////////////////////////////////////
	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::allocator_type
	Red_Black_Tree<T, Compare, Allocator>::get_allocator() const
	{
		return alloc;
	}

	template <class T, class Compare, class Allocator>
	typename Red_Black_Tree<T, Compare, Allocator>::value_compare
	Red_Black_Tree<T, Compare, Allocator>::get_value_compare() const
	{
		return cmp;
	}
	////////////////////////////allocator and value_compare/////////////////////////////////////
}

#endif
