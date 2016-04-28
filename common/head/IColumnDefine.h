#pragma once
enum tp_data_type
{
	dt_long_t,
	dt_double_t,
	dt_char_t,
	dt_string_t,
	dt_decimal_t,
	dt_numeric_t,
	dt_data_time_t,
    dt_long_long_t
};
struct IColumnDefine 
{
	virtual ~IColumnDefine()
	{
	}
	virtual void Set(bool bNull, bool bUnique = false, const char* sDefault = "") = 0;
	virtual void SetCollate(const char* sCollate) = 0;
	virtual void SetLittleNum(long nNum) = 0;
	virtual void SetAutoIncrease(long nBegin = 1, long nNum = 1) = 0;
};