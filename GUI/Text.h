#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>
#include "DXException.h"
#include "UIBase.h"

namespace ui{

/**
* Esta clase implementa la estructura más simple de la biblioteca gráfica, un texto. Encapsula funcionalidad mínima para poder pintar en pantalla un objeto 2D simple.
* Se trata de uno de los mayores puntos de cohesión de la biblioteca con el motor de render, y por lo tanto candidata a la reimplementación si este varia.
*/
class Text{

public:
	/**
	* Constructor de Text.
	* @param pD3Ddevice puntero a un dispositivo D3D9.	
	* @param iWidth ancho en pixels del bitmap.
	* @param iHeight alto en pixels del bitmap.
	* @param iFontSize entero con el tamaño de la fuente.
	* @param iWeight entero con el peso de la fuente.
	* @param bIsItalic booleano que indica si el texto estará en cursiva.
	* @param wFormat flag para justificación y alineado del texto.
	* @param pwsFontName nombre de la fuente del sistema a utilizar.
	* @param pwcText texto.
	*/
	Text(IDirect3DDevice9* pD3Ddevice,int iFontSize, int iWeight, bool bIsItalic, const WCHAR* pwsFontName) throw(DXException);	

	/**
	* Constructor de Text.
	* @param pD3Ddevice puntero a un dispositivo D3D9.
	* @param iXpos posición de pintado X, en pixels.
	* @param iYpos posición de pintado Y, en pixels.
	* @param iWidth ancho en pixels del bitmap.
	* @param iHeight alto en pixels del bitmap.
	* @param iFontSize entero con el tamaño de la fuente.
	* @param iWeight entero con el peso de la fuente.
	* @param bIsItalic booleano que indica si el texto estará en cursiva.
	* @param wFormat flag para justificación y alineado del texto.
	* @param pwsFontName nombre de la fuente del sistema a utilizar.
	* @param pwcText texto.
	*/
	Text(IDirect3DDevice9* pD3Ddevice,int iXpos, int iYpos, int iHeight, int iWidth,int iFontSize, int iWeight, bool bIsItalic,DWORD wFormat, const WCHAR* pwsFontName, const WCHAR* pwcText) throw(DXException);	

	void drawTextHere(int iXpos, int iYpos,int iHeight,int iWidth, const WCHAR* wcpText, DWORD format)throw(DXException);

	/**
	* Dibuja el texto.
	*/
	void draw(void);
	
	/**
	* Modifica el texto mostrado.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setText(const WCHAR* wcpText);	

	/**
	* Modifica el tamaño de la fuente.
	* @param iSize entero con el nuevo tamaño de la fuente.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setFontSize(int iSize);

	/**
	* Modifica el peso de la fuente.
	* @param iWeight entero con el nuevo peso de la fuente.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setFontWeight(int iWeight);

	/**
	* Indica si el texto aparece o no en cursiva.
	* @param bIsItalic booleano indicando si el texto está en cursiva.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setFontItalic(bool bIsItalic);

	/**
	* Modifica la fuente del texto mostrado.
	* @param pwsFontName nombre de la nueva fuente.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setFontName(const WCHAR* pwsFontName);	
	
	/**
	* Modifica el color de la fuente del texto mostrado.
	* @param fontColor color.
	* @return éxito o fracaso de la operación en forma de HRESULT.
	*/
	HRESULT setFontColor(fontColor fontColor);

	/**
	* Destructor
	*/
	~Text(void);

private:	
	D3DXFONT_DESC m_fontDesc;
	LPD3DXFONT m_pFont;
	std::wstring m_wsFileName;	
	std::wstring m_wsText;
	IDirect3DDevice9* m_pD3Ddevice;	

	int m_iXpos;
	int m_iYpos;
	int m_iHeight;
	int m_iWidth;
	DWORD m_wFormat;
	fontColor m_color;

};
}
#endif