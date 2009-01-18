#include "DXUT.h"
#include "Text.h"
#include "DXException.h"

using namespace ui;

Text::Text(IDirect3DDevice9* pD3Ddevice,int iFontSize, int iWeight, bool bIsItalic, const WCHAR* pwsFontName){	
	HRESULT hr;	

	m_pD3Ddevice = pD3Ddevice;	

	m_pFont = NULL;

	try{
	//Inicializamos la  descripción fuente con valor por defecto.
	D3DXFONT_DESC defaultFontDesc =	{24,  0, 400, 1, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH, L"Arial"};	
	m_fontDesc = defaultFontDesc;

	V_RET(setFontSize(iFontSize));
	V_RET(setFontItalic(bIsItalic));
	V_RET(setFontName(pwsFontName));
	V_RET(setFontWeight(iWeight));

	V_RET(D3DXCreateFontIndirect(pD3Ddevice, &m_fontDesc, &m_pFont));

	V_RET(setText(L""));
	
	}
	catch(DXException e){
		SAFE_RELEASE(m_pFont);

		throw DXException(hr);
	}
}

Text::Text(IDirect3DDevice9* pD3Ddevice,int iXpos, int iYpos, int iHeight, int iWidth,int iFontSize, int iWeight, bool bIsItalic,DWORD wFormat, const WCHAR* pwsFontName, const WCHAR* pwcText) throw(DXException){	
	HRESULT hr;	

	m_pD3Ddevice = pD3Ddevice;	

	m_pFont = NULL;

	try{
	//Inicializamos la  descripción fuente con valor por defecto.
	D3DXFONT_DESC defaultFontDesc =	{24,  0, 400, 1, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH, L"Arial"};	
	m_fontDesc = defaultFontDesc;

	V_RET(setFontSize(iFontSize));
	V_RET(setFontItalic(bIsItalic));
	V_RET(setFontName(pwsFontName));
	V_RET(setFontWeight(iWeight));

	V_RET(D3DXCreateFontIndirect(pD3Ddevice, &m_fontDesc, &m_pFont));

	m_wsText = pwcText;
	m_iXpos = iXpos;
	m_iYpos = iYpos;
	m_iHeight = iHeight;
	m_iWidth = iWidth;
	m_wFormat = wFormat;
	m_color = WHITE;
	}
	catch(DXException e){
		SAFE_RELEASE(m_pFont);

		throw DXException(hr);
	}
}

void Text::drawTextHere(int iXpos, int iYpos,int iHeight,int iWidth, const WCHAR* wcpText, DWORD format){
	HRESULT hr;
	
		V_RET(setText(wcpText));
		RECT fontPosition = {iXpos, iYpos, iXpos + iWidth, iYpos + iHeight};				
		D3DCOLOR color = D3DCOLOR_RGBA(255,255,255,0);		
		V_RET(m_pFont->DrawText(NULL, m_wsText.c_str(), -1, &fontPosition, format, 0xf1000000));	
}

void Text::draw(void){
	HRESULT hr;	
		
		RECT fontPosition = {m_iXpos, m_iYpos, m_iXpos + m_iWidth, m_iYpos + m_iHeight};				
		//D3DCOLOR color = D3DCOLOR_RGBA(255,255,255,0);		
		V_RET(m_pFont->DrawText(NULL, m_wsText.c_str(), -1, &fontPosition, m_wFormat, m_color));	
}

HRESULT Text::setText(const WCHAR* wcpText){
	HRESULT hr = S_OK;

	if(wcpText != NULL){
		m_wsText = wcpText;
	}
	else{
		hr = E_INVALIDARG;
	}

	return hr;	
}

HRESULT Text::setFontName(const WCHAR* pzwsFontName){
	HRESULT hr = S_OK;

		
		std::wstring wsTemp = pzwsFontName;
		if(wsTemp.length() < LF_FACESIZE) wcscpy(m_fontDesc.FaceName, pzwsFontName);
		else hr = E_INVALIDARG;


	return hr;
}

HRESULT Text::setFontSize(int iSize){
	HRESULT hr = S_OK;
	
		if(iSize > 0) m_fontDesc.Height = iSize;
		else hr = E_INVALIDARG;
		
		D3DXCreateFontIndirect(m_pD3Ddevice, &m_fontDesc, &m_pFont);

	return hr;
}

HRESULT Text::setFontWeight(int iWeight){
	HRESULT hr = S_OK;

	
		if(iWeight >= 0 && iWeight <= 1000) m_fontDesc.Weight = iWeight;
		else hr = E_INVALIDARG;
	

	return hr;
}

HRESULT Text::setFontItalic(bool bIsItalic){
	HRESULT hr = S_OK;

	
		m_fontDesc.Italic = bIsItalic;
	

	return hr;
}

HRESULT Text::setFontColor(fontColor fontColor){
	HRESULT hr = S_OK;

	m_color = fontColor;

	return hr;
}

Text::~Text(void){
	SAFE_RELEASE(m_pFont);	
}

