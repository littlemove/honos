#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>

namespace ui{

	/**
	* Este fichero agrupa una serie de utilidades para ayudar a la conversión de tipos.
	* 
	* Proporciona funciones para convertir a enteros y doubles cadenas de caracteres anchos. También proporciona una forma de convertir
	* números en cadenas de caracteres anchos.
	*/

	class BadConversion : public std::runtime_error {
	public:
		BadConversion(const std::string& s)
			: std::runtime_error(s)
		{ }
	};

	inline int convertToInt(const std::wstring& s)
	{
		std::wistringstream i(s);
		int x;
		if (!(i >> x))
			throw BadConversion("convertToInt");
		return x;
	}

	inline double convertToDouble(const std::wstring& s)
	{
		std::wistringstream i(s);
		double x;
		if (!(i >> x))
			throw BadConversion("convertToDouble");
		return x;
	}

	inline std::wstring stringify(double x)
	{
		std::wostringstream o;
		o << std::setprecision(3);
		if (!(o << x))
			throw BadConversion("stringify(double)");
		return o.str();
	}

}
#endif