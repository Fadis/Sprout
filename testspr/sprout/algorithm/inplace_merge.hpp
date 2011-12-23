#ifndef TESTSPR_SPROUT_ALGORITHM_INPLACE_MERGE_HPP
#define TESTSPR_SPROUT_ALGORITHM_INPLACE_MERGE_HPP

#include <sprout/algorithm/inplace_merge.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_inplace_merge_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 3, 5, 7, 9, 2, 4, 6, 8, 10}};

			// マージ
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::inplace_merge(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::inplace_merge(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// マージ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::inplace_merge(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 4, 5, 6, 7, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{1, 3, 2, 4, 5, 6, 7, 9, 8, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::inplace_merge(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 4, 5, 6, 7, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{1, 3, 2, 4, 5, 6, 7, 9, 8, 10}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 3, 5, 7, 9, 2, 4, 6, 8, 10}};

			// マージ
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::inplace_merge(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::inplace_merge(
					arr1,
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// マージ
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::inplace_merge(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 4, 5, 6, 7, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{1, 3, 2, 4, 5, 6, 7, 9, 8, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::inplace_merge(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{2, 4, 5, 6, 7, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{1, 3, 2, 4, 5, 6, 7, 9, 8, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_INPLACE_MERGE_HPP

