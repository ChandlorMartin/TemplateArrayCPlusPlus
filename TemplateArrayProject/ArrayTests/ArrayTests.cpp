#include "pch.h"
#include "CppUnitTest.h"
#include "../TemplateArray/Array.h"
#include "../TemplateArray/Exception.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const int START_INDEX = 3;
const int LENGTH = 15;
const int DEFAULT_START_INDEX = 0;
const int DEFAULT_START_LENGTH = 0;
const int TEST_DATA_LENGTH = 10;
const int INTEGER_TEST_DATA[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const string STRING_TEST_DATA[] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };

namespace ArrayTests
{
	TEST_CLASS(IntegerArrayUnitTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			Array<int> integer_array;

			Assert::AreEqual(integer_array.GetSize(), DEFAULT_START_LENGTH);
			Assert::AreEqual(integer_array.GetStartingIndex(), DEFAULT_START_INDEX);
		}

		TEST_METHOD(TestSingleArgumentConstructor)
		{
			Array<int> integer_array(LENGTH);

			Assert::AreEqual(integer_array.GetSize(), 15);
			Assert::AreEqual(integer_array.GetStartingIndex(), DEFAULT_START_INDEX);
		}

		TEST_METHOD(TestDoubleArgumentConstructor)
		{
			Array<int> integer_array(LENGTH, START_INDEX);

			Assert::AreEqual(integer_array.GetSize(), 15);
			Assert::AreEqual(integer_array.GetStartingIndex(), 3);
		}

		TEST_METHOD(TestNegativeLength)
		{
			Array<int> integer_array(20, 0);

			Assert::ExpectException<std::invalid_argument>([&]() { integer_array.SetSize(-5); });
		}

		TEST_METHOD(TestLowerBounds)
		{
			Array<int> integer_array(20, 0);

			Assert::ExpectException<std::domain_error>([&]() { integer_array[-3] = 0; });
		}

		TEST_METHOD(TestUpperBounds)
		{
			Array<int> integer_array(LENGTH, 0);

			Assert::ExpectException<std::domain_error>([&]() { integer_array[30] = 0; });
		}

