#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <algorithm>
#include "Red_Black_Tree_Iterator.hpp"
#include "map.hpp"

namespace ft
{
	template <class T>
	class rbt_node // node of red-black tree
	{
		public:
				typedef rbt_node<T>* node_ptr; // pointer to type T
				typedef T value_type; // type of the value

				value_type	key; // value of the node
				node_ptr	left; // left child node
				node_ptr	right; // right child node
				node_ptr	p; // parent node
				bool		is_black; // if is_black == 1 color of the node is black otherwise is red
				bool		is_end_rend; // check the node in situations end() and rend() when we can't have an access to the content of the node, and attempting to access it results in undefined behavior

				// constructors, destructor and assign operator
				rbt_node(): key(-1), left(NULL), right(NULL), p(NULL), is_black(0), is_end_rend(0) {} // default constructor
				rbt_node(value_type k, node_ptr l, node_ptr r, node_ptr parent, bool b): //constructor with parameters
						key(k), left(l), right(r), p(parent), is_black(b), is_end_rend(0) {}
				rbt_node(const rbt_node&) {} // copy constructor
				~rbt_node() {} // destructor
				rbt_node& operator=(const rbt_node&) {} // assign operator
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
		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	/* this method finds the biggest key in the tree */
	template  <class Node_Ptr>
	Node_Ptr tree_maximum(Node_Ptr x)
	{
		while (x->right != NULL)
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
				typedef typename allocator_type::size_type size_type;
				typedef typename allocator_type::difference_type difference_type;
		private:
				node_ptr T_root; // root of the red-black tree
				node_ptr T_null; // use the one sentinel T_null to represent all the NULLs - all leaves and the root's parent.
				value_compare cmp;
				allocator_type alloc;
				allocator_node_type node_alloc; // allocator for node
				node_ptr rend; // element preceding the first element of the non-reversed vector (sentinel node)
				node_ptr end; // element foolowing the last element (sentinel node).
				size_type size;
		public:
				explicit Red_Black_Tree(const value_compare& comp, const allocator_type& allocator);
				Red_Black_Tree(const Red_Black_Tree& copy);
				~Red_Black_Tree();

		private:
				// sentinels
				void	define_T_null();
				void	define_end();
				void	define_rend();
				// rbt methods
				void left_rotate(node_ptr x);
				void right_rotate(node_ptr x);
				void rb_insert(node_ptr z);
				void rb_insert_fixup(node_ptr z);
				void transplant(node_ptr u, node_ptr v);
				void rb_delete(node_ptr z);
				void rb_delete_fixup(node_ptr z);
				template <class, class, class, class> friend class map;
	};
	////////////////////////////RBT Class////////////////////////////

