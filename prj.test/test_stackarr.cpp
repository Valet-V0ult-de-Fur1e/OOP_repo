#include <stackarr/stackarr.hpp>
#include <complex/complex.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stackarr push item") {
	StackArr test_stackArr;
	Complex first_item(1, 2);
	Complex check_first = first_item;
	test_stackArr.Push(first_item);
	CHECK_EQ(test_stackArr.Top(), check_first);
}

TEST_CASE("stackarr pop item") {
	StackArr test_stackArr;
	Complex first_item(1, 2);
	Complex second_item(2, 2);
	Complex check_first = first_item;
	test_stackArr.Push(first_item);
	test_stackArr.Push(second_item);
	test_stackArr.Pop();
	CHECK_EQ(test_stackArr.Top(), check_first);
}

TEST_CASE("stackarr isempty") {
	StackArr test_stackArr;
	CHECK_EQ(test_stackArr.IsEmpty(), true);
	Complex first_item(1, 2);
	test_stackArr.Push(first_item);
	CHECK_EQ(test_stackArr.IsEmpty(), false);
}

TEST_CASE("stackarr clear") {
	StackArr test_stackArr;
	Complex first_item(1, 2);
	Complex second_item(2, 2);
	test_stackArr.Push(first_item);
	test_stackArr.Push(second_item);
	test_stackArr.Clear();
	CHECK_EQ(test_stackArr.IsEmpty(), true);
}