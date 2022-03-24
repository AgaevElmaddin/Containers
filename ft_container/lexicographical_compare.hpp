#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

/* Lexicographical comparison is a operation with the following properties:
	1) Two ranges are compared element by element.
	2) The first mismatching element defines which range is lexicographically less or greater than the other.
	3) If one range is a prefix of another, the shorter range is lexicographically less than the other.
	4) If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
	5) An empty range is lexicographically less than any non-empty range.
	6) Two empty ranges are lexicographically equal.
*/

namespace ft
{
	// checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
	// Elements are compared using operator<.
	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// Elements are compared using the given binary comparison function comp.
	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif
