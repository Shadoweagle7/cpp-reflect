#ifndef SE7_UTIL
#define SE7_UTIL

#include <type_traits>

namespace SE7 {
	constexpr size_t strlen(const char *str, size_t count = 0) {
		if (str == nullptr) {
			return 0;
		}

		return (str[0] == '\0') ? count : strlen(str + 1, count + 1);
	}

	template<char c, char... cs>
	struct rec_print {
		
	};

	template<char c>
	struct rec_print<c> {

	};

	template<char... cs>
	struct exploded_string {

	};

	template<class string_provider, size_t N, char... cs>
	struct explode_impl {
		using result = typename explode_impl<string_provider, N - 1, string_provider::str()[N - 1],
			cs...>::result;
	};

	template<class string_provider, char... cs>
	struct explode_impl<string_provider, 0U, cs...> {
		using result = exploded_string<cs...>;
	};

	template<class string_provider>
	using explode = typename explode_impl<string_provider, strlen(string_provider::str())>::result;

	template<class S, class = const char *()>
	struct is_string_provider : std::false_type {};

	template<class S>
	struct is_string_provider<S, decltype(S::str)> : std::true_type {};

	struct string_provider {
		static constexpr const char *str() {
			return "";
		}
	};
}

#endif // !SE7_UTIL
