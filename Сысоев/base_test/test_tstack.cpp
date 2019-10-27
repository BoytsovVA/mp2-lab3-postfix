#include "stack.h"
#include <gtest.h>
#include "postfix.cpp"
TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> tmp(5));
}
TEST(TStack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> tmp(-5));
}
TEST(TStack, can_not_create_stack_with_too_large_length)
{
	ASSERT_ANY_THROW(TStack<int> tmp(MaxStackSize + 1));
}
TEST(TStack, can_return_last_elem_of_stack)
{
	TStack<int> tmp(5);
	for (int i = 0; i < 5; i++)
		tmp.Push(i);
	EXPECT_EQ(4, tmp.Top());
}
TEST(TStack, can_put_elem_in_stack)
{
	TStack<int> tmp(1);
	ASSERT_NO_THROW(tmp.Push(10));
}
TEST(TStack, can_get_elem_of_stack)
{
	TStack<int> tmp(1);
	tmp.Push(10);
	EXPECT_EQ(10, tmp.Pop());
}
TEST(TStack, can_check_stack_for_empty)
{
	TStack<int> tmp(1);
	EXPECT_TRUE(tmp.IsEmpty());
}
TEST(TStack, can_check_stack_for_full)
{
	TStack<int> st(5);
	while (!st.IsFull())
		st.Push(5);
	EXPECT_TRUE(st.IsFull());
}
TEST(TStack, can_create_copied_stack)
{
	TStack<int> st1(5);
	st1.Push(5);
	TStack<int> st2(st1);
	EXPECT_EQ(st1, st2);
}
TEST(TStack, two_stacks_are_not_equal)
{
	TStack<int> st1(5), st2(5);
	st1.Push(5);
	EXPECT_NE(st1, st2);
}
TEST(TStack, assign_operator_change_stack_size)
{
	TStack<int> st1(5), st2(10);
	st1 = st2;
	EXPECT_NE(5, st1.GetSize());
}
TEST(TStack, assign_operator_change_stack_top)
{
	TStack<int> st1(5), st2(10);
	while (!st1.IsFull())
	{
		st1.Push(5);
	}
	st2 = st1;
	EXPECT_NE(-1, st2.Top());
}
TEST(TStack, two_different_stacks_have_different_memories)
{
	TStack<int> st1(2), st2(3);
	EXPECT_NE(&st1, &st2);
}