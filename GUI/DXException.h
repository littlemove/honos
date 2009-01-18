#ifndef _DXEXCEPTION_H_
#define _DXEXCEPTION_H_

#include <exception>
#include <string>

namespace ui{

	/**
	* Esta clase es una especialización de una excepción estándar C++ aplicada a los errores relacionados con DirectX.
	*/
	class DXException :	public std::exception{

	public:
		DXException(HRESULT hr);
		void addMoreInfo(std::wstring wsMoreInfo);
		const wchar_t* what();
		DXException(const DXException&);
		~DXException(void);

	private:
		std::wstring m_wsErrorDescription;
	};
}
#endif
