/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/weed/attr_cnv/results/times.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace results {
				//
				// modulus
				//
				template<std::size_t Limit, typename T, typename = void>
				struct modulus
					: public sprout::weed::attr_cnv::results::times<Limit, T>
				{};
			}	// namespace results
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP
