#ifndef TESTSPR_SPROUT_ALGORITHM_GENERATE_HPP
#define TESTSPR_SPROUT_ALGORITHM_GENERATE_HPP

#include <sprout/algorithm/generate.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_generate_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// 生成
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate(
					arr1,
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}}
					));
			}
			// 生成
			// 範囲の切り出し
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(generated),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate(
					sprout::sub(arr1, 2, 8),
					testspr::x2<int>(),
					2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{2, 4, 8, 16, 32, 64}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(generated),
					array<int, 10>{{1, 2, 2, 4, 8, 16, 32, 64, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_GENERATE_HPP

