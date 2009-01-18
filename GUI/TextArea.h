#ifndef _TEXT_AREA_H_
#define _TEXT_AREA_H_

#include "UIComponent.h"
#include "Text.h"
#include "Bitmap.h"

#include <string>

namespace ui{

	/**
	* Defina un componente "area de texto", es decir, area plana rectángular que puede tener una imagen de fondo y sobre la que se
	* renderiza texto.
	*/
	class TextArea : public UIComponent {

	public:
		/**
		* Contructor de TextArea.
		* @param pD3Ddevice puntero a un dispositivo D3D9.
		* @param pwcID cadena identificador único de la TextArea.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.
		* @param iWidth ancho en pixels de la TextArea.
		* @param iHeight alto en pixels de la TextArea.
		* @param pwcFontName cadena con el nombre de la fuente a utilizar.
		* @param iFontSize tamaño de la fuente.
		* @param iFontWidth ancho de la fuente.
		* @param wFormat flags que indican el formateo del texto.
		* @param pwcText texto a rendernizar.
		* @param pwcBackgroundFile ruta al fichero imagen para el fondo (opcional)
		* @param bStrechBackground true indica que la imagen de fondo ocupará todo el area | false la imagen conservará su aspecto original. Por defecto false.
		*/
		TextArea(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, int iHeight, int iWidth,	const WCHAR* pwcFontName, int iFontSize,int iFontWidth,DWORD wFormat, const WCHAR* pwcText,const WCHAR* pwcBackgroundFile = NULL, bool bStrechBackground = false);

		/**
		* Dibuja la TextArea.
		*/
		void draw(void);

		/**
		* Modifica el valor de una propiedad del componente si existe.
		* @param wsName nombre de la propiedad.
		* @param wsValue cadena que representa el nuevo valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool setProperty(std::wstring wsName, std::wstring wsValue);

		void setFontWeight(int iValue);

		/**
		* Destructor.
		*/
		~TextArea(void);

	private:
		Text* m_pText;
		Bitmap* m_pBitmap;
	};
}
#endif