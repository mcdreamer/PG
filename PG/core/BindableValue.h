#pragma once

#include <functional>

namespace PG {

//--------------------------------------------------------
template <typename T>
class BindableValue
{
public:
	using callback_func = std::function<void (const T&)>;

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
		
		if (m_ValueChangedFunc)
		{
			m_ValueChangedFunc(m_Value);
		}
	}
	
	//--------------------------------------------------------
	void setBinding(const callback_func& func)
	{
		m_ValueChangedFunc = func;
		m_ValueChangedFunc(m_Value);
	}

	//--------------------------------------------------------
	BindableValue<T>& operator++()
	{
		++m_Value;
		m_ValueChangedFunc(m_Value);
		return *this;
	}
	
	//--------------------------------------------------------
	BindableValue<T>& operator--()
	{
		--m_Value;
		m_ValueChangedFunc(m_Value);
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

private:
	T				m_Value;
	callback_func	m_ValueChangedFunc;
};

}
