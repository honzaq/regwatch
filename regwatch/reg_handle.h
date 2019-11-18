#pragma once

#include <wtypes.h>

namespace regwatcher
{

class reg_handle
{
public:
	reg_handle(const HKEY& hKey)
		: m_hKey(hKey)
	{}

	reg_handle(reg_handle&& rh) noexcept
	{
		m_hKey = rh.m_hKey;
		rh.m_hKey = nullptr;
	}

	~reg_handle()
	{
		if (m_hKey != nullptr) {
			::RegCloseKey(m_hKey);
		}
	}

	reg_handle& operator=(reg_handle&& rh) noexcept
	{
		if (this != &rh) {
			if (m_hKey != nullptr) {
				::RegCloseKey(m_hKey);
			}
			m_hKey = rh.m_hKey;
			rh.m_hKey = nullptr;
		}

		return *this;
	}

	HKEY* put() throw()
	{
		return &m_hKey;
	}

	operator HKEY() const
	{
		return m_hKey;
	}

private:
	HKEY m_hKey = nullptr;
};

} // end of namespace regwatcher