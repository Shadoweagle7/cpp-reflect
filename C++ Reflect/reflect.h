#ifndef SE7_REFLECT
#define SE7_REFLECT

#include <iostream>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <functional>
#include <tuple>
#include <numeric>
#include <cstdint>
#include <initializer_list>
#include <map>

#define STRINGIFY(x) #x

#ifdef __cplusplus

namespace SE7 {
	class base {
	public:
		base() {
			std::cout << "base::base()" << std::endl;
		}

		~base() {
			std::cout << "base::~base()" << std::endl;
		}
	};

	class derived : public base {
	public:
		derived() {
			std::cout << "derived::derived()" << std::endl;
		}

		~derived() {
			std::cout << "derived::~derived()" << std::endl;
		}
	};

	template<class T, bool is_class_type = std::is_class<T>::value>
	class reflect;

	template<class T>
	class reflect<T, false> final {
	private:
		T *ptr;
		std::type_index datatype;
	public:
		using type = T;

		reflect() : datatype(typeid(T)) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_size_in_bytes() const {
			return sizeof(T);
		}

		~reflect() {

		}
	};

	template<class T>
	class reflect<T, true> final {
	private:
		T *ptr;
		std::type_index datatype;
	public:
		using type = T;

		reflect() : datatype(typeid(T)) {}

		template<class... argv>
		constexpr bool is_constructible() const {
			return std::is_constructible<T, argv...>::value;
		}

		template<class... argv>
		constexpr bool is_nothrow_constructible() const {
			return std::is_nothrow_constructible<argv...>::value;
		}

		template<class... argv>
		constexpr bool is_trivially_constructible() const {
			return std::is_trivially_constructible<T, argv...>::value;
		}

		constexpr bool is_default_constructible() const {
			return std::is_default_constructible<T>::value;
		}

		constexpr bool is_nothrow_default_constructible() const {
			return std::is_nothrow_default_constructible<T>::value;
		}

		constexpr bool is_trivially_default_constructible() const {
			return std::is_trivially_default_constructible<T>::value;
		}

		constexpr bool is_copy_constructible() const {
			return std::is_copy_constructible<T>::value;
		}

		constexpr bool is_nothrow_copy_constructible() const {
			return std::is_nothrow_copy_constructible<T>::value;
		}

		constexpr bool is_trivially_copy_constructible() const {
			return std::is_trivially_copy_constructible<T>::value;
		}

		constexpr bool is_move_constructible() const {
			return std::is_move_constructible<T>::value;
		}

		constexpr bool is_nothrow_move_constructible() const {
			return std::is_nothrow_move_constructible<T>::value;
		}

		constexpr bool is_trivially_move_constructible() const {
			return std::is_trivially_move_constructible<T>::value;
		}

		template<class U>
		constexpr bool is_assignable() const {
			return std::is_assignable<T, U>::value; // Assign U to T
		}

		template<class U>
		constexpr bool is_nothrow_assignable() const {
			return std::is_nothrow_assignable<T, U>::value; // Assign U to T
		}

		template<class U>
		constexpr bool is_trivially_assignable() const {
			return std::is_trivially_assignable<T, U>::value; // Assign U to T
		}

		constexpr bool is_copy_assignable() const {
			return std::is_copy_assignable<T>::value;
		}

		constexpr bool is_nothrow_copy_assignable() const {
			return std::is_nothrow_copy_assignable<T>::value;
		}

		constexpr bool is_trivially_move_assignable() const {
			return std::is_trivially_move_assignable<T>::value;
		}

		constexpr bool is_move_assignable() const {
			return std::is_move_assignable<T>::value;
		}

		constexpr bool is_nothrow_move_assignable() const {
			return std::is_nothrow_move_assignable<T>::value;
		}

		constexpr bool is_trivially_move_assignable() const {
			return std::is_trivially_move_assignable<T>::value;
		}

		constexpr bool is_trivial() const {
			return std::is_trivial<T>::value;
		}

		constexpr bool is_destructible() const {
			return std::is_destructible<T>::value;
		}

		constexpr bool is_trivially_destructible() const {
			return std::is_trivially_destructible<T>::value;
		}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_size_in_bytes() const {
			return sizeof(T);
		}

		~reflect() {}
	};

	template<class T, size_t N>
	class reflect<T[N], false> final {
	private:
		std::type_index datatype;
	public:
		using type = T[N];

		reflect() : datatype(typeid(T[N])) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_type_size() const {
			return sizeof(T);
		}

		constexpr size_t get_array_size() const {
			return N;
		}

		constexpr size_t get_size_of_memory_occupied() const {
			return sizeof(T[N]);
		}

		~reflect() {}
	};

	template<class T>
	class reflect<T *, false> final {
	private:
		std::type_index datatype;
	public:
		using type = T *;

		static constexpr T *null_pointer = nullptr;

		reflect() : datatype(typeid(T *)) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_size_in_bytes() const {
			return sizeof(T *);
		}

		reflect<T> get_pointed_to_type() const {
			return reflect<T>();
		}

		static constexpr std::intptr_t to_intptr(const T *ptr) const {
			return reinterpret_cast<std::intptr_t>(ptr);
		}

		static constexpr std::intptr_t to_uintptr(const T *ptr) const {
			return reinterpret_cast<std::uintptr_t>(ptr);
		}

		static constexpr T *to_ptr(std::intptr_t i) const {
			return reinterpret_cast<T *>(i);
		}

		static constexpr T *to_ptr(std::uintptr_t i) const {
			return reinterpret_cast<T *>(i);
		}

		~reflect() {}
	};

	template<class T, class...argv>
	class reflect<T(argv...), false> final {
	private:
		std::type_index datatype;
		std::tuple<reflect<argv>...> parameters;
	public:
		using type = T(argv...);

		reflect() : datatype(typeid(T(argv...))) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_pointer_size() const {
			return sizeof(T (*)(argv...));
		}

		constexpr size_t get_number_of_arguments() const {
			return sizeof...(argv);
		}

		constexpr size_t get_minimum_frame_size() const {
			// sizeof(pointer) == sizeof(register)

			return sizeof(std::intptr_t) + (sizeof(std::intptr_t) * sizeof...(argv));
		}

		reflect<T> get_reflected_return_type() const {
			return reflect<T>();
		}

		template<size_t I>
		decltype(auto) get_reflected_type_of_arg() {
			return std::get<I>(this->parameters);
		}
	};

	template<class R, class T, class... argv>
	class reflect<R (T:: *)(argv...), false> final {
	private:
		std::type_index datatype;
		std::tuple<reflect<argv>...> parameters;
	public:
		using type = R(T:: *)(argv...);

		reflect() : datatype(typeid(R(T:: *)(argv...))) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_pointer_size() const {
			return sizeof(R(T:: *)(argv...));
		}

		constexpr size_t get_number_of_arguments() const {
			return sizeof...(argv);
		}

		constexpr size_t get_minimum_frame_size() const {
			// sizeof(pointer) == sizeof(register)

			return sizeof(std::intptr_t) + (sizeof(std::intptr_t) * (1U + sizeof...(argv))); // this pointer
		}

		reflect<R> get_reflected_return_type() const {
			return reflect<R>();
		}

		template<size_t I>
		decltype(auto) get_reflected_type_of_arg() {
			return std::get<I>(this->parameters);
		}
	};

	template<class R, class T, class... argv>
	class reflect<R(T:: *)(argv...) const, false> final {
	private:
		std::type_index datatype;
		std::tuple<reflect<argv>...> parameters;
	public:
		using type = R(T:: *)(argv...) const;

		reflect() : datatype(typeid(R(T:: *)(argv...) const)) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_pointer_size() const {
			return sizeof(R(T:: *)(argv...) const);
		}

		constexpr size_t get_number_of_arguments() const {
			return sizeof...(argv);
		}

		constexpr size_t get_minimum_frame_size() const {
			// sizeof(pointer) == sizeof(register)

			return sizeof(std::intptr_t) + (sizeof(std::intptr_t) * (1U + sizeof...(argv))); // this pointer
		}

		reflect<R> get_reflected_return_type() const {
			return reflect<R>();
		}

		template<size_t I>
		decltype(auto) get_reflected_type_of_arg() {
			return std::get<I>(this->parameters);
		}
	};

	template<class R, class T, class... argv>
	class reflect<R(T:: *)(argv...) const &, false> final {
	private:
		std::type_index datatype;
		std::tuple<reflect<argv>...> parameters;
	public:
		using type = R(T:: *)(argv...) const &;

		reflect() : datatype(typeid(R(T:: *)(argv...) const &)) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_pointer_size() const {
			return sizeof(R(T:: *)(argv...) const &);
		}

		constexpr size_t get_number_of_arguments() const {
			return sizeof...(argv);
		}

		constexpr size_t get_minimum_frame_size() const {
			// sizeof(pointer) == sizeof(register)

			return sizeof(std::intptr_t) + (sizeof(std::intptr_t) * (1U + sizeof...(argv))); // this pointer
		}

		reflect<R> get_reflected_return_type() const {
			return reflect<R>();
		}

		template<size_t I>
		decltype(auto) get_reflected_type_of_arg() {
			return std::get<I>(this->parameters);
		}
	};

	template<class R, class T, class... argv>
	class reflect<R(T:: *)(argv...) const &&, false> final {
	private:
		std::type_index datatype;
		std::tuple<reflect<argv>...> parameters;
	public:
		using type = R(T:: *)(argv..) const &&;

		reflect() : datatype(typeid(R(T:: *)(argv...) const &&)) {}

		const char *get_name() const {
			return this->datatype.name();
		}

		constexpr size_t get_pointer_size() const {
			return sizeof(R(T:: *)(argv...) const &&);
	}

		constexpr size_t get_number_of_arguments() const {
			return sizeof...(argv);
		}

		constexpr size_t get_minimum_frame_size() const {
			// sizeof(pointer) == sizeof(register)

			return sizeof(std::intptr_t) + (sizeof(std::intptr_t) * (1U + sizeof...(argv))); // this pointer
		}

		reflect<R> get_reflected_return_type() const {
			return reflect<R>();
		}

		template<size_t I>
		decltype(auto) get_reflected_type_of_arg() {
			return std::get<I>(this->parameters);
		}
	};
}

#else

#endif // __cplusplus

#endif // !SE7_REFLECT
