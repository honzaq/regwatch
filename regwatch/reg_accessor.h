#pragma once

#include "reg_accessor_intf.h"

namespace regwatcher
{

class reg_accessor : public reg_accessor_intf
{
public:
	reg_accessor();

	int32_t create_key(HKEY hKey, const wchar_t* sub_key, reg_handle& rh) override;

	int32_t delete_key(HKEY hKey, const wchar_t* sub_key, bool recursivelly = false) override;

	int32_t write_value(HKEY hKey, const wchar_t* value_name, DWORD type, const std::byte* data, uint32_t data_size) override;

	int32_t read_value(HKEY hKey, const wchar_t* value_name, LPDWORD type, LPBYTE data, LPDWORD data_size) override;

};

} // end of namespace regwatcher