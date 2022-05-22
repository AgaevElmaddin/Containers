#ifndef VECTOR_HPP
# define VECTOR_HPP


#include "iterators_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "make_pair.hpp"
#include "reverse_iterator.hpp"
#include "is_iterator.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <limits>
#include <algorithm>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
				// member types.
				//************************************************************************************************************//
				// A type that represents the data type stored in a vector
				typedef T value_type;
				// A type that represents the allocator class for the vector object
				typedef Allocator allocator_type;
				// A type that counts the number of elements in the vector
				typedef std::size_t size_type;
				// A type that provides the difference between the addresses of two elements in a vector
				typedef std::ptrdiff_t difference_type;
				// A type that provides a reference to an element stored in a vector
				typedef value_type& reference;
				// A type that provides a reference to a const element stored in a vector. It's used for reading and doing const operations
				typedef const value_type& const_reference;
				// A type that provides a pointer to an element in a vector
				typedef typename Allocator::pointer pointer;
				// A type that provides a pointer to a const element in a vector
				typedef typename Allocator::const_pointer const_pointer;
				// A type that provides a random-access iterator that can read or modify any element in a vector.
				// Random-access iterators are the ones whose functionality is same as pointers
				// typedef std::__wrap_iter<pointer> iterator;
				typedef typename ft::iterator_traits<pointer>::pointer iterator;
				// A type that provides a random-access iterator that can read a const element in a vector
				// typedef std::__wrap_iter<const_pointer> const_iterator;
				typedef typename ft::iterator_traits<const_pointer>::pointer const_iterator;
				// A type that provides a random-access iterator that can read or modify any element in a reversed vector
				typedef ft::reverse_iterator<iterator> reverse_iterator;
				// A type that provides a random-access iterator that can read any const element in the vector
				typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
				//************************************************************************************************************//

				// member functions prototypes
				//********************************************************************************************************************************************//
				explicit vector(const allocator_type& alloc = allocator_type()); // default constructor *****************************************************//
				explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); // fill constructor ****//
				template <class InputIterator> // range constructor ***************************************************************************************//
				vector(InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
				const allocator_type& alloc = allocator_type()
						); // *********************************//
				vector(const vector& x); // copy constructor ******************************************************************************************//
				~vector(); // destructor *************************************************************************************************************//
				//***********************************************************************************************************************************//

				// operator=
				vector& operator=(const vector& x);

				// Iterators
				//************************************************************************************************************//
				iterator begin(); //*****************************************************************************************//
				const_iterator begin() const; //****************************************************************************//
				iterator end(); //*****************************************************************************************//
				const_iterator end() const; //****************************************************************************//
				reverse_iterator rbegin(); //****************************************************************************//
				const_reverse_iterator rbegin() const; //***************************************************************//
				reverse_iterator rend(); //****************************************************************************//
				const_reverse_iterator rend() const; //***************************************************************//
				//***************************************************************************************************//

				// Capacity
				//************************************************************************************************************//
				size_type size() const; //***********************************************************************************//
				size_type max_size() const; //******************************************************************************//
				void resize(size_type n, value_type val = value_type()); //************************************************//
				size_type capacity() const; //****************************************************************************//
				bool empty() const; //***********************************************************************************//
				void reserve(size_type n); //***************************************************************************//
				//*****************************************************************************************************//

				// Element access
				//************************************************************************************************************//
				reference operator[] (size_type n);
				const_reference operator[] (size_type n) const;
				reference at (size_type n);
				const_reference at (size_type n) const;
				reference front();
				const_reference front () const;
				reference back();
				const_reference back () const;
				//************************************************************************************************************//

				// Modifiers
				//******************************************************************************************************************************************************//
				template <class InputIterator> //************************************************************************************************* 1) range assign ****//
				typename enable_if<!is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last); //********************************//
				void assign(size_type n, const value_type& val); //****************************************************************************** 2) fill assign ****//
				void push_back(const value_type& val); //**************************************************************************************** 3) push_back *****//
				void pop_back(); //************************************************************************************************************** 4) pop_back *****//
				iterator insert(iterator position, const value_type& val); //******************************************************* 5) single element insert ****//
				void insert(iterator position, size_type n, const value_type& val); //****************************************************** 6) fill insert *****//
				template <class InputIterator> //****************************************************************************************** 7) range insert ****//
				typename enable_if<!is_integral<InputIterator>::value, void>::type insert(iterator position, InputIterator first, InputIterator last); //******//
				iterator erase(iterator position); //**************************************************************************** 8) single element erase ****//
				iterator erase(iterator first, iterator last); //************************************************************************ 9) range erase ****//
				void swap(vector& x); //****************************************************************************************************** 10) swap ****//
				void clear(); //************************************************************************************************************ 11) clear ****//
				//****************************************************************************************************************************************//

				//Allocator: get allocator
				allocator_type	get_allocator() const;
		private:
				allocator_type alloc;
				pointer v_begin;
				pointer v_end;
				pointer v_capacity_end;
	};

	//default constructor - constructs an empty container, with no elements.
	template <class T, class Allocator>
	vector<T, Allocator>::vector(const allocator_type& alloc):
								alloc(alloc), v_begin(0), v_end(0), v_capacity_end(0)
	{
		//std::cout << "default constructor for vector!" << std::endl;
	}

	/* fill constructor (n - the size of the container, val - the value to initialize elements of the container with, alloc -
	   allocator to use for all memory allocations of this container).
	   Constructs a container with n elements. Each element is a copy of val												*/
	template <class T, class Allocator>
	vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& alloc):
								alloc(alloc), v_begin(0), v_end(0), v_capacity_end(0)
	{
		v_begin = this->alloc.allocate(n);
		v_capacity_end = v_begin + n;
		v_end = v_begin;
		while (n--)
		{
			this->alloc.construct(v_end, val);
			v_end++;
		}
		//std::cout << "fill constructor for vector!" << std::endl;
	}

	/* range constructor: constructs the container with the contents of the range [first, last).
	   This constructor has the same effect as
	   vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
	   if InputIterator is an integral type.*/
	template <class T, class Allocator>
	template <class InputIterator>
	// ft::enable<ft::is_iterator<ft::iterator_traits<InputIterator>::iterator_category>::value_type, InputIterator>::type
	vector<T, Allocator>::vector(InputIterator first,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
						const allocator_type& alloc):alloc(alloc)
	{
		difference_type n = ft::distance(first, last);
		v_begin = this->alloc.allocate(n);
		v_capacity_end = v_begin + n;
		v_end = v_begin;
		while (n--)
		{
			this->alloc.construct(v_end, *first++);
			v_end++;
		}
		//std::cout << "range constructor for vector!" << std::endl;
	}

	// copy constructor - constructs a container with a copy of each of the element in x, in the same order
	template <class T, class Allocator>
	vector<T, Allocator>::vector(const vector& x): alloc(x.alloc), v_begin(0), v_end(0), v_capacity_end(0)
	{
		size_type n = x.size();
		pointer x_begin = x.v_begin;

		if (n > 0)
		{
			if (2 * n > max_size())
				throw std::length_error("Exception because of length of vector");
			this->v_begin = this->v_end = this->alloc.allocate(2 * n);
			v_capacity_end = v_begin + 2 * n;
			for (size_type i = 0; i < n; ++i, ++this->v_end, ++x_begin)
				this->alloc.construct(this->v_end, *x_begin);
		}
	}

	/* destructor. This destroys all container elements, and deallocates all the storage capacity
	   allocated by the vector using its allocator.												 */
	template <class T, class Allocator>
	vector<T, Allocator>::~vector()
	{
		this->clear();
		alloc.deallocate(this->v_begin, this->capacity());
	}

	// operator= Copies all the elements from x into the container.
	template <class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator= (const vector& x)
	{
		if (this != &x)
		{
			this->alloc = x.alloc;
			for (size_type i = 0; i < this->capacity(); ++i)
				this->alloc.destroy(this->v_begin + i);
			this->alloc.deallocate(this->v_begin, this->capacity());
			this->v_begin = this->v_end = this->v_capacity_end = 0;
			for (pointer i = x.v_begin; i < x.v_end; ++i)
				this->push_back(*i);
		}
		return *this;
	}

	// Iterators
	//*********************************************************************************************************************************//
	template <class T, class Allocator> 									//********************************************************//
	typename vector <T, Allocator>::iterator vector<T, Allocator>::begin() // return iterator to begining ***************************//
	{																	  //********************************************************//
		return (vector <T, Allocator>::iterator)this->v_begin;			 //********************************************************//
	}																	//********************************************************//

	template <class T, class Allocator>								  //********************************************************//
	typename vector <T, Allocator>::const_iterator vector<T, Allocator>::begin() const // return const_iterator to begining ***//
	{																//********************************************************//
		return (vector <T, Allocator>::iterator)this->v_begin;	   //********************************************************//
	}															  //********************************************************//

	template <class T, class Allocator>							//********************************************************//
	typename vector <T, Allocator>::iterator vector<T, Allocator>::end() // return iterator to end **********************//
	{														  //********************************************************//
		return iterator(this->v_end); //********************************************************//
	}														//********************************************************//

	template <class T, class Allocator>					  //********************************************************//
	typename vector <T, Allocator>::const_iterator vector<T, Allocator>::end() const //****************************//
	{													//********************** return const_iterator to end ****//
		return const_iterator(this->v_end); //**************************************************//
	}												  //********************************************************//

	template <class T, class Allocator>				//********************************************************//
	typename vector <T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() //***********************//
	{											  //********************************************************//
		return reverse_iterator(this->end());  //*********** return reverse_iterator to reverse beginning//
	}											//********************************************************//

	template <class T, class Allocator>		  //********************************************************//
	typename vector <T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const //*****//
	{										//********************************************************//
		return reverse_iterator(this->end()); // return const_reverse_iterator to reverse beginning//
	}									  //********************************************************//

	template <class T, class Allocator> //********************************************************//
	typename vector <T, Allocator>::reverse_iterator vector<T, Allocator>::rend() //*************//
	{								  //********************************************************//
		return reverse_iterator(this->begin()); //** return reverse_iterator to reverse end *//
	}								//********************************************************//

	template <class T, class Allocator> //**************************************************//
	typename vector <T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const
	{							//********************************************************//
		return reverse_iterator(this->begin()); //*************************************//
	}						  //************return const_reverse_iterator to reverse end//
	//*********************************************************************************//

	// Capacity
	//*********************************************************************************
	/* Returns the number of elements in the vector. This is the number of actual objects
	   held in the vector, which is not necessarily equal to its storage capacity.		  */
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
	{
		return (this->v_end - this->v_begin);
	}
	////////////////////////////////////////////////////////////////////////////////////////
	/* Returns the maximum number of elements that the vector can hold. This is the maximum
	   potential size the container can reach due to known system or library implementation
	   limitations, but the container is by no means guaranteed to be able to reach that size:
	   it can still fail to allocate storage at any point before that size is reached. 		*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
	{
		return this->alloc.max_size();
	}
	////////////////////////////////////////////////////////////////////////////////////////
	/* Change size. Resizes the container so that it contains n elements.
	   (1)If n is smaller than the current container size, the content is reduced to its first n elements,
	   removing those beyond (and destroying them).
	   (2)If n is greater than the current container size, the content is expanded by inserting at the end
	   as many elements as needed to reach a size of n. If val is specified, the new elements are
	   initialized as copies of val, otherwise, they are value-initialized.
	   (3)If n is also greater than the current container capacity, an automatic reallocation of the allocated
	   storage space takes place.
	   Notice that this function changes the actual content of the container by inserting or erasing elements
	   from it.																									*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::resize(size_type n, value_type val)
	{
		if (n > this->capacity()) // (3)
			this->reserve(n);
		for (pointer i = this->v_end; i < this->v_begin + n; ++i) // (2)
			this->alloc.construct(i, val);
		if (n < this->size())
		{
			for (pointer i = this->v_begin + n; i < this->v_end; ++i)
				this->alloc.destroy(i);
		}
		this->v_end = this->v_begin + n;
	}
	////////////////////////////////////////////////////////////////////////////////////////
	/* Return size of allocated storage capacity. Returns the size of the storage space currently
	  allocated for the vector, expressed in terms of elements.
	  This capacity is not necessarilly equal to the vector size. It can be equal or greater, with the extra
	  space allowing to accommodate for growth without the need to reallocate on each insrtion.
	  Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is
	  exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space).
	  The theoretical limit on the size of a vector is given by member max_size.
	  The capacity of a vector can be explicitly altered by calling member vector::reserve.						*/
	  template <class T, class Allocator>
	  typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const
	  {
		  return static_cast<size_type>(this->v_capacity_end - this->v_begin);
	  }
	////////////////////////////////////////////////////////////////////////////////////////
	// Test whether vector is empty
	template <class T, class Allocator>
	bool vector<T, Allocator>::empty() const
	{
		return (this->v_begin == this->v_end);
	}
	////////////////////////////////////////////////////////////////////////////////////////
	/* Request a change in capacity. Requests that the vector capacity be at least enough to contain n elements.
	   If n is greater than the current vector capacity, the function causes the container to reallocate its storage
	   increasing its capacity to n (or greater).
	   In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
	   This function has no effect on the vector size and cannot alter its elements.									*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::reserve(size_type n)
	{
		if (n > this->max_size())
			throw (std::length_error("Error(vector): attempts to exceed implementation defined length limits."));
		else if (n > this->capacity())
		{
			size_t size = this->v_end - this->v_begin;
			pointer new_begin;
			new_begin = this->alloc.allocate(n);
			for (size_t i = 0; i < size; i++)
				this->alloc.construct(new_begin + i, *(this->v_begin + i));
			for (size_type i = 0; i < this->capacity(); i++)
				this->alloc.destroy(this->v_begin + i);
			this->alloc.deallocate(this->v_begin, this->capacity());
			this->v_begin = new_begin;
			this->v_end = this->v_begin + size;
			this->v_capacity_end = this->v_begin + n;
		}
	}
	/* std::length error - defines a type of object to be thrown as exception. It reports errors that
	   result from attempts to exceed implementation defined length limits for some object.
	   This exception is thrown by member functions of std::basic_string and std::vector::reserve.
	   length_error(const std::string& what_arg), where what_arg - explanatory string.*/
	//*********************************************************************************

	// Element access
	//***********************************************************************************************************
	/* Returns a reference to the element at position n in the vector container.
	   A similar member function, vector::at, has the same behaviour as this operator function, except that
	   vector::at is bound-checked and signals if the requested position is out of range by throwing an
	   out_of_range exception.
	   Portable programs should never call this function with an argument n that is out of range, since
	   this causes undefined behavior.																		*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::operator[] (size_type n)
	{
		return *(this->v_begin + n);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[] (size_type n) const
	{
		return *(this->v_begin + n);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Returns a reference to the element at position n in the vector.
	   The function automatically checks whether n is within the bounds of valid elements in the vector,
	   throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
	   This is in contrast with member operator[], that does not check against bounds.							*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type n)
	{
		if (n >= static_cast<size_type>(this->v_end - this->v_begin))
			throw std::out_of_range("vector");
		return this->v_begin[n];
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type n) const
	{
		if (n >= static_cast<size_type>(this->v_end - this->v_begin))
			throw std::out_of_range("vector");
		return this->v_begin[n];
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Access first element. Returns a reference to the first element in the vector.
	   Unlike member vector::begin, which returns an iterator to this same element, this function returns a
	   direct reference. Calling this function on an empty container causes undefined behavior.					*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::front()
	{
		return *(this->v_begin);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const
	{
		return *(this->v_begin);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Access last element. Returns a reference to the last element in the vector.
	   Unlike member vector::end, which returns an iterator just past this element, this function returns a
	   direct reference. Calling this function on an empty container causes undefined behaviour.				*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::back()
	{
		return *(this->v_end - 1);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const
	{
		return *(this->v_end - 1);
	}
	//***********************************************************************************************************

	// Modifiers
	//************************************************************************************************************
	/*1) In the range version 1), the new contents are elements constructed from each of the elements in the
	  range between first and last, in the same order.
	  Any elements held in the container before the call are destroyed and replaced by newly constructed
	  elements (no assignments of elements take place)
	  This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size
	  surpasses the current vector capacity																		*/
	template <class T, class Allocator>
	template <class InputIterator>
	typename enable_if<!is_integral<InputIterator>::value, void>::type vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		this->clear();
		for ( ; first != last; ++first)
			this->push_back(*first);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 2) In the fill version 2), the new contents are n elements, each initialized to a copy of val.
	   Any elements held in the container before the call are destroyed and replaced by newly constructed
	   elements (no assignments of elements take place)
	   This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size
	   surpasses the current vector capacity																	*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::assign(size_type n, const value_type& val)
	{
		this->clear();
		for (size_type i = 0; i < n; ++i)
			this->push_back(val);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 3) Add element at the end. Adds a new element at the end of the vector, after its current last element.
	   The content of val is copied (or moved) to the new element.
	   This effectively increases the container size by one, which causes an automatic reallocation of the
	   allocated storage space if -and only if- the new vector size surpasses the current vector capacity. */
	template <class T, class Allocator>
	void	vector<T, Allocator>::push_back(const value_type& val)
	{
		if (this->v_end == this->v_capacity_end)
			this->reserve(2 * (this->capacity() > 0 ? this->capacity() : 1));
		this->alloc.construct(this->v_end, val);
		this->v_end++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 4) Delete last element. Removes the last element in the vector, effectively reducing the container size
	   by one. This destroys the removed element.																*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::pop_back()
	{
		this->alloc.destroy(this->v_end - 1);
		std::cout << "here" << std::endl;
		--(this->v_end);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Insert elements. The vector is extended by inserting new elements before the element at the specified
	   position, effectively increasing the container size by the number of elements inserted.
	   Thid causes an automatic reallocation of the allocated storage space if -and only if- the new vector size
	   surpasses the current vector capacity.
	   Because vectors use an array as their underlying storage, inserting elements in positions other than the
	   vector end causes the container to relocate all the elements that were after position to their new positions.
	   This is generally an inefficient operation compared to the one performed for the same operation by other kinds of
	   sequence containers (such as list or forward_list).
	   5) single element insert. Parameters: position - position in the vector where the new elements are inserted.
	   val - value to be copied (or moved) to the inserted elements													*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator position, const value_type& val)
	{
		difference_type start = position - begin();
		if (position == this->v_end - 1)
			this->push_back(val);
		else
		{
			size_type new_capacity = (this->size() < this->capacity()) ? this->capacity() : 2 * this->capacity();
			pointer new_begin = this->alloc.allocate(new_capacity);
			size_type i = 0;
			for ( ; i < static_cast<size_type>(position - this->v_begin); ++i)
				this->alloc.construct(new_begin + i, *(this->v_begin + i)); // insert element(s) before the position
			this->alloc.construct(new_begin + i, val); // insert position
			for ( ; i < this->size(); ++i)
				this->alloc.construct(new_begin + i + 1, *(this->v_begin + i)); // insert element(s) after the position
			this->clear();
			this->alloc.deallocate(this->v_begin, this->capacity());
			this->v_begin = new_begin;
			this->v_end = new_begin + i + 1;
			this->v_capacity_end = new_begin + new_capacity;
		}
		return static_cast<iterator>(this->v_begin + start);
	}

	// 6) fill insert: n - number of elements to insert. Each element is initialized to a copy of val.
	template <class T, class Allocator>
	void	vector<T, Allocator>::insert(iterator position, size_type n, const value_type& val)
	{
		 if (position == this->v_end - 1)
		 {
				pointer new_begin = this->alloc.allocate(n + this->size());
				size_type i = 0;
				size_type j = 0;
				for ( ; i < n; ++i, ++j)
					this->alloc.construct(new_begin + i, val);
				for ( ; i < n + this->size(); ++i, ++j)
					this->alloc.construct(new_begin + i, *(this->v_end - 1));
				 this->clear();
				 this->alloc.deallocate(this->v_begin, this->size());
				this->v_begin = new_begin;
				this->v_end = new_begin + i;
				this->v_capacity_end = new_begin + i + j;
		 }
		else
		{
			size_type new_capacity = (this->size() < this->capacity()) ? this->capacity() : 2 * this->capacity();
			pointer new_begin = this->alloc.allocate(new_capacity);
			size_type i = 0;
			size_type j = 0;
			for ( ; i < static_cast<size_type>(position - this->v_begin); ++i)
				this->alloc.construct(new_begin + i, *(this->v_begin + i));
			for (pointer it = position; it < position + n; ++it, ++j)
				this->alloc.construct(new_begin + i + j, val);
			for ( ; i < this->size(); ++i)
				this->alloc.construct(new_begin + i + j, *(this->v_begin + i));
			this->clear();
			this->alloc.deallocate(this->v_begin, this->capacity());
			this->v_begin = new_begin;
			this->v_end = new_begin + i + j;
			this->v_capacity_end = new_begin + new_capacity;
		}
	}

	/* 7) range insert: [first, last) - iterators specifying a range of elements. Copies of the elements in the range
	   [first, last) are inserted at position (in the same order).
	   The function template argument InputIterator shall be an input iterator type that points to elements of a type
	   from which value_type objects can be constructed.															*/
	template <class T, class Allocator>
	template <class InputIterator>
	typename enable_if<!is_integral<InputIterator>::value, void>::type vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
	{
		if (position == this->v_end - 1)
			for (InputIterator it = first; it != last; ++it)
				this->push_back(*it);
		else
		{
			size_type new_capacity = (this->size() < this->capacity()) ? this->capacity() : 2 * this->capacity();
			pointer new_begin = this->alloc.allocate(new_capacity);
			size_type i = 0;
			size_type j = 0;
			for ( ; i < static_cast<size_type>(position - this->v_begin); ++i)
				this->alloc.construct(new_begin + i, *(this->v_begin + i));
			for (InputIterator it = first; it != last; ++it, ++j)
				this->alloc.construct(new_begin + i + j, *it);
			for ( ; i < this->size(); ++i)
				this->alloc.construct(new_begin + i + j, *(this->v_begin + i));
			this->clear();
			this->alloc.deallocate(this->v_begin, this->capacity());
			this->v_begin = new_begin;
			this->v_end = new_begin + i + j;
			this->v_capacity_end = new_begin + new_capacity + i + j;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 8), 9) Erase elements. Removes from the vector either a single element (position) or a range of elements ([first, last)).
	   This effectively reduces the container size by the number of elements removed, which are destroyed.
	   Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end
	   causes the container to relocate all the elements after the segment erased to their new positions. This is generally an
	   inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
	   (such as list or forward_list).
	   Parameters: position - iterator pointing to a single element to be removed from the vector.
	   first, last - iterators specifying a range within the vector to be removed: [first, last).
	   Return value: an iterator pointing to the new location of the element that followed the last element erased by the function
	   call. This is the container en if the operation erased the last element in the sequence*/
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator position)
	{
		size_type prev_position = static_cast<size_type>(position - this->v_begin);
		if (position == this->v_end - 1)
			this->pop_back();
		else
		{
			size_type capacity = this->capacity();
			pointer new_begin = this->alloc.allocate(capacity);
			size_type i = 0;
			for ( ; i < static_cast<size_type>(position - this->v_begin); ++i)
				this->alloc.construct(new_begin + i, *(this->v_begin + i));
			++i;
			for ( ; i < this->size(); ++i)
				this->alloc.construct(new_begin + i - 1, *(this->v_begin + i));
			this->clear();
			this->v_begin = new_begin;
			this->v_end = new_begin + i - 1;
			this->v_capacity_end = new_begin + capacity;
		}
		return reinterpret_cast<iterator>(this->v_begin + prev_position);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
	{
		size_type capacity = this->capacity();
		size_type prev_position = first - this->v_begin;
		size_type sequence_erase = static_cast<size_type>(last - first);
		pointer new_begin = this->alloc.allocate(capacity);
		size_type i = 0;
		for ( ; i < static_cast<size_type>(first - this->v_begin); ++i)
			this->alloc.construct(new_begin + i, *(this->v_begin + i));
		i += sequence_erase;
		for ( ; i < this->size(); ++i)
			this->alloc.construct(new_begin + i - sequence_erase, *(this->v_begin + i));
		this->clear();
		this->v_begin = new_begin;
		this->v_end = new_begin + i - sequence_erase;
		this->v_capacity_end = new_begin + capacity;
		return reinterpret_cast<iterator>(this->v_begin + prev_position);

		// pointer p_first = first;
		// 		for (; first != last; first++)
		// 			alloc.destroy(first);
		// 		for (int i = 0; i < v_end - last; i++)
		// 		{
		// 			alloc.construct(p_first + i, *(last + i));
		// 			alloc.destroy(last + i);
		// 		}
		// 		v_end -= (last - p_first);
		// 		return (iterator(p_first));
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 10) Exchanges the content of the container by the content of x, which is another vector object of the same
	   type. Sizes may differ.
	   After the call to this member function, the elements in this container are those which were in x before the
	   call, and the elements of x are those which were in this. All iterators, references and pointers remain
	   valid for the swapped objects																			*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::swap(vector& x)
	{
		pointer tmp_v_begin = x.v_begin;
		pointer tmp_v_end = x.v_end;
		pointer tmp_v_capacity_end = x.v_capacity_end;
		allocator_type tmp_alloc = x.alloc;

		x.v_begin = this->v_begin;
		x.v_end = this->v_end;
		x.v_capacity_end = this->v_capacity_end;
		x.alloc = this->alloc;

		this->v_begin = tmp_v_begin;
		this->v_end = tmp_v_end;
		this->v_capacity_end = tmp_v_capacity_end;
		this->alloc = tmp_alloc;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 11) Clear content. Removes all elements from the vector (which are destroyed), leaving the container with a
	   size of 0.																									*/
	template <class T, class Allocator>
	void	vector<T, Allocator>::clear()
	{
		size_type save_size = this->size();
		for (size_type i = 0; i < save_size; ++i)
		{
			v_end--;
			this->alloc.destroy(v_end);
		}
	}
	//************************************************************************************************************

	// Allocator: get allocator
	//************************************************************************************************************
	// Returns a copy of the allocator object associated with the vector
	template <class T, class Allocator>
	typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const
	{
		return this->alloc;
	}

	// Non-member functions overloads
	//************************************************************************************************************
	// relational operators
	//************************************************************************************************************
	/* Performs the appropriate comparison operation between the vector containers x and y.
	   The equality comparison (operator==) is performed by first comparing sizes, and if they match, the elements
	   are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).
	   The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, which compares
	   the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and
	   stopping at the first occurrence.																		*/
	template <class T, class Allocator>
	bool operator== (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
	}

	template <class T, class Allocator>
	bool operator!= (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return !(x == y);
	}

	template <class T, class Allocator>
	bool operator< (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class T, class Allocator>
	bool operator<= (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return !(y < x);
	}

	template <class T, class Allocator>
	bool operator> (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return y < x;
	}

	template <class T, class Allocator>
	bool operator>= (const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return !(x < y);
	}
	//************************************************************************************************************
	/* This is an overload of the generic algorithm swap that improves its performance by mutually transferring
	   ownership over their assets to the other container (i.e., the containers exchange references to their data,
	   without actually performing any element copy or movement): It behaves as if x.swap(y) was called. */
	template <class T, class Allocator>
	void	swap(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		x.swap(y);
	}
}

#endif