	////////////////////////////sentinels////////////////////////////
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::define_T_null() // sentinel node
	{
		T_null = node_alloc.allocate(1);
		node_alloc.construct(T_null, rbt_node());
		this->T_null->is_black = 1;
		this->T_null->left = this->T_null;
		this->T_null->right = this->T_null;
		this->T_root = this->T_null;
		this->T_root->is_black = 1;
		this->T_null->p = this->p;
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::define_end() // sentinel node
	{
		end = node_alloc.allocate(1);
		node_alloc.construct(end->key, rbt_node());
		end->key = alloc.allocate(1);
		alloc.construct(end->key, value_type());
		end->color = 1;
		end->is_end_rend = 1;
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::define_rend() // sentinel node
	{
		rend = node_alloc.allocate(1);
		node_alloc.construct(rend->key, rbt_node());
		rend->key = alloc.allocate(1);
		alloc.construct(rend->key, value_type());
		rend->color = 1;
		rend->is_end_rend = 1;
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
		if (y != T_null)				// 3)If the left child of y != NULL, then we
			y->left->p = x;			// change the left child y parent to x.
		y->p = x->p;				// 4)Change parent y to parent x.
		if (x->p == T_null)			// 5) If x was root, then y becomes root.
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
		y->left = x.right;
		if (x->right != T_null)
			x->right->p = y;
		x->p = y->p;
		if (y->p == T_null)
			T_root = x;
		else if (y == y->p->right)
			y->p->right = x;
		else
			y->parent->left = x;
		x->right = y;
		y->p = x;
	}

	////////////////////////////insert////////////////////////////
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_insert_fixup(node_ptr z)
	{
		while (z->p->is_black == 0)
		{
			if (z->p == z->p->p->left)
			{
				node_ptr y = z->p->p->right; // y is uncle of z
				if (y->is_black == 0) // in the first case when uncle is red,
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
				if (y->is_black == 0)
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
		node_ptr y = T_null; // (1) we need to make the last node in the below iteratation the parent of the new node. We use variable y for this.
		node_ptr x = T_root; // We will use a temprorary pointer (x) and go to the place where the node is going to be inserted.
		while (x != T_null)
		{
			y = x;
			if (z->key < y->key)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y; // (1)
		if (y == T_null) // When the tree won't have any node, the new node will be the root of the tree and its
			T_root = z; // parent will be NULL. So, initially the value of y is NULL. In this case, the loop (while (x != NULL)) will also not run.
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
		z->left = T_null;
		z.right = T_null;
		z.is_black = 0; // color is red.
		insert_fixup(z);
	}
	////////////////////////////insert////////////////////////////

	/* transplant a subtree rooted at node v in place of the subtree rooted at node u. */
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::transplant(node_ptr u, node_ptr v)
	{
		if (u->p == T_null)
			T_root = v;
		else if (u == u->p->left)
			u->p->left = v;
		else
			u->p->right = v;
		v->p = u->p;
	}

	////////////////////////////delete////////////////////////////
	/* The violation of the property 5 (change in black height) is our main concern. We are going to
	   deal it with a bit different way. We are going to say that the property 5 has not been violated
	   and the node x which is now occupying y's original position has an "extra black" in it. */
	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_delete_fixup(node_ptr x)
	{
		while (x != T_root && x->is_black == 1)
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
						w->left->is_black == 1;
						w->is_black = 0;
						right_rotate(w);
						w = x->p->right;
					}
					w->is_black = x->p->is_black; // case 4 (w is black and its right child is red)
					x->p->is_black = 1;
					w->right->is_black == 1;
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
						w->right->is_black == 1;
						w->is_black = 0;
						left_rotate(w);
						w = x->p->left;
					}
					w->is_black = x->p->is_black;
					x->p->is_black = 1;
					w->left->is_black == 1;
					right_rotate(x->p);
					x = T_root;
				}
			}
		}
		x->is_black = 1; // a) root always is black, b) if x is red we color him to black in order to fix property number 5
	}

	template <class T, class Compare, class Allocator>
	void	Red_Black_Tree<T, Compare, Allocator>::rb_delete(node_ptr z)
	{
		node_ptr y = z; // let the node to be deleted be y
		bool y_original_color = y->is_black; // save the color of node to be deleted in original color
		node_ptr x; // it will occupy y's original position after its deletion. We need this variable in order to keep in control properties of the red-black tree.

		if (z->left == T_null) // first case when the node (z) to be deleted hasn't the left child
		{
			x = z->right; // assign the right child of node to be deleted (z) to x
			transplant(z, z->right); // transplant node to be deleted with x
		}
		else if (z->right == T_null) // second case when the node (z) to be deleted hasn't the right child
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
			if (y->p == z) // If z is parent of y,
				x->p = y; // then y is parent of x
			else // Here, we have to put this minimum node (y) in the place of z.
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
	}
	////////////////////////////delete////////////////////////////
	////////////////////////////rbt methods////////////////////////////

	////////////////////////////constructors and destructor////////////////////////////
	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::Red_Black_Tree(const value_compare& comp, const allocator_type& allocator):
						cmp(comp), alloc(allocator), T_root(NULL), size(0)
	{
		define_T_null();
		define_end();
		define_rend();
	}

	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::Red_Black_Tree(const Red_Black_Tree& copy): cmp(copy.cmp), alloc(copy.alloc),
						node_alloc(copy.node_alloc), T_null(copy.T_null), T_root(copy.T_root), end(copy.end), rend(copy.rend), size(copy.size)
	{

	}

	template <class T, class Compare, class Allocator>
	Red_Black_Tree<T, Compare, Allocator>::~Red_Black_Tree()
	{

	}
	////////////////////////////constructors and destructor////////////////////////////
}

#endif
