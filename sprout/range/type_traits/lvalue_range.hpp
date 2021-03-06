/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_TYPE_TRAITS_LVALUE_RANGE_HPP
#define SPROUT_RANGE_TYPE_TRAITS_LVALUE_RANGE_HPP

#include <sprout/config.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/type_traits/lvalue_iterator.hpp>

namespace sprout {
	namespace range {
		//
		// lvalue_range
		//
		template<typename Range>
		struct lvalue_range {
		public:
			typedef sprout::range::range_container<typename sprout::range::lvalue_iterator<Range>::type> type;
		};
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_TYPE_TRAITS_LVALUE_RANGE_HPP
