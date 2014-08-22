//!
//! @file 			TrimTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-08-22
//! @last-modified 	2014-08-22
//! @brief 			Makes sure the String::Trim() method works as expected.
//! @details
//!					See README.rst in root dir for more info.

// User libraries
#include "../lib/UnitTest++/src/UnitTest++.h"

// User source
#include "../api/StringApi.hpp"

namespace StringTestsNs
{
	SUITE(TrimTests)
	{

		//======================== TRIM FROM LEFT TESTS ====================//

		TEST(TrimJustSpacesFromStartTest)
		{
			mNinja::String myString1("   There is white space before me.");

			// Trim white space
			myString1.Trim();

			CHECK_EQUAL("There is white space before me.", myString1.cStr);
		}

		TEST(TrimJustCarriageReturnsFromStartTest)
		{
			mNinja::String myString1("\r\r\rThere are carriage returns before me.");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are carriage returns before me.", myString1.cStr);
		}

		TEST(TrimJustNewLinesFromStartTest)
		{
			mNinja::String myString1("\n\n\nThere are new lines before me.");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are new lines before me.", myString1.cStr);
		}

		TEST(TrimJustTabsFromStartTest)
		{
			mNinja::String myString1("\t\t\tThere are tabs before me.");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are tabs before me.", myString1.cStr);
		}

		TEST(TrimAMixtureOfWhiteSpaceFromStartTest)
		{
			mNinja::String myString1("\r \n     \t There is a mixture of white-space chars before me.");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There is a mixture of white-space chars before me.", myString1.cStr);
		}

		//======================== TRIM FROM END TESTS ====================//

		TEST(TrimJustSpacesFromEndTest)
		{
			mNinja::String myString1("There is white space after me.    ");

			// Trim white space
			myString1.Trim();

			CHECK_EQUAL("There is white space after me.", myString1.cStr);
		}

		TEST(TrimJustCarriageReturnsFromEndTest)
		{
			mNinja::String myString1("There are carriage returns after me.\r\r\r\r");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are carriage returns after me.", myString1.cStr);
		}

		TEST(TrimJustNewLinesFromEndTest)
		{
			mNinja::String myString1("There are new lines after me.\n\n\n\n\n");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are new lines after me.", myString1.cStr);
		}

		TEST(TrimJustTabsFromEndTest)
		{
			mNinja::String myString1("There are tabs after me.\t");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There are tabs after me.", myString1.cStr);
		}

		TEST(TrimAMixtureOfWhiteSpaceFromEndTest)
		{
			mNinja::String myString1("There is a mixture of white-space chars after me.\r  \t\n\n ");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There is a mixture of white-space chars after me.", myString1.cStr);
		}

		//======================== TRIM FROM BOTH ENDS TESTS ====================//

		TEST(TrimAMixtureOfWhiteSpaceFromBothEndsTest)
		{
			mNinja::String myString1("   \t \r\nThere is a mixture of white-space chars before and after me.\r  \t\n\n ");

			// Trim string
			myString1.Trim();

			CHECK_EQUAL("There is a mixture of white-space chars before and after me.", myString1.cStr);
		}

		//======================== DOESN'T TRIM FROM MIDDLE TESTS ====================//

		TEST(DoesntTrimWhiteSpaceFromMiddleOfStringTest)
		{
			mNinja::String myString1("\r \n     \t a\r b\t cdef gh");

			// Trim string
			myString1.Trim();

			//  String should now start the the 'a' char.
			CHECK_EQUAL("a\r b\t cdef gh", myString1.cStr);
		}

		//======================== ONLY TRIM WHAT I'M TOLD TO TESTS ====================//

		TEST(OnlyTrimFromLeftTest)
		{
			mNinja::String myString1(
					"   \t \r\nThere is a mixture of white-space chars before and after me.\r  \t\n\n ");

			// Trim string
			myString1.Trim(mNinja::EndsToTrim::LEFT);

			CHECK_EQUAL(
				"There is a mixture of white-space chars before and after me.\r  \t\n\n ",
				myString1.cStr);
		}

		TEST(OnlyTrimFromRightTest)
		{
			mNinja::String myString1(
					"   \t \r\nThere is a mixture of white-space chars before and after me.\r  \t\n\n ");

			// Trim string
			myString1.Trim(mNinja::EndsToTrim::RIGHT);

			CHECK_EQUAL(
				"   \t \r\nThere is a mixture of white-space chars before and after me.",
				myString1.cStr);
		}

		//======================== SPECIFYING WHAT TO TRIM TESTS ====================//

		TEST(TrimSomeATest)
		{
			mNinja::String myString1(
					"aaaaThere are some 'a' before and after me.\r  \t\n\n aaaa");

			// Trim string
			myString1.Trim(mNinja::String("a"));

			CHECK_EQUAL(
				"There are some 'a' before and after me.\r  \t\n\n ",
				myString1.cStr);
		}

		//======================== EDGE-CASE TRIM TESTS ====================//

		TEST(TrimEmptyStringTest)
		{
			mNinja::String myString1("");

			// Trim string
			myString1.Trim();

			//  String should now be empty.
			CHECK_EQUAL("", myString1.cStr);
		}

		TEST(TrimEmptyStringWithEmptyMatchingCharsTest)
		{
			mNinja::String myString1("");

			// Trim string
			myString1.Trim(mNinja::String());

			//  String should still be empty.
			CHECK_EQUAL("", myString1.cStr);
		}

		TEST(TrimStringWithEmptyMatchingCharsTest)
		{
			mNinja::String myString1("Please don't hurt me!");

			// Trim string
			myString1.Trim(mNinja::String());

			//  String should of not been modified
			CHECK_EQUAL("Please don't hurt me!", myString1.cStr);
		}

		TEST(AllWhiteSpaceTest)
		{
			mNinja::String myString1("\r \n     \t  ");

			// Trim string
			myString1.Trim();

			//  String should now be empty.
			CHECK_EQUAL("", myString1.cStr);
		}

	} // SUITE(TrimTests)
} // namespace StringTestsNs
