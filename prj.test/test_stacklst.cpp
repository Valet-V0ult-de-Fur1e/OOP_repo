#include <stacklst/stacklst.hpp>
#include <complex/complex.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stackarr push item") {
	StackLst test_stackLst;
	Complex first_item(1, 2);
	test_stackLst.Push(first_item);
	Complex second_item(2, 2);
	test_stackLst.Push(second_item);
	Complex check_item = second_item;
	CHECK_EQ(test_stackLst.Top(), second_item);
}

TEST_CASE("stackarr pop item") {
	StackLst test_stackLst;
	Complex first_item(1, 2);
	Complex second_item(2, 2);
	Complex check_first = first_item;
	test_stackLst.Push(first_item);
	test_stackLst.Push(second_item);
	test_stackLst.Pop();
	CHECK_EQ(test_stackLst.Top(), check_first);
}

TEST_CASE("stackarr isempty") {
	StackLst test_stackLst;
	CHECK_EQ(test_stackLst.IsEmpty(), true);
	Complex first_item(1, 2);
	test_stackLst.Push(first_item);
	CHECK_EQ(test_stackLst.IsEmpty(), false);
}

TEST_CASE("stackarr clear") {
	StackLst test_stackLst;
	Complex first_item(1, 2);
	//Complex second_item(2, 2);
	test_stackLst.Push(first_item);
	//test_stackLst.Push(second_item);
	test_stackLst.Clear();
	CHECK_EQ(test_stackLst.IsEmpty(), true);
}