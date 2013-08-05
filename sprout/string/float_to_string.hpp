#ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
#define SPROUT_STRING_FLOAT_TO_STRING_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string/string.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/detail/char_conversion.hpp>
#include <sprout/detail/math/int.hpp>
#include <sprout/detail/math/float.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		SPROUT_STATIC_CONSTEXPR std::size_t decimal_places_length = 6;
	}	// namespace detail

	//
	// printed_float_digits
	//
	template<typename FloatType>
	struct printed_float_digits
		: public std::integral_constant<
			std::size_t,
			std::numeric_limits<FloatType>::max_exponent10 + sprout::detail::decimal_places_length + 2
		>
	{};

	namespace detail {
		template<typename Elem, typename FloatType, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string_impl(FloatType val, bool negative, int digits, int v, sprout::index_tuple<Indexes...>) {
			typedef sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value> type;
			return negative
				? type{
					{
						static_cast<Elem>('-'),
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
							: Indexes == digits ? static_cast<Elem>('.')
							: Indexes < digits + 1 + sprout::detail::decimal_places_length
								? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(v, digits + sprout::detail::decimal_places_length - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits + 2 + sprout::detail::decimal_places_length)
					}
				: type{
					{
						(Indexes < digits ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, digits - 1 - Indexes))
							: Indexes == digits ? static_cast<Elem>('.')
							: Indexes < digits + 1 + sprout::detail::decimal_places_length
								? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(v, digits + sprout::detail::decimal_places_length - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(digits + 1 + sprout::detail::decimal_places_length)
					}
				;
		}
		template<typename Elem, typename FloatType>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
		float_to_string(FloatType val, bool negative, int digits) {
			return sprout::detail::float_to_string_impl<Elem>(
				val, negative, digits, static_cast<int>((val - sprout::math::floor(val)) * sprout::detail::int_pow<int>(sprout::detail::decimal_places_length)),
				sprout::make_index_tuple<sprout::printed_float_digits<FloatType>::value - 1>::make()
				);
		}
	}	// namespace detail

	//
	// float_to_string
	//
	template<
		typename Elem, typename FloatType,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
	float_to_string(FloatType val) {
		typedef sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value> type;
		return sprout::math::isinf(val) ? sprout::math::signbit(val)
				? type{{static_cast<Elem>('-'), static_cast<Elem>('i'), static_cast<Elem>('n'), static_cast<Elem>('f')}, 4}
				: type{{static_cast<Elem>('i'), static_cast<Elem>('n'), static_cast<Elem>('f')}, 3}
			: sprout::math::isnan(val) ? sprout::math::signbit(val)
				? type{{static_cast<Elem>('-'), static_cast<Elem>('n'), static_cast<Elem>('a'), static_cast<Elem>('n')}, 4}
				: type{{static_cast<Elem>('n'), static_cast<Elem>('a'), static_cast<Elem>('n')}, 3}
			: sprout::detail::float_to_string<Elem>(
				sprout::detail::float_round_at(val < 0 ? -val : val, sprout::detail::decimal_places_length),
				sprout::math::signbit(val),
				sprout::detail::float_digits(val)
				)
			;
	}

	namespace detail {
		template<typename FloatType>
		struct printed_float_exponent10_digits
			: public std::integral_constant<
				std::size_t,
				NS_SSCRISK_CEL_OR_SPROUT::max(sprout::detail::int_digits(std::numeric_limits<FloatType>::max_exponent10), 2)
			>
		{};
	}	// namespace detail

	//
	// printed_float_exp_digits
	//
	template<typename FloatType>
	struct printed_float_exp_digits
		: public std::integral_constant<
			std::size_t,
			5 + sprout::detail::decimal_places_length + sprout::detail::printed_float_exponent10_digits<FloatType>::value
		>
	{};

	namespace detail {
		template<typename Elem, typename FloatType, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value>
		float_to_string_exp(FloatType val, bool negative, int exponent10, int e10_digits, sprout::index_tuple<Indexes...>) {
			typedef sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value> type;
			return negative
				? type{
					{
						static_cast<Elem>('-'),
						(Indexes == 0 ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 0))
							: Indexes == 1 ? static_cast<Elem>('.')
							: Indexes < 2 + sprout::detail::decimal_places_length
								? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 1 - Indexes))
							: Indexes == 2 + sprout::detail::decimal_places_length ? static_cast<Elem>('e')
							: Indexes == 3 + sprout::detail::decimal_places_length ? static_cast<Elem>(exponent10 < 0 ? '-' : '+')
							: Indexes < 4 + sprout::detail::decimal_places_length + e10_digits
								? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(exponent10, 3 + sprout::detail::decimal_places_length + e10_digits - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(5 + sprout::detail::decimal_places_length + e10_digits)
					}
				: type{
					{
						(Indexes == 0 ? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 0))
							: Indexes == 1 ? static_cast<Elem>('.')
							: Indexes < 2 + sprout::detail::decimal_places_length
								? sprout::detail::int_to_char<Elem>(sprout::detail::float_digit_at(val, 1 - Indexes))
							: Indexes == 2 + sprout::detail::decimal_places_length ? static_cast<Elem>('e')
							: Indexes == 3 + sprout::detail::decimal_places_length ? static_cast<Elem>(exponent10 < 0 ? '-' : '+')
							: Indexes < 4 + sprout::detail::decimal_places_length + e10_digits
								? sprout::detail::int_to_char<Elem>(sprout::detail::int_digit_at(exponent10, 3 + sprout::detail::decimal_places_length + e10_digits - Indexes))
							: Elem()
							)...
						},
						static_cast<std::size_t>(4 + sprout::detail::decimal_places_length + e10_digits)
					}
				;
		}
	}	// namespace detail

	//
	// float_to_string_exp
	//
	template<
		typename Elem, typename FloatType,
		typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value>
	float_to_string_exp(FloatType val) {
		typedef sprout::basic_string<Elem, sprout::printed_float_exp_digits<FloatType>::value> type;
		return sprout::math::isinf(val) ? sprout::math::signbit(val)
				? type{{static_cast<Elem>('-'), static_cast<Elem>('i'), static_cast<Elem>('n'), static_cast<Elem>('f')}, 4}
				: type{{static_cast<Elem>('i'), static_cast<Elem>('n'), static_cast<Elem>('f')}, 3}
			: sprout::math::isnan(val) ? sprout::math::signbit(val)
				? type{{static_cast<Elem>('-'), static_cast<Elem>('n'), static_cast<Elem>('a'), static_cast<Elem>('n')}, 4}
				: type{{static_cast<Elem>('n'), static_cast<Elem>('a'), static_cast<Elem>('n')}, 3}
			: sprout::detail::float_to_string_exp<Elem>(
				sprout::detail::float_round_at(
					(val < 0 ? -val : val) / sprout::detail::float_pow10<FloatType>(sprout::detail::float_exponent10(val)),
					sprout::detail::decimal_places_length
					),
				sprout::math::signbit(val),
				sprout::detail::float_exponent10(val),
				NS_SSCRISK_CEL_OR_SPROUT::max(sprout::detail::int_digits(sprout::detail::float_exponent10(val)), 2),
				sprout::make_index_tuple<sprout::printed_float_exp_digits<FloatType>::value - 1>::make()
				)
			;
	}

	//
	// to_string_of
	//
	template<typename Elem, typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<Elem, sprout::printed_float_digits<FloatType>::value>
	to_string_of(FloatType val) {
		return sprout::float_to_string<Elem>(val);
	}

	//
	// to_string
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char, sprout::printed_float_digits<FloatType>::value>
	to_string(FloatType val) {
		return sprout::to_string_of<char>(val);
	}

	//
	// to_wstring
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, sprout::printed_float_digits<FloatType>::value>
	to_wstring(FloatType val) {
		return sprout::to_string_of<wchar_t>(val);
	}

	//
	// to_u16string
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, sprout::printed_float_digits<FloatType>::value>
	to_u16string(FloatType val) {
		return sprout::to_string_of<char16_t>(val);
	}

	//
	// to_u32string
	//
	template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, sprout::printed_float_digits<FloatType>::value>
	to_u32string(FloatType val) {
		return sprout::to_string_of<char32_t>(val);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_FLOAT_TO_STRING_HPP