		TEST_METHOD(TestAddingValues)
		{
			Array<int> integer_array(10);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = integer_array[i] + INTEGER_TEST_DATA[i];
				Assert::AreEqual(integer_array[i], INTEGER_TEST_DATA[i] * 2);
			}
		}

		TEST_METHOD(TestIncreasingLengthOfExistingArray)
		{
			const int new_length = 20;
			Array<int> integer_array(LENGTH);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			integer_array.SetSize(new_length);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				Assert::AreEqual(integer_array[i], INTEGER_TEST_DATA[i]);
			}

			for (int i = 10; i < new_length; ++i)
			{
				Assert::IsTrue(integer_array[i] <= 0);
			}
		}

		TEST_METHOD(TestDecreasingLengthOfExistingArray)
		{
			int new_length = 8;
			Array<int> integer_array(LENGTH);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			integer_array.SetSize(new_length);

			for (int i = 0; i < new_length; ++i)
			{
				Assert::AreEqual(integer_array[i], INTEGER_TEST_DATA[i]);
			}

			Assert::ExpectException<std::domain_error>([&]() { integer_array[8] = 8; });
			Assert::ExpectException<std::domain_error>([&]() { integer_array[9] = 9; });
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Array<int> integer_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			Array<int> integer_array_copy(integer_array);

			Assert::AreEqual(integer_array_copy.GetSize(), TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				Assert::AreEqual(integer_array_copy[i], INTEGER_TEST_DATA[i]);
			}
		}

		TEST_METHOD(TestEqualOperator)
		{
			Array<int> integer_array(TEST_DATA_LENGTH);
			Array<int> integer_array_copy;

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			integer_array_copy = integer_array;

			Assert::AreEqual(integer_array_copy.GetSize(), integer_array.GetSize());
			for (int i = 0; i < integer_array.GetSize(); ++i)
			{
				Assert::AreEqual(integer_array_copy[i], integer_array[i]);
			}
		}

		TEST_METHOD(TestGetSize)
		{
			Array<int> integer_array(TEST_DATA_LENGTH);
			Assert::AreEqual(integer_array.GetSize(), 10);

		}

		TEST_METHOD(TestGetFront)
		{
			Array<int> integer_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			Assert::AreEqual(integer_array.GetFront(), 0);
		}

		TEST_METHOD(TestGetBack)
		{
			Array<int> integer_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				integer_array[i] = INTEGER_TEST_DATA[i];
			}

			Assert::AreEqual(integer_array.GetBack(), 9);
		}

		TEST_METHOD(TestIsEmpty)
		{
			Array<int> integer_array(0);
			Assert::IsTrue(integer_array.IsEmpty());
		}
	};

	TEST_CLASS(StringArrayUnitTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			Array<string> string_array;

			Assert::AreEqual(string_array.GetSize(), DEFAULT_START_LENGTH);
			Assert::AreEqual(string_array.GetStartingIndex(), DEFAULT_START_INDEX);
		}

		TEST_METHOD(TestSingleArgumentConstructor)
		{
			Array<string> string_array(LENGTH);

			Assert::AreEqual(string_array.GetSize(), 15);
			Assert::AreEqual(string_array.GetStartingIndex(), DEFAULT_START_INDEX);
		}

		TEST_METHOD(TestDoubleArgumentConstructor)
		{
			Array<string> string_array(LENGTH, START_INDEX);

			Assert::AreEqual(string_array.GetSize(), 15);
			Assert::AreEqual(string_array.GetStartingIndex(), 3);
		}

		TEST_METHOD(TestNegativeLength)
		{
			Array<string> string_array(20, 0);

			Assert::ExpectException<std::invalid_argument>([&]() { string_array.SetSize(-5); });
		}

		TEST_METHOD(TestLowerBounds)
		{
			Array<string> string_array(20, 0);

			Assert::ExpectException<std::domain_error>([&]() { string_array[-3] = "Zero"; });
		}

		TEST_METHOD(TestUpperBounds)
		{
			Array<string> string_array(LENGTH, 0);

			Assert::ExpectException<std::domain_error>([&]() { string_array[30] = "Zero"; });
		}

		TEST_METHOD(TestAddingValues)
		{
			Array<string> string_array(10);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = string_array[i] + STRING_TEST_DATA[i];
				Assert::AreEqual(string_array[i], STRING_TEST_DATA[i] + STRING_TEST_DATA[i]);
			}
		}

		TEST_METHOD(TestIncreasingLengthOfExistingArray)
		{
			const int new_length = 20;

			Array<string> string_array(LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			string_array.SetSize(new_length);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				Assert::AreEqual(string_array[i], STRING_TEST_DATA[i]);
			}

			for (int i = 10; i < new_length; ++i)
			{
				string val = string_array[i];
				string none = "";
				Assert::AreEqual(val, none);
			}
		}

		TEST_METHOD(TestDecreasingLengthOfExistingArray)
		{
			int new_length = 8;
			Array<string> string_array(LENGTH);

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			string_array.SetSize(new_length);

			for (int i = 0; i < new_length; ++i)
			{
				Assert::AreEqual(string_array[i], STRING_TEST_DATA[i]);
			}

			Assert::ExpectException<std::domain_error>([&]() { string_array[8] = "Eight"; });
			Assert::ExpectException<std::domain_error>([&]() { string_array[9] = "Nine"; });
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Array<string> string_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			Array<string> string_array_copy(string_array);

			Assert::AreEqual(string_array_copy.GetSize(), TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				Assert::AreEqual(string_array_copy[i], STRING_TEST_DATA[i]);
			}
		}

		TEST_METHOD(TestEqualOperator)
		{
			Array<string> string_array(TEST_DATA_LENGTH);
			Array<string> string_array_copy;

			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			string_array_copy = string_array;

			Assert::AreEqual(string_array_copy.GetSize(), string_array.GetSize());
			for (int i = 0; i < string_array.GetSize(); ++i)
			{
				Assert::AreEqual(string_array_copy[i], string_array[i]);
			}
		}

		TEST_METHOD(TestGetSize)
		{
			Array<string> string_array(TEST_DATA_LENGTH);
			Assert::AreEqual(string_array.GetSize(), 10);

		}

		TEST_METHOD(TestGetFront)
		{
			Array<string> string_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			Assert::AreEqual(string_array.GetFront(), (string)"Zero");
		}

		TEST_METHOD(TestGetBack)
		{
			Array<string> string_array(TEST_DATA_LENGTH);
			for (int i = 0; i < TEST_DATA_LENGTH; ++i)
			{
				string_array[i] = STRING_TEST_DATA[i];
			}

			Assert::AreEqual(string_array.GetBack(), (string)"Nine");
		}

		TEST_METHOD(TestIsEmpty)
		{
			Array<string> string_array(0);
			Assert::IsTrue(string_array.IsEmpty());
		}
	};
}
