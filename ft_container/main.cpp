#include "vector.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include "Red_Black_Tree.hpp"
#include "Red_Black_Tree_Iterator.hpp"
#include <map>
#include "map.hpp"
#include "vector.hpp"
#include "set.hpp"
#include <stack>
#include "stack.hpp"
#include <deque>

bool fncomp (int lhs, int rhs) {return lhs<rhs;}
struct classcomp_char {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

void stack_test_constructor();
void stack_test_empty();
void stack_test_size();
void stack_test_top();
void stack_test_push();
void stack_test_pop();
void stack_test_operators();

void map_test_iterators();
void map_test_base();
void map_test_insert_el();
void map_test_insert_iter();
void map_test_insert_iter_range();
void map_test_erase();
void map_test_lower_upper_bound();
void map_test_operator_access();
void map_test_swap();
void map_test_find();
void map_test_at();
void map_test_count();
void map_test_equal_range();
void map_test_copy();
void map_test_operators();
void map_test_iterator_invalidation();

void vector_test_constructor();
void vector_test_iterators();
void vector_test_size();
void vector_test_resize();
void vector_test_capacity();
void vector_test_empty();
void vector_test_reserve();
void vector_test_at();
void vector_test_front();
void vector_test_back();
void vector_test_assign();
void vector_test_push_back();
void vector_test_pop_back();
void vector_test_insert();
void vector_test_erase();
void vector_test_swap();
void vector_test_clear();
void vector_test_operators();

int main(void)
{
	std::cout << "\nMAP" << std::endl;
    map_test_iterators();
    map_test_base();
    map_test_insert_el();
    map_test_insert_iter();
    map_test_insert_iter_range();
    map_test_erase();
    map_test_lower_upper_bound();
    map_test_operator_access();
    map_test_swap();
    map_test_find();
    map_test_at();
    map_test_count();
    map_test_equal_range();
    map_test_copy();
    map_test_operators();
    map_test_iterator_invalidation();

	std::cout << "\nSTACK" << std::endl;
    stack_test_constructor();
    stack_test_empty();
    stack_test_size();
    stack_test_top();
    stack_test_push();
    stack_test_pop();
    stack_test_operators();

	std::cout << "\nVECTOR" << std::endl;
    vector_test_constructor();
    vector_test_iterators();
    vector_test_size();
    vector_test_resize();
    vector_test_capacity();
    vector_test_empty();
    vector_test_reserve();
    vector_test_at();
    vector_test_front();
    vector_test_back();
    vector_test_assign();
    vector_test_push_back();
    vector_test_pop_back();
    vector_test_insert();
    vector_test_erase();
    vector_test_swap();
    vector_test_clear();
    vector_test_operators();

    std::cout << "\nSET\n";
		{
			{
				ft::set<int> first;                           // empty set of ints

				int myints[] = {10, 20, 30, 40, 50};
				ft::set<int> second(myints, myints + 5);        // range

				ft::set<int> third(second);                  // a copy of second

				ft::set<int> fourth(second.begin(), second.end());  // iterator ctor.

				ft::set<int, classcomp_char> fifth;                 // class as Compare

				bool (*fn_pt)(int, int) = fncomp;
				ft::set<int, bool (*)(int, int)> sixth(fn_pt);  // function pointer as Compare

			}
			{
				int myints[] = {12, 82, 37, 64, 15};
				ft::set<int> first(myints, myints + 5);   // set with 5 ints
				ft::set<int> second(myints, myints + 5);                    // empty set

				second = first;                          // now second contains the 5 ints
				first = ft::set<int>();                 // and first is empty

				std::cout << "Size of first: " << int(first.size()) << '\n';
				std::cout << "Size of second: " << int(second.size()) << '\n';
			}
			{
				int myints[] = {75, 23, 65, 42, 13};
				ft::set<int> myset(myints, myints + 5);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;

				std::cout << '\n';

			}
			{
				int myints[] = {21, 64, 17, 78, 49};
				ft::set<int> myset(myints, myints + 5);

				ft::set<int>::reverse_iterator rit;

				std::cout << "myset contains:";
				for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
					std::cout << ' ' << *rit;

				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				myset.insert(20);
				myset.insert(30);
				myset.insert(10);

				std::cout << "myset contains:";
				while (!myset.empty())
				{
					std::cout << ' ' << *myset.begin();
					myset.erase(myset.begin());
				}
				std::cout << '\n';

			}
			{
				ft::set<int> myints;
				std::cout << "0. size: " << myints.size() << '\n';

				for (int i = 0; i < 10; ++i) myints.insert(i);
				std::cout << "1. size: " << myints.size() << '\n';

				myints.insert(100);
				std::cout << "2. size: " << myints.size() << '\n';

				myints.erase(6); // erase 5 doesn't work correctly - segmentation fault
				std::cout << "3. size: " << myints.size() << '\n';

			}
			{
				int i;
				ft::set<int> myset;

				if (myset.max_size() > 1000)
				{
					for (i = 0; i < 1000; i++) myset.insert(i);
					std::cout << "The set contains 1000 elements.\n";
				} else std::cout << "The set could not hold 1000 elements.\n";

			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;
				ft::pair<ft::set<int>::iterator, bool> ret;

				// set some initial values:
				for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

				ret = myset.insert(20);               // no new element inserted

				if (ret.second == false) it = ret.first;  // "it" now points to element 20

				myset.insert(it, 25);                 // max efficiency inserting
				myset.insert(it, 24);                 // max efficiency inserting
				myset.insert(it, 26);                 // no max efficiency inserting

				int myints[] = {5, 10, 15};              // 10 already in set, not inserted
				myset.insert(myints, myints + 3);

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;

				// insert some values:
				for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

				it = myset.begin();
				++it;                                         // "it" points now to 20

				//myset.erase(it); // need to fix this - segmentation fault

				myset.erase(40);

				it = myset.find(60);
				myset.erase(it, myset.end());

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				int myints[] = {12, 75, 10, 32, 20, 25};
				ft::set<int> first(myints, myints + 3);     // 10,12,75
				ft::set<int> second(myints + 3, myints + 6);  // 20,25,32

				first.swap(second);

				std::cout << "first contains:";
				for (ft::set<int>::iterator it = first.begin(); it != first.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				std::cout << "second contains:";
				for (ft::set<int>::iterator it = second.begin(); it != second.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

			}
			{
				ft::set<int> myset;

				myset.insert(100);
				myset.insert(200);
				myset.insert(300);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';

				myset.clear();
				myset.insert(1101);
				myset.insert(2202);

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;
				int highest;

				ft::set<int>::key_compare mycomp = myset.key_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				highest = *myset.rbegin();
				ft::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				ft::set<int>::value_compare mycomp = myset.value_comp();

				for (int i = 0; i <= 5; i++) myset.insert(i);

				std::cout << "myset contains:";

				int highest = *myset.rbegin();
				ft::set<int>::iterator it = myset.begin();
				do
				{
					std::cout << ' ' << *it;
				} while (mycomp(*(++it), highest));

				std::cout << '\n';
			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator it;

				// set some initial values:
				for (int i = 1; i <= 5; i++) myset.insert(i * 10);    // set: 10 20 30 40 50

				it = myset.find(20);
				myset.erase(it);
				myset.erase(myset.find(40));

				std::cout << "myset contains:";
				for (it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				// set some initial values:
				for (int i = 1; i < 5; ++i) myset.insert(i * 3);    // set: 3 6 9 12

				for (int i = 0; i < 10; ++i)
				{
					std::cout << i;
					if (myset.count(i) != 0)
						std::cout << " is an element of myset.\n";
					else
						std::cout << " is not an element of myset.\n";
				}
			}
			{
				ft::set<int> myset;
				ft::set<int>::iterator itlow, itup;

				for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

				itlow = myset.lower_bound(30);                //       ^
				itup = myset.upper_bound(60);                 //                   ^

				//myset.erase(itlow, itup);                     // 10 20 70 80 90 // segmentation fault - need to fix

				std::cout << "myset contains:";
				for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
					std::cout << ' ' << *it;
				std::cout << '\n';
			}
			{
				ft::set<int> myset;

				for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

				ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> ret;
				ret = myset.equal_range(30);

				std::cout << "the lower bound points to: " << *ret.first << '\n';
				std::cout << "the upper bound points to: " << *ret.second << '\n';
			}
			{
				ft::set<int> myset;
				int *p;
				unsigned int i;

				// allocate an array of 5 elements using myset's allocator:
				p = myset.get_allocator().allocate(5);

				// assign some values to array
				for (i = 0; i < 5; i++) p[i] = (i + 1) * 10;

				std::cout << "The allocated array contains:";
				for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
				std::cout << '\n';

				myset.get_allocator().deallocate(p, 5);
			}
		}

   // sleep(10);

    return (0);
}

void stack_test_constructor(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::deque<int> mydeque (3,100);          // deque with 3 elements
        std::vector<int> myvector (2,200);        // vector with 2 elements

        std::stack<int> first;                    // empty stack
        std::stack<int> second (first);         // stack initialized to copy of deque

        std::stack<int,std::vector<int> > third;  // empty stack using vector
        std::stack<int,std::vector<int> > fourth (myvector);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        std::deque<int> mydeque (3,100);          // deque with 3 elements
        std::vector<int> myvector (2,200);        // vector with 2 elements

        ft::stack<int> first;                    // empty stack
        ft::stack<int> second(first);         // stack initialized to copy of deque

        ft::stack<int,std::vector<int> > third;  // empty stack using vector
        ft::stack<int,std::vector<int> > fourth (myvector);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_empty(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> mystack;
        int sum (0);

        for (int i=1;i<=10;i++) mystack.push(i);

        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }

        std::cout << "total: " << sum << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> mystack;
        int sum (0);

        for (int i=1;i<=10;i++) mystack.push(i);

        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }

        std::cout << "total: " << sum << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_size(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_top(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_push(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_pop(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void stack_test_operators(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::stack<int> mystack;
        for (int i=0; i<5; ++i) mystack.push(i);
        std::stack<int> mystac1 = mystack;
        std::cout << "== ? - " << (mystack == mystac1) << std::endl;
        std::cout << "!= ? - " << (mystack != mystac1) << std::endl;
        std::cout << ">  ? - " << (mystack > mystac1) << std::endl;
        std::cout << ">= ? - " << (mystack >= mystac1) << std::endl;
        std::cout << "<  ? - " << (mystack < mystac1) << std::endl;
        std::cout << "<= ? - " << (mystack <= mystac1) << std::endl;
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::stack<int> mystack;
        for (int i=0; i<5; ++i) mystack.push(i);
        ft::stack<int> mystac1 = mystack;
        std::cout << "== ? - " << (mystack == mystac1) << std::endl;
        std::cout << "!= ? - " << (mystack != mystac1) << std::endl;
        std::cout << ">  ? - " << (mystack > mystac1) << std::endl;
        std::cout << ">= ? - " << (mystack >= mystac1) << std::endl;
        std::cout << "<  ? - " << (mystack < mystac1) << std::endl;
        std::cout << "<= ? - " << (mystack <= mystac1) << std::endl;
        std::cout << "\033[0m";
    }
}

void map_test_iterators(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char, int> mymap;
        mymap.insert(std::pair<char, int>('a', 10));
        mymap.insert(std::pair<char, int>('b', 20));
        mymap.insert(std::pair<char, int>('c', 30));
        mymap.insert(std::pair<char, int>('d', 40));
        mymap.insert(std::pair<char, int>('e', 50));

        std::cout << "PART 1\n";
        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (std::map<char, int>::const_iterator it = mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::map<char, int>::reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::map<char, int>::const_reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        std::cout << "PART 2\n";
        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (std::map<char, int>::const_iterator it = mymap.begin(); it!=mymap.end(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::map<char, int>::reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::map<char, int>::const_reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        std::cout << "PART 3\n";
        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = --mymap.end(); it!=mymap.begin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (std::map<char, int>::const_iterator it = --mymap.end(); it!=mymap.begin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::map<char, int>::reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::map<char, int>::const_reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        {
            ft::map<char,int> mymap;

            mymap['x'] = 100;
            mymap['y'] = 200;
            mymap['z'] = 300;

            // show content:
            std::cout << "---cplusplus---\n";
            ft::map<char,int>::reverse_iterator rit;
            for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
                std::cout << rit->first << " => " << rit->second << '\n';
        }

        std::cout << "PART 4\n";
        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = --mymap.end(); it!=mymap.begin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (std::map<char, int>::const_iterator it = --mymap.end(); it!=mymap.begin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        std::map<char, int>::reverse_iterator it_rbegin = mymap.rbegin();
        for (std::map<char, int>::reverse_iterator it = --mymap.rend(); it!=it_rbegin; it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::map<char, int>::const_reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char, int> mymap;
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));

        std::cout << "PART 1\n";
        std::cout << "---iterator---\n";
        ft::map<char, int>::iterator it_end = mymap.end();
        for (ft::map<char, int>::iterator it = mymap.begin(); it!=it_end; ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::map<char, int>::const_iterator it = mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::map<char, int>::reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::map<char, int>::const_reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        std::cout << "PART 2\n";
        std::cout << "---iterator---\n";
        for (ft::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::map<char, int>::const_iterator it = mymap.begin(); it!=mymap.end(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::map<char, int>::reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::map<char, int>::const_reverse_iterator it = mymap.rbegin(); it!=mymap.rend(); it++)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        std::cout << "PART 3\n";
        std::cout << "---iterator---\n";
        for (ft::map<char, int>::iterator it = --mymap.end(); it!=mymap.begin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::map<char, int>::const_iterator it = --mymap.end(); it!=mymap.begin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::map<char, int>::reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::map<char, int>::const_reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); --it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;

        std::cout << "PART 4\n";
        std::cout << "---iterator---\n";
        for (ft::map<char, int>::iterator it = --mymap.end(); it!=mymap.begin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::map<char, int>::const_iterator it = --mymap.end(); it!=mymap.begin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::map<char, int>::reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::map<char, int>::const_reverse_iterator it = --mymap.rend(); it!=mymap.rbegin(); it--)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "size = " << mymap.size() << std::endl;
        std::cout << "\033[0m";
    }
}

void map_test_base(){
    std::cout << "===================================================================" << std::endl;
        {
        std::cout << "\033[33m";
        std::map<int, std::string> m;
        m.insert(std::pair<int, std::string>(161, "Hinata1"));
        std::cout << "size = " << m.size() << std::endl;
        m.insert(std::pair<int, std::string>(162, "Hinata2"));
        std::cout << "size = " << m.size() << std::endl;
        m.insert(std::pair<int, std::string>(161, "Hinata0"));
        std::cout << "size = " << m.size() << std::endl;
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        m.erase(160);
        m.erase(161);
        m.erase(161);
        std::cout << "size = " << m.size() << std::endl;
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        m.clear();
        std::cout << "size = " << m.size() << std::endl;
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<int, std::string> m;
        m.insert(ft::pair<int, std::string>(161, "Hinata1"));
        std::cout << "size = " << m.size() << std::endl;
        m.insert(ft::pair<int, std::string>(162, "Hinata2"));
        std::cout << "size = " << m.size() << std::endl;
        m.insert(ft::pair<int, std::string>(161, "Hinata0"));
        std::cout << "size = " << m.size() << std::endl;
        for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        m.erase(160);
        m.erase(161);
        m.erase(161);
        std::cout << "size = " << m.size() << std::endl;
        for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        m.clear();
        std::cout << "size = " << m.size() << std::endl;
        for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it){
            std::cout << "iter_i = " << (it->second) << std::endl;
        }
        std::cout << "\033[0m";
    }
}

 void map_test_insert_el(){
    std::cout << "===================================================================" << std::endl;
    {
         std::cout << "\033[33m";
         std::map<char,int> mymap;
         // first insert function version (single parameter):
         mymap.insert ( std::pair<char,int>('a',100) );
         mymap.insert ( std::pair<char,int>('z',200) );

         std::pair<std::map<char,int>::iterator,bool> ret;
         ret = mymap.insert ( std::pair<char,int>('z',500) );
         if (ret.second==false) {
             std::cout << "element 'z' already existed";
             std::cout << " with a value of " << ret.first->second << '\n';
         }
         std::cout << "\033[0m";
     }
     {
        std::cout << "\033[34m";
         ft::map<char, int> mymap;
         // first insert function version (single parameter):
         mymap.insert(ft::pair<char, int>('a', 100));
         mymap.insert(ft::pair<char, int>('z', 200));

         ft::pair<ft::map<char, int>::iterator, bool> ret;
         ret = mymap.insert(ft::pair<char, int>('z', 500));
         if (ret.second == false) {
             std::cout << "element 'z' already existed";
             std::cout << " with a value of " << ret.first->second << '\n';
         }
         std::cout << "\033[0m";
     }
 }

 void map_test_insert_iter(){
     std::cout << "===================================================================" << std::endl;
     {
         std::cout << "\033[33m";
         std::map<char,int> mymap;
         // second insert function version (with hint position):
         std::map<char,int>::iterator it = mymap.begin();
         mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
         mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting
         mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
         std::cout << "size = " << mymap.size() << std::endl;
         for (std::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
     }
     {
         std::cout << "\033[34m";
         ft::map<char,int> mymap;
         // second insert function version (with hint position):
         ft::map<char,int>::iterator it = mymap.begin();
         mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
         mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting
         mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
         std::cout << "size = " << mymap.size() << std::endl;
         for (ft::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
     }
 }

 void map_test_insert_iter_range(){
     std::cout << "===================================================================" << std::endl;
     {
         std::cout << "\033[33m";
         std::map<char,int> mymap;

         // first insert function version (single parameter):
         mymap.insert ( std::pair<char,int>('a',100) );
         mymap.insert ( std::pair<char,int>('z',200) );

         std::pair<std::map<char,int>::iterator,bool> ret;
         ret = mymap.insert ( std::pair<char,int>('z',500) );

         // second insert function version (with hint position):
         std::map<char,int>::iterator it = mymap.begin();
         mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
         mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

         // third insert function version (range insertion):
         std::map<char,int> anothermap;
         anothermap.insert(mymap.begin(),mymap.find('c'));

         // showing contents:
         std::cout << "mymap contains:\n";
         for (it=mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';

         std::cout << "anothermap contains:\n";
         for (it=anothermap.begin(); it!=anothermap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
     }
     {
        std::cout << "\033[34m";
         ft::map<char,int> mymap;

         // first insert function version (single parameter):
         mymap.insert ( ft::pair<char,int>('a',100) );
         mymap.insert ( ft::pair<char,int>('z',200) );

         ft::pair<ft::map<char,int>::iterator,bool> ret;
         ret = mymap.insert ( ft::pair<char,int>('z',500) );

         // second insert function version (with hint position):
         ft::map<char,int>::iterator it = mymap.begin();
         mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
         mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

         // third insert function version (range insertion):
         ft::map<char,int> anothermap;
         anothermap.insert(mymap.begin(),mymap.find('c'));

         // showing contents:
         std::cout << "mymap contains:\n";
         for (it=mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';

         std::cout << "anothermap contains:\n";
         for (it=anothermap.begin(); it!=anothermap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
     }
 }

 void map_test_erase(){
     std::cout << "===================================================================" << std::endl;
     {
         std::cout << "\033[33m";
         std::map<char,int> mymap;
         std::map<char,int>::iterator it;

         // insert some values:
        mymap.insert(std::pair<char, int>('a', 10));
        mymap.insert(std::pair<char, int>('b', 20));
        mymap.insert(std::pair<char, int>('c', 30));
        mymap.insert(std::pair<char, int>('d', 40));
        mymap.insert(std::pair<char, int>('e', 50));

         // erasing by iterator
         it=mymap.find('b');
         mymap.erase (it);

         // erasing by key
         mymap.erase ('c');

         // erasing by range
         it=mymap.find ('e');
         mymap.erase ( it, mymap.end() );

         // show content:
         for (it=mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
         std::cout << "size = " << mymap.size() << std::endl;
        std::cout << "\033[0m";
     }
     {
         std::cout << "\033[34m";
         ft::map<char,int> mymap;
         ft::map<char,int>::iterator it;

         // insert some values:
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));

         // erasing by iterator
         it=mymap.find('b');
         mymap.erase (it);

         // erasing by key
         mymap.erase ('c');

         // erasing by range
         it=mymap.find ('e');
         mymap.erase ( it, mymap.end() );

         // show content:
         for (it=mymap.begin(); it!=mymap.end(); ++it)
             std::cout << it->first << " => " << it->second << '\n';
         std::cout << "size = " << mymap.size() << std::endl;
        std::cout << "\033[0m";
     }
 }

void map_test_lower_upper_bound() {
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> mymap;
        std::map<char,int>::iterator itlow,itup;

        // insert some values:
        mymap.insert(std::pair<char, int>('a', 10));
        mymap.insert(std::pair<char, int>('b', 20));
        mymap.insert(std::pair<char, int>('c', 30));
        mymap.insert(std::pair<char, int>('d', 40));
        mymap.insert(std::pair<char, int>('e', 50));

        itlow=mymap.lower_bound ('b');  // itlow points to b
        itup=mymap.upper_bound ('d');   // itup points to e (not d!)

        // erases [itlow,itup)
         mymap.erase(itlow, itup);

        // print content:
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> mymap;
        ft::map<char,int>::iterator itlow,itup;

        // insert some values:
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));

        itlow=mymap.lower_bound ('b');  // itlow points to b
        itup=mymap.upper_bound ('d');   // itup points to e (not d!)

        // erases [itlow,itup)
         mymap.erase(itlow, itup);

        // print content:
        for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
}

void map_test_operator_access(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,std::string> mymap;

        mymap['a']="an element";
        mymap['b']="another element";
        mymap['c']=mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,std::string> mymap;

        mymap['a']="an element";
        mymap['b']="another element";
        mymap['c']=mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";
        std::cout << "\033[0m";
    }
}

void map_test_swap() {
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
}

void map_test_find(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> mymap;
        std::map<char,int>::iterator it;

        mymap['a']=50;
        mymap['b']=100;
        mymap['c']=150;
        mymap['d']=200;

        it = mymap.find('b');
        if (it != mymap.end())
            mymap.erase (it);

        // print content:
        std::cout << "elements in mymap:" << '\n';
        std::cout << "a => " << mymap.find('a')->second << '\n';
        std::cout << "c => " << mymap.find('c')->second << '\n';
        std::cout << "d => " << mymap.find('d')->second << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> mymap;
        ft::map<char,int>::iterator it;

        mymap['a']=50;
        mymap['b']=100;
        mymap['c']=150;
        mymap['d']=200;

        it = mymap.find('b');
        if (it != mymap.end())
            mymap.erase (it);

        // print content:
        std::cout << "elements in mymap:" << '\n';
        std::cout << "a => " << mymap.find('a')->second << '\n';
        std::cout << "c => " << mymap.find('c')->second << '\n';
        std::cout << "d => " << mymap.find('d')->second << '\n';
        std::cout << "\033[0m";
    }
}

void map_test_at() {
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> mymap;
        std::map<char,int>::iterator it;

        mymap['a']=50;
        mymap['b']=100;
        mymap['c']=150;
        mymap['d']=200;
        try {
            std::cout << mymap.at('a') << std::endl;
            std::cout << mymap.at('z') << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> mymap;
        ft::map<char,int>::iterator it;

        mymap['a']=50;
        mymap['b']=100;
        mymap['c']=150;
        mymap['d']=200;
        try {
            std::cout << mymap.at('a') << std::endl;
            std::cout << mymap.at('z') << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "\033[0m";
    }
}

void map_test_count(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> mymap;
        char c;

        mymap ['a']=101;
        mymap ['c']=202;
        mymap ['f']=303;

        for (c='a'; c<'h'; c++)
        {
            std::cout << c;
            if (mymap.count(c)>0)
                std::cout << " is an element of mymap.\n";
            else
                std::cout << " is not an element of mymap.\n";
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> mymap;
        char c;

        mymap ['a']=101;
        mymap ['c']=202;
        mymap ['f']=303;

        for (c='a'; c<'h'; c++)
        {
            std::cout << c;
            if (mymap.count(c)>0)
                std::cout << " is an element of mymap.\n";
            else
                std::cout << " is not an element of mymap.\n";
        }
        std::cout << "\033[0m";
    }
}

void map_test_equal_range(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char,int> mymap;

        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;

        std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char,int> mymap;

        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;

        ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
        std::cout << "\033[0m";
    }
}

void map_test_copy(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char, int> mymap;
        mymap.insert(std::pair<char, int>('a', 10));
        mymap.insert(std::pair<char, int>('b', 20));
        mymap.insert(std::pair<char, int>('c', 30));
        mymap.insert(std::pair<char, int>('d', 40));
        mymap.insert(std::pair<char, int>('e', 50));

        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::map<char, int> mymap1(mymap);
        std::cout << "---iterator---\n";
        for (std::map<char, int>::iterator it = mymap1.begin(); it!=mymap1.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char, int> mymap;
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));

        std::cout << "---iterator---\n";
        for (ft::map<char, int>::iterator it = mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        ft::map<char, int> mymap1(mymap);
        std::cout << "---iterator---\n";
        for (ft::map<char, int>::iterator it = mymap1.begin(); it!=mymap1.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "\033[0m";
    }
}

void map_test_operators(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        ft::map<char, int> mymap;
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));
        ft::map<char, int> mymap1 = mymap;

        std::cout << "== ? - " << (mymap == mymap1) << std::endl;
        std::cout << "!= ? - " << (mymap != mymap1) << std::endl;
        std::cout << ">  ? - " << (mymap > mymap1) << std::endl;
        std::cout << ">= ? - " << (mymap >= mymap1) << std::endl;
        std::cout << "<  ? - " << (mymap < mymap1) << std::endl;
        std::cout << "<= ? - " << (mymap <= mymap1) << std::endl;
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char, int> mymap;
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('b', 20));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));
        ft::map<char, int> mymap1 = mymap;

        std::cout << "== ? - " << (mymap == mymap1) << std::endl;
        std::cout << "!= ? - " << (mymap != mymap1) << std::endl;
        std::cout << ">  ? - " << (mymap > mymap1) << std::endl;
        std::cout << ">= ? - " << (mymap >= mymap1) << std::endl;
        std::cout << "<  ? - " << (mymap < mymap1) << std::endl;
        std::cout << "<= ? - " << (mymap <= mymap1) << std::endl;
        std::cout << "\033[0m";
    }
}

void map_test_iterator_invalidation(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::map<char, int> mymap;
        mymap.insert(std::pair<char, int>('b', 20));

        std::map<char, int>::iterator it = mymap.begin();
        mymap.insert(std::pair<char, int>('a', 10));
        mymap.insert(std::pair<char, int>('c', 30));
        mymap.insert(std::pair<char, int>('d', 40));
        mymap.insert(std::pair<char, int>('e', 50));
        for (; it!= mymap.end(); ++it){
            std::cout << it->first << " => " << it->second << '\n';
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::map<char, int> mymap;
        mymap.insert(ft::pair<char, int>('b', 20));

        ft::map<char, int>::iterator it = mymap.begin();
        mymap.insert(ft::pair<char, int>('a', 10));
        mymap.insert(ft::pair<char, int>('c', 30));
        mymap.insert(ft::pair<char, int>('d', 40));
        mymap.insert(ft::pair<char, int>('e', 50));
        for (; it!= mymap.end(); ++it){
            std::cout << it->first << " => " << it->second << '\n';
        }
        std::cout << "\033[0m";
    }
}



void vector_test_constructor(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        // constructors used in the same order as described above:
        std::vector<int> first;                                // empty vector of ints
        std::vector<int> second(4,100);                       // four ints with value 100
        std::vector<int> third(second.begin(),second.end());  // iterating through second
        std::vector<int> fourth(third);                       // a copy of third

        // the iterator constructor can also be used to construct from arrays:
        int myints[] = {16,2,77,29};
        std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

        std::cout << "The contents of fifth are:";
        for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        // constructors used in the same order as described above:
        ft::vector<int> first;                                // empty vector of ints
        ft::vector<int> second (4,100);                       // four ints with value 100
        ft::vector<int> third(second.begin(), second.end());  // iterating through second
        ft::vector<int> fourth(third);                       // a copy of third

        // the iterator constructor can also be used to construct from arrays:
        int myints[] = {16,2,77,29};
        ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );

        std::cout << "The contents of fifth are:";
        for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_iterators(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<std::string> v;

        v.push_back("one");
        v.push_back("two");
        v.push_back("three");
        v.push_back("four");
        v.push_back("five");

        std::cout << "PART 1\n";
        std::cout << "---iterator---\n";
        for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (std::vector<std::string>::const_iterator it = v.begin(); it!=v.end(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::vector<std::string>::reverse_iterator it = v.rbegin(); it!=v.rend(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::vector<std::string>::const_reverse_iterator it = v.rbegin(); it!=v.rend(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 2\n";
        std::cout << "---iterator---\n";
        for (std::vector<std::string>::iterator it = v.begin(); it!=v.end(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (std::vector<std::string>::const_iterator it = v.begin(); it!=v.end(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::vector<std::string>::reverse_iterator it = v.rbegin(); it!=v.rend(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::vector<std::string>::const_reverse_iterator it = v.rbegin(); it!=v.rend(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 3\n";
        std::cout << "---iterator---\n";
        for (std::vector<std::string>::iterator it = --v.end(); it!=v.begin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (std::vector<std::string>::const_iterator it = --v.end(); it!=v.begin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::vector<std::string>::reverse_iterator it = --v.rend(); it!=v.rbegin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::vector<std::string>::const_reverse_iterator it = --v.rend(); it!=v.rbegin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 4\n";
        std::cout << "---iterator---\n";
        for (std::vector<std::string>::iterator it = --v.end(); it!=v.begin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (std::vector<std::string>::const_iterator it = --v.end(); it!=v.begin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (std::vector<std::string>::reverse_iterator it = --v.rend(); it!=v.rbegin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (std::vector<std::string>::const_reverse_iterator it = --v.rend(); it!=v.rbegin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<std::string> v;

        v.push_back("one");
        v.push_back("two");
        v.push_back("three");
        v.push_back("four");
        v.push_back("five");

        std::cout << "PART 1\n";
        std::cout << "---iterator---\n";
        for (ft::vector<std::string>::iterator it = v.begin(); it!=v.end(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::vector<std::string>::const_iterator it = v.begin(); it!=v.end(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::vector<std::string>::reverse_iterator it = v.rbegin(); it!=v.rend(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::vector<std::string>::const_reverse_iterator it = v.rbegin(); it!=v.rend(); ++it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 2\n";
        std::cout << "---iterator---\n";
        for (ft::vector<std::string>::iterator it = v.begin(); it!=v.end(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::vector<std::string>::const_iterator it = v.begin(); it!=v.end(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::vector<std::string>::reverse_iterator it = v.rbegin(); it!=v.rend(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::vector<std::string>::const_reverse_iterator it = v.rbegin(); it!=v.rend(); it++)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 3\n";
        std::cout << "---iterator---\n";
        ft::vector<std::string>::iterator iter = v.end();
        for (ft::vector<std::string>::iterator it = --iter; it!=v.begin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::vector<std::string>::const_iterator it = --iter; it!=v.begin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::vector<std::string>::reverse_iterator it = --v.rend(); it!=v.rbegin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::vector<std::string>::const_reverse_iterator it = --v.rend(); it!=v.rbegin(); --it)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;

        std::cout << "PART 4\n";
        std::cout << "---iterator---\n";
        ft::vector<std::string>::iterator ite = v.end();
        for (ft::vector<std::string>::iterator it = --ite; it!=v.begin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_iterator---\n";
        for (ft::vector<std::string>::const_iterator it = --ite; it!=v.begin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---reverse_iterator---\n";
        for (ft::vector<std::string>::reverse_iterator it = --v.rend(); it!=v.rbegin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "---const_reverse_iterator---\n";
        for (ft::vector<std::string>::const_reverse_iterator it = --v.rend(); it!=v.rbegin(); it--)
            std::cout << "*it=" << *it << '\n';
        std::cout << "size = " << v.size() << std::endl;
        std::cout << "\033[0m";
    }
}

void vector_test_size(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<10; i++) myints.push_back(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.insert (myints.end(),10,100);
        std::cout << "2. size: " << myints.size() << '\n';

        myints.pop_back();
        std::cout << "3. size: " << myints.size() << '\n';
        std::cout << "\033[0m";
    }
    {
  			std::cout << "\033[34m";
        	ft::vector<int> myints;
        	std::cout << "0. size: " << myints.size() << '\n';

        	for (int i=0; i<10; i++) myints.push_back(i);
     		std::cout << "1. size: " << myints.size() << '\n';

        	myints.insert (myints.end(),10,100);
        	std::cout << "2. size: " << myints.size() << '\n';

        	myints.pop_back();
        	std::cout << "3. size: " << myints.size() << '\n';
        	std::cout << "\033[0m";
    }
}

void vector_test_capacity(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        // set some content in the vector:
        for (int i=0; i<100; i++) myvector.push_back(i);

        std::cout << "size: " << myvector.size() << "\n";
        std::cout << "capacity: " << myvector.capacity() << "\n";
        std::cout << "max_size: " << myvector.max_size() << "\n";
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        // set some content in the vector:
        for (int i=0; i<100; i++) myvector.push_back(i);

        std::cout << "size: " << myvector.size() << "\n";
        std::cout << "capacity: " << myvector.capacity() << "\n";
        std::cout << "max_size: " << myvector.max_size() << "\n";
        std::cout << "\033[0m";
    }
}

void vector_test_resize(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        // set some initial content:
        for (int i=1;i<10;i++) myvector.push_back(i); // ±±±

        myvector.resize(5);
        myvector.resize(8,100);
        myvector.resize(12);

        std::cout << "myvector contains:";
        for (unsigned long i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        // set some initial content:
        for (int i=1;i<10;i++) myvector.push_back(i);

        myvector.resize(5);
        myvector.resize(8,100);
        myvector.resize(12);

        std::cout << "myvector contains:";
        for (unsigned long i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_empty(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;
        int sum (0);

        for (int i=1;i<=10;i++) myvector.push_back(i);

        while (!myvector.empty())
        {
            sum += myvector.back();
            myvector.pop_back();
        }

        std::cout << "total: " << sum << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;
        int sum (0);

        for (int i=1;i<=10;i++) myvector.push_back(i);

        while (!myvector.empty())
        {
            sum += myvector.back();
            myvector.pop_back();
        }

        std::cout << "total: " << sum << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_reserve(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int>::size_type sz;

        std::vector<int> foo;
        sz = foo.capacity();
        std::cout << "making foo grow:\n";
        for (int i=0; i<100; ++i) {
            foo.push_back(i);
            if (sz!=foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
            }
        }

        std::vector<int> bar;
        sz = bar.capacity();
        bar.reserve(100);   // this is the only difference with foo above
        std::cout << "making bar grow:\n";
        for (int i=0; i<100; ++i) {
            bar.push_back(i);
            if (sz!=bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
            }
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int>::size_type sz;

        ft::vector<int> foo;
        sz = foo.capacity();
        std::cout << "making foo grow:\n";
        for (int i=0; i<100; ++i) {
            foo.push_back(i);
            if (sz!=foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
            }
        }

        ft::vector<int> bar;
        sz = bar.capacity();
        bar.reserve(100);   // this is the only difference with foo above
        std::cout << "making bar grow:\n";
        for (int i=0; i<100; ++i) {
            bar.push_back(i);
            if (sz!=bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
            }
        }
        std::cout << "\033[0m";
    }
}

void vector_test_at(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector (10);   // 10 zero-initialized ints

        // assign some values:
        for (unsigned i=0; i<myvector.size(); i++)
            myvector.at(i)=i;

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector.at(i);
        std::cout << '\n';

        try {
            std::cout << myvector.at(10000) << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector (10);   // 10 zero-initialized ints

        // assign some values:
        for (unsigned i=0; i<myvector.size(); i++)
            myvector.at(i)=i;

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector.at(i);
        std::cout << '\n';

        try {
            std::cout << myvector.at(10000) << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "\033[0m";
    }
}

void vector_test_front(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        myvector.push_back(78);
        myvector.push_back(16);

        // now front equals 78, and back 16

        myvector.front() -= myvector.back();

        std::cout << "myvector.front() is now " << myvector.front() << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        myvector.push_back(78);
        myvector.push_back(16);

        // now front equals 78, and back 16

        myvector.front() -= myvector.back();

        std::cout << "myvector.front() is now " << myvector.front() << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_back(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        myvector.push_back(10);

        while (myvector.back() != 0)
        {
            myvector.push_back ( myvector.back() -1 );
        }

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size() ; i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        myvector.push_back(10);

        while (myvector.back() != 0)
        {
            myvector.push_back ( myvector.back() -1 );
        }

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size() ; i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_assign(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> first;
        std::vector<int> second;
        std::vector<int> third;

        first.assign (7,100);             // 7 ints with a value of 100

        std::vector<int>::iterator it;
        it=first.begin()+1;

        second.assign (it,first.end()-1); // the 5 central values of first

        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);   // assigning from array.

        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        std::cout << "Size of third: " << int (third.size()) << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> first;
        ft::vector<int> second;
        ft::vector<int> third;

        first.assign (7,100);             // 7 ints with a value of 100

        ft::vector<int>::iterator it;
        it=first.begin()+1;

        second.assign (it,first.end()-1); // the 5 central values of first

        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);   // assigning from array.

        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        std::cout << "Size of third: " << int (third.size()) << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_push_back(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        for (int i = 0; i < 100; i++) myvector.push_back(i);

        std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        for (int i = 0; i < 100; i++) myvector.push_back(i);

        std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
        std::cout << "\033[0m";
    }
}

void vector_test_pop_back(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        while (!myvector.empty())
        {
            sum+=myvector.back();
            myvector.pop_back();
        }

        std::cout << "The elements of myvector add up to " << sum << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        while (!myvector.empty())
        {
            sum+=myvector.back();
            myvector.pop_back();
        }

        std::cout << "The elements of myvector add up to " << sum << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_insert(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector (3,100);
        std::vector<int>::iterator it;

        it = myvector.begin();
        it = myvector.insert ( it , 200 );

        myvector.insert (it,2,300);

        // "it" no longer valid, get a new one:
        it = myvector.begin();

        std::vector<int> anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());

        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);

        std::cout << "myvector contains:";
        for (it=myvector.begin(); it<myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector (3,100);
        ft::vector<int>::iterator it;

        it = myvector.begin();
        it = myvector.insert ( it , 200 );

        myvector.insert (it,2,300);

        // "it" no longer valid, get a new one:
        it = myvector.begin();

        std::vector<int> anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());

        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);

        std::cout << "myvector contains:";
        for (it=myvector.begin(); it<myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_erase(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;

        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);

        // erase the 6th element
        myvector.erase (myvector.begin()+5);

        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;

        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);

        // erase the 6th element
        myvector.erase (myvector.begin()+5);

        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_swap(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> foo (3,100);   // three ints with a value of 100
        std::vector<int> bar (5,200);   // five ints with a value of 200

        foo.swap(bar);

        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> foo (3,100);   // three ints with a value of 100
        ft::vector<int> bar (5,200);   // five ints with a value of 200

        foo.swap(bar);

        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_clear(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "\033[0m";
    }
}

void vector_test_operators(){
    std::cout << "===================================================================" << std::endl;
    {
        std::cout << "\033[33m";
        std::vector<int> vec;
        for (int i=0; i<5; ++i) vec.push_back(i);
        std::vector<int> vec1 = vec;
        std::cout << "== ? - " << (vec == vec1) << std::endl;
        std::cout << "!= ? - " << (vec != vec1) << std::endl;
        std::cout << ">  ? - " << (vec > vec1) << std::endl;
        std::cout << ">= ? - " << (vec >= vec1) << std::endl;
        std::cout << "<  ? - " << (vec < vec1) << std::endl;
        std::cout << "<= ? - " << (vec <= vec1) << std::endl;
        std::cout << "\033[0m";
    }
    {
        std::cout << "\033[34m";
        ft::vector<int> vec;
        for (int i=0; i<5; ++i) vec.push_back(i);
        ft::vector<int> vec1 = vec;
        std::cout << "== ? - " << (vec == vec1) << std::endl;
        std::cout << "!= ? - " << (vec != vec1) << std::endl;
        std::cout << ">  ? - " << (vec > vec1) << std::endl;
        std::cout << ">= ? - " << (vec >= vec1) << std::endl;
        std::cout << "<  ? - " << (vec < vec1) << std::endl;
        std::cout << "<= ? - " << (vec <= vec1) << std::endl;
        std::cout << "\033[0m";
    }
}

// int main()
// {
// 		//vector default costructor
// 		ft::vector<int> ft_v;



// 		//vector fill costructor
// 		ft::vector<int> fill_v(4, 45);



// 		//vector range costructor
// 		// int range_array[] = {45, 43949, 5, 3333, 999};
// 		// ft::vector<int>::iterator ft_iterator = fill_v.begin();
// 		// ft::vector<int>::iterator ft_end = fill_v.end();
// 		// ft::vector<int> ft_range_vector(ft_iterator, ft_end);
// }

// 	// {
// 	// 	std::cout << "\033[33m";
//     //     // constructors used in the same order as described above:
//     //     std::vector<int> first;                                // empty vector of ints
//     //     std::vector<int> second (4,100);                       // four ints with value 100
//     //     std::vector<int> third (second.begin(),second.end());  // iterating through second
//     //     std::vector<int> fourth (third);                       // a copy of third

//     //     // the iterator constructor can also be used to construct from arrays:
//     //     int myints[] = {16,2,77,29};
//     //     std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//     //     std::cout << "The contents of fifth are:";
//     //     for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//     //         std::cout << ' ' << *it;
//     //     std::cout << '\n';
//     //     std::cout << "\033[0m";
// 	// }

// 	// {
//     //     std::cout << "\033[34m";
//     //     // constructors used in the same order as described above:
//     //     ft::vector<int> first;                                // empty vector of ints
//     //     ft::vector<int> second (4,100);                       // four ints with value 100
//     //     ft::vector<int> third (second.begin(),second.end());  // iterating through second
//     //     ft::vector<int> fourth (third);                       // a copy of third

//     //     // the iterator constructor can also be used to construct from arrays:
//     //     int myints[] = {16,2,77,29};
//     //     ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//     //     std::cout << "The contents of fifth are:";
//     //     for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//     //         std::cout << ' ' << *it;
//     //     std::cout << '\n';
//     //     std::cout << "\033[0m";
//     // }

// 	return 0;
// }

// #include <iostream>
// #include <string>
// #include <deque>
// #if 0 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include "map.hpp"
// 	#include "stack.hpp"
// 	#include "vector.hpp"
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs)
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}

// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }