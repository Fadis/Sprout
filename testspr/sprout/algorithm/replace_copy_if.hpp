#ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_COPY_IF_HPP
#define TESTSPR_SPROUT_ALGORITHM_REPLACE_COPY_IF_HPP

#include <sprout/algorithm/replace_copy_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_replace_copy_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) の範囲を置換 (is_odd -> -1)
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 10>{{-1, 0, -1, 0, -1, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
			}
			// [2 .. 8) の範囲を置換 (is_odd -> -1)
			// 出力範囲をオーバーする場合
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 4>{{-1, 0, -1, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 4>{{-1, 0, -1, 0}}
					));
			}
			// [2 .. 8) の範囲を置換 (is_odd -> -1)
			// 出力範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(replaced),
					array<int, 10>{{0, 0, -1, 0, -1, 0, -1, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto replaced = sprout::fit::replace_copy_if(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>(),
					-1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					replaced,
					array<int, 6>{{-1, 0, -1, 0, -1, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(replaced),
					array<int, 10>{{0, 0, -1, 0, -1, 0, -1, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REPLACE_COPY_IF_HPP

