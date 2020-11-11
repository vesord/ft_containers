//
// Created by Mushroom Atrus on 11/11/20.
//

#include "gtest/gtest.h"
//#include "allocator.hpp"
#include "list.hpp"
#include <list>
#include <string>
#include <sstream>

class ListTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i)
			ftList.push_front(i);
		for (int i = 0; i < 10; ++i)
			stdList.push_front(i);
	}
//	virtual void TearDown();

	ft::list<int> ftList;
	std::list<int> stdList;
};

template <typename ftIter, typename stdIter>
void	listIteratorTest(ft::list<int> & ftList, std::list<int> & stdList)
{
	ftIter fIt = ftList.begin();
	ftIter fIte(ftList.end());
	ftIter ftmpIt;
	stdIter sIt = stdList.begin();
	stdIter sIte = stdList.end();
	stdIter stmpIt;

	EXPECT_EQ(*fIt, *sIt);
	++fIt;
	++sIt;
	EXPECT_EQ(*fIt, *sIt);
	ftmpIt = fIt++;
	stmpIt = sIt++;
	EXPECT_EQ(*fIt, *sIt);
	EXPECT_EQ(*stmpIt, *ftmpIt);

	for (int i = 0; i < 25; ++i)
	{
		--fIt;
		--sIt;
		if (sIt == sIte) {
			ASSERT_EQ(*fIt, *fIte);
			continue;
		}
		EXPECT_EQ(*fIt, *sIt);
	}
}

TEST_F(ListTest, forwardIterator)
{
	listIteratorTest<ft::list<int>::iterator, std::list<int>::iterator>(ftList, stdList);
}

TEST_F(ListTest, forwardIteratorConst)
{
	listIteratorTest<ft::list<int>::const_iterator, std::list<int>::const_iterator>(ftList, stdList);
}