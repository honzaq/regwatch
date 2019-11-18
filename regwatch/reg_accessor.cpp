#include <Windows.h>
#include "reg_accessor.h"
#include <ktmw32.h>
#include "scope_guard.h"

namespace regwatcher
{

int32_t reg_accessor::create_key(HKEY hKey, const wchar_t* sub_key, reg_handle& rh)
{
	//
	struct KeyData {
		GUID guid = { 0 };
	};
	KeyData key_data;
	auto result = CoCreateGuid(&key_data.guid);
	if (result != S_OK) {
		throw std::exception("Cannot create key GUID");
	}

	HANDLE hTransaction = ::CreateTransaction(nullptr, 0, 0, 0, 0, 300, nullptr);
	if (hTransaction == INVALID_HANDLE_VALUE) {
		//return ::GetLastError();
		throw std::exception("Create transaction fail.");
	}
	auto trans_guard = scope_guard([hTransaction]() {
		::CloseHandle(hTransaction);
	});

	auto result = ::RegCreateKeyTransacted(hKey, sub_key, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, rh.put(), nullptr, hTransaction, nullptr);
	if (result != ERROR_SUCCESS) {
		return result;
	}

	


	// we must commit it or it will be reverted
	::CommitTransaction(hTransaction);

	return ERROR_SUCCESS;
}

int32_t reg_accessor::delete_key(HKEY hKey, const wchar_t* sub_key, bool recursivelly /*= false*/)
{
	return int32_t();
}

int32_t reg_accessor::write_value(HKEY hKey, const wchar_t* value_name, DWORD type, const std::byte* data, uint32_t data_size)
{
	return int32_t();
}

int32_t reg_accessor::read_value(HKEY hKey, const wchar_t* value_name, LPDWORD type, LPBYTE data, LPDWORD data_size)
{
	return int32_t();
}

} // end of namespace regwatcher