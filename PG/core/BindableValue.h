#pragma once

#include <functional>
#include <functional>

namespace PG {

//--------------------------------------------------------
template <typename T>
class BindableValue
{
public:
	using callback_func = std::function<void (const T&)>;
	using callback_func_array = std::vector<callback_func>; // Do something better than this

	//--------------------------------------------------------
	BindableValue()
	: m_Value(T())
	{}
	
	//--------------------------------------------------------
	explicit BindableValue(const T& initialValue)
	: m_Value(initialValue)
	{}
	
	BindableValue(const BindableValue<T>& initialValue) = delete;

	//--------------------------------------------------------
	const T& get() const
	{
		return m_Value;
	}
	
	//--------------------------------------------------------
	void set(const T& value)
	{
		m_Value = value;
		
		for (auto& valueChangedFunc : m_ValueChangedFuncs)
		{
			valueChangedFunc(m_Value);
		}
	}
	
	//--------------------------------------------------------
	void setBinding(const callback_func& func)
	{
		m_ValueChangedFuncs.push_back(func);
		func(m_Value);
	}
	
	//--------------------------------------------------------
	void clearBindings()
	{
		m_ValueChangedFuncs.clear();
	}

	//--------------------------------------------------------
	BindableValue<T>& operator++()
	{
		++m_Value;
		set(m_Value);
		return *this;
	}
	
	//--------------------------------------------------------
	BindableValue<T>& operator--()
	{
		--m_Value;
		set(m_Value);
		return *this;
	}

	//--------------------------------------------------------
	const T& operator*() const
	{
		return m_Value;
	}
	
	//--------------------------------------------------------
	BindableValue<T>& operator=(const T& v)
	{
		set(v);
		return *this;
	}
	
	//--------------------------------------------------------
	bool operator<=(const T& v)
	{
		return m_Value <= v;
	}

private:
	T					m_Value;
	callback_func_array	m_ValueChangedFuncs;
};

}
