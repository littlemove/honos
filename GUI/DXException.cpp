#include "DXUT.h"
#include "DXException.h"
#include <stdlib.h>
#include <dxerr.h>

using namespace ui;

DXException::DXException(HRESULT hr) : std::exception(), m_wsErrorDescription(){

	const WCHAR* pErrorString = DXGetErrorString(hr);	
	m_wsErrorDescription = pErrorString; 	
}

DXException::DXException(const ui::DXException& dxe){
	m_wsErrorDescription = std::wstring(dxe.m_wsErrorDescription);
}
void DXException::addMoreInfo(std::wstring wsMoreInfo){
	m_wsErrorDescription += L" - " + wsMoreInfo + L"\n";
}

const wchar_t* DXException::what(){
	
	return m_wsErrorDescription.c_str();
}

DXException::~DXException(void){}
