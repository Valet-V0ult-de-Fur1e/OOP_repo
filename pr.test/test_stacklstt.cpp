#include <stacklstt/stacklstt.hpp>
#include <complex/complex.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stackarr push item") {
	StackLstT<int> test_stackLst;
	int first_item(1);
	test_stackLst.Push(first_item);
	int second_item(2);
	test_stackLst.Push(second_item);
	int check_item = second_item;
	CHECK_EQ(test_stackLst.Top(), second_item);
}

TEST_CASE("stackarr pop item") {
	StackLstT<int> test_stackLst;
	int first_item(1);
	int second_item(2);
	int check_first = first_item;
	test_stackLst.Push(first_item);
	test_stackLst.Push(second_item);
	test_stackLst.Pop();
	CHECK_EQ(test_stackLst.Top(), check_first);
}

TEST_CASE("stackarr isempty") {
	StackLstT<int> test_stackLst;
	CHECK_EQ(test_stackLst.IsEmpty(), true);
	int first_item(1);
	test_stackLst.Push(first_item);
	CHECK_EQ(test_stackLst.IsEmpty(), false);
}

TEST_CASE("stackarr clear") {
	StackLstT<int> test_stackLst;
	int first_item(1);
	int second_item(2);
	test_stackLst.Push(first_item);
	test_stackLst.Push(second_item);
	test_stackLst.Clear();
	CHECK_EQ(test_stackLst.IsEmpty(), true);
}