#include <exception>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <mipp.h>
#include <catch.hpp>

template <typename T>
void test_reg_cmpneq()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	for (auto t = 0; t < 100; t++)
	{
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::reg r1 = mipp::load<T>(inputs1);
		mipp::reg r2 = mipp::load<T>(inputs2);
		mipp::msk m  = mipp::cmpneq<T>(r1, r2);

		mipp::reg r3 = mipp::toreg<mipp::N<T>()>(m);

		for (auto i = 0; i < mipp::N<T>(); i++)
		{
			if (inputs1[i] != inputs2[i])
				REQUIRE(*((T*)&r3 +i) != (T)0);
			else
				REQUIRE(*((T*)&r3 +i) == (T)0);
		}
	}
}

#ifndef MIPP_NO
TEST_CASE("Compare not equal - mipp::reg", "[mipp::cmpneq]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_reg_cmpneq<double>(); }
#endif
	SECTION("datatype = float") { test_reg_cmpneq<float>(); }

#if !defined(MIPP_AVX) || defined(MIPP_AVX2) || (defined(MIPP_AVX) && !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC))
#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int64_t") { test_reg_cmpneq<int64_t>(); }
#endif
#endif
	SECTION("datatype = int32_t") { test_reg_cmpneq<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_reg_cmpneq<int16_t>(); }
	SECTION("datatype = int8_t") { test_reg_cmpneq<int8_t>(); }
#endif
#if defined(MIPP_AVX2) || defined(MIPP_AVX512) || ((defined(MIPP_AVX) && !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC)))
	SECTION("datatype = uint32_t") { test_reg_cmpneq<uint32_t>(); }
#endif
}
#endif

template <typename T>
void test_Reg_cmpneq()
{
	T inputs1[mipp::N<T>()], inputs2[mipp::N<T>()];
	std::iota(inputs1, inputs1 + mipp::N<T>(), (T)1);
	std::iota(inputs2, inputs2 + mipp::N<T>(), (T)1);

	std::mt19937 g;
	for (auto t = 0; t < 100; t++)
	{
		std::shuffle(inputs1, inputs1 + mipp::N<T>(), g);
		std::shuffle(inputs2, inputs2 + mipp::N<T>(), g);

		mipp::Reg<T> r1 = inputs1;
		mipp::Reg<T> r2 = inputs2;
		mipp::Msk<mipp::N<T>()> m = r1 != r2;

		for (auto i = 0; i < mipp::N<T>(); i++)
			REQUIRE(m[i] == (inputs1[i] != inputs2[i]));
	}
}

TEST_CASE("Compare not equal - mipp::Reg", "[mipp::cmpneq]")
{
#if defined(MIPP_64BIT)
	SECTION("datatype = double") { test_Reg_cmpneq<double>(); }
#endif
	SECTION("datatype = float") { test_Reg_cmpneq<float>(); }

#if !defined(MIPP_AVX) || defined(MIPP_AVX2) || (defined(MIPP_AVX) && !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC))
#if defined(MIPP_64BIT)
#if !defined(MIPP_SSE) || (defined(MIPP_SSE) && MIPP_INSTR_VERSION >= 41)
	SECTION("datatype = int64_t") { test_Reg_cmpneq<int64_t>(); }
#endif
#endif
	SECTION("datatype = int32_t") { test_Reg_cmpneq<int32_t>(); }
#endif
#if defined(MIPP_BW)
	SECTION("datatype = int16_t") { test_Reg_cmpneq<int16_t>(); }
	SECTION("datatype = int8_t") { test_Reg_cmpneq<int8_t>(); }
#endif
#if defined(MIPP_AVX2) || defined(MIPP_AVX512) || ((defined(MIPP_AVX) && !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC)))
	SECTION("datatype = uint32_t") { test_Reg_cmpneq<uint32_t>(); }
#endif
}
