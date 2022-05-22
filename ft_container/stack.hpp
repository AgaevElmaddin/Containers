#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
				// member types
				typedef Container container_type;
				typedef T value_type;
				typedef typename Container::size_type size_type;
				typedef typename Container::reference reference;
				typedef typename Container::const_reference const_reference;
		protected:
				// member objects
				container_type c;
		public:
				//**************** member functions: constructor, destructor, operator= ************************//
				//**********************************************************************************************//
				explicit stack(const container_type& cont = container_type()): c(cont) {} // default constructor

				stack& operator=(const stack& other) // assigment operator
				{
					if(this == &other)
						return *this;
					this->c = other.c;
					return *this;
				}

				stack(const stack& other) // copy constructor
				{
					this->operator=(other);
				}

				~stack() {}
				//**********************************************************************************************//

				//**************** member functions: element access ********************************************//
				//**********************************************************************************************//
				reference top()
				{
					return c.back();
				}

				const_reference top() const
				{
					return c.back();
				}
				//**********************************************************************************************//

				//**************** member functions: capacity **************************************************//
				//**********************************************************************************************//
				bool empty() const
				{
					return c.empty();
				}

				size_type size() const
				{
					return c.size();
				}
				//**********************************************************************************************//

				//**************** member functions: modifiers **************************************************//
				//**********************************************************************************************//
				void push(const value_type& value)
				{
					c.push_back(value);
				}

				void pop()
				{
					c.pop_back();
				}
				//**********************************************************************************************//
	};

	// non-member functions
	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(rhs < lhs);
	}
}

#endif
