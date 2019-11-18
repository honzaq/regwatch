#pragma once

#include <string>
#include <cstddef>
#include "reg_handle.h"

namespace regwatcher
{

class reg_accessor_intf
{
public:
	virtual ~reg_accessor_intf() = default;

	virtual int32_t create_key(HKEY hKey, const wchar_t* sub_key, reg_handle& rh) = 0;

	virtual int32_t delete_key(HKEY hKey, const wchar_t* sub_key, bool recursivelly = false) = 0;

	virtual int32_t write_value(HKEY hKey, const wchar_t* value_name, DWORD type, const std::byte* data, uint32_t data_size) = 0;

	virtual int32_t read_value(HKEY hKey, const wchar_t* value_name, LPDWORD type, LPBYTE data, LPDWORD data_size) = 0;

};

}