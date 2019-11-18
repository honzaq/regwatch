#pragma once

#include <assert.h>

namespace regwatcher {

namespace implementation {

	template <typename T>
	class scope_lambda
	{
	public:
		scope_lambda(const scope_lambda&) = delete;
		scope_lambda& operator=(const scope_lambda&) = delete;
		scope_lambda& operator=(scope_lambda&& other) = delete;

		explicit scope_lambda(T&& lambda) noexcept
			: m_lambda(std::move(lambda))
		{
			static_assert(std::is_same<decltype(lambda()), void>::value, "scope_exit lambdas must not have a return value");
			static_assert(!std::is_lvalue_reference<T>::value && !std::is_rvalue_reference<T>::value, "scope_exit should only be directly used with a lambda");
		}

		scope_lambda(scope_lambda&& other) noexcept
			: m_lambda(wistd::move(other.m_lambda))
			, m_release(other.m_release)
		{
			other.m_release = false;
		}

		~scope_lambda() noexcept
		{
			release();
		}

		// Ensures the scope_exit lambda will not be called
		void dismiss() noexcept
		{
			m_release = false;
		}

		// Executes the scope_exit lambda immediately if not yet run; ensures it will not run again
		void release() noexcept
		{
			if (m_release) {
				m_release = false;
				try {
					m_lambda();
				}
				catch (...) {
					assert(false && "scope_exit lambda throw exception");
				}
			} 
		}

		// Returns true if the scope_exit lambda is still going to be executed
		explicit operator bool() const noexcept
		{
			return m_release;
		}

	protected:
		T m_lambda;
		bool m_release = true;
	};

} // end of namespace implementation

template <typename T>
[[nodiscard]] inline auto scope_guard(T&& lambda) noexcept
{
	return implementation::scope_lambda<T>(std::forward<T>(lambda));
}

}