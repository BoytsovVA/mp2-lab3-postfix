#include "queue.h"
#include <gtest.h>
#include "classter.cpp"
TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> tmp(5));
}
TEST(TQueue, can_not_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> tmp(-5));
}
TEST(TQueue, can_not_create_queue_with_too_large_length)
{
	ASSERT_ANY_THROW(TQueue<int> tmp(MaxQueueSize + 1));
}
TEST(TQueue, can_return_first_elem_of_queue)
{
	TQueue<int> tmp(5);
	for (int i = 0; i < 5; i++)
		tmp.Push(i);
	EXPECT_EQ(0, tmp.GetFirst());
}
TEST(TQueue, can_put_elem_in_stack)
{
	TQueue<int> tmp(1);
	ASSERT_NO_THROW(tmp.Push(10));
}
TEST(TQueue, can_get_elem_of_queue)
{
	TQueue<int> tmp(1);
	tmp.Push(10);
	EXPECT_EQ(10, tmp.GetFirst());
}
TEST(TQueue, can_check_queue_for_empty)
{
	TQueue<int> tmp(1);
	EXPECT_TRUE(tmp.IsEmpty());
}
TEST(TQueue, can_check_queue_for_full)
{
	TQueue<int> st(5);
	while (!st.IsFull())
		st.Push(5);
	EXPECT_TRUE(st.IsFull());
}
TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> st1(5);
	st1.Push(5);
	TQueue<int> st2(st1);
	EXPECT_EQ(st1, st2);
}
TEST(TQueue, two_queues_are_not_equal)
{
	TQueue<int> st1(5), st2(5);
	st1.Push(5);
	EXPECT_NE(st1, st2);
}
TEST(TQueue, assign_operator_change_queue_size)
{
	TQueue<int> st1(3), st2(10);
	st1 = st2;
	EXPECT_NE(5, st1.GetSize());
}
TEST(TQueue, assign_operator_change_queue_first)
{
	TQueue<int> st1(5), st2(10);
	while (!st1.IsFull())
	{
		st1.Push(5);
	}
	st2 = st1;
	EXPECT_NE(-1, st2.GetFirst());
}
TEST(TQueue, assign_operator_change_queue_last)
{
	TQueue<int> st1(5), st2(10);
	while (!st1.IsFull())
	{
		st1.Push(5);
	}
	st2 = st1;
	EXPECT_NE(1, st2.GetLast());
}
TEST(TQueue, two_different_stacks_have_different_memories)
{
	TQueue<int> st1(2), st2(3);
	EXPECT_NE(&st1, &st2);
}