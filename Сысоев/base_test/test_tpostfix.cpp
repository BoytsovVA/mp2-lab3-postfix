#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_return_infix)
{
	TPostfix str("(((1+23)*1-22)+5)*2-7");
	EXPECT_EQ("(((1+23)*1-22)+5)*2-7", str.GetInfix());
}
TEST(TPostfix, can_return_postfix)
{
	TPostfix str("(((1+23)*1-22)+5)*2-7");
	str.ToPostfix();
	EXPECT_EQ(str.GetPostfix(), "1,23,+,1,*,22,-,5,+,2,*,7,-");
}
TEST(TPostfix, cant_start_with_clossed_bracket)
{
	TPostfix str(")a+b(");
	ASSERT_ANY_THROW(str.ToPostfix());
}
TEST(TPostfix, coutn_of_open_brackets_compare_closed_brackets)
{
	TPostfix str("((a+b)");
	ASSERT_ANY_THROW(str.ToPostfix());
}
TEST(TPostfix, can_translate_an_incorrect_expression_into_a_postfix_form)
{
	TPostfix str("a++b");
	ASSERT_NO_THROW(str.ToPostfix());
}
TEST(TPostfix, not_enough_operands_to_calculate)
{
	TPostfix str("a++b");
	str.ToPostfix();
	ASSERT_ANY_THROW(str.Calculate());
}
TEST(TPostfix, the_postfix_form_is_correct_only_for_numbers)
{
	TPostfix str("5+6-1");
	EXPECT_EQ("5,6,+,1,-", str.ToPostfix());
}
TEST(TPostfix, the_postfix_form_is_correct_only_for_variables)
{
	TPostfix str("a+b-c");
	EXPECT_EQ("a,b,+,c,-", str.ToPostfix());
}
TEST(TPostfix, the_postfix_form_is_correct_for_numbers_and_variables)
{
	TPostfix str("5+a-c/d-1");
	EXPECT_EQ("5,a,+,c,d,/,-,1,-", str.ToPostfix());
}
TEST(TPostfix, cant_calculate_without_postfix_form)
{
	TPostfix str("(((1+23)*1-22)+5)*2-7");
	ASSERT_ANY_THROW(str.Calculate());
}
TEST(TPostfix, cannot_be_divided_by_zero)
{
	TPostfix str("1+2/(3-3)");
	str.ToPostfix();
	ASSERT_ANY_THROW(str.Calculate());
}

