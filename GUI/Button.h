#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "DXException.h"
#include "UIBase.h"
#include "Bitmap.h"
#include "Text.h"
#include "EventsIDs.h"
#include "UIComponent.h"
#include <string>

namespace ui{

	/**
	* Clase que implementa un botón 2D.
	* Permite definir un botón cuya apariencia viene dada por (como máximo) un par de texturas. El texto del botón, de haberlo, se genera dinámicamente, 
	* es decir, que no tiene porque estar incluido en la textura.
	*/
	class Button : public UIComponent {

	public:
		/**
		* Contructor de Button. Inicializa y reserva todos los recursos necesarios para poder representar un botón.
		* @param pD3Ddevice puntero a un dispositivo D3D9.
		* @param pwcID cadena identificador único del botón.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.
		* @param pwcMainTextureFile cadena con la ubicación del archivo de textura principal.
		* @param pwcPressedTextureFile cadena con la ubicación del archivo de textura secundario.
		* @param pwcText cadena con el texto del botón.
		*/
		Button(IDirect3DDevice9* pD3Ddevice,const WCHAR* pwcID, int iXpos, int iYpos, const WCHAR* pwcMainTextureFile, const WCHAR* pwcPressedTextureFile, const WCHAR* pwcText);

		/**
		* Contructor de Button. Inicializa y reserva todos los recursos necesarios para poder representar un botón.
		* @param pD3Ddevice puntero a un dispositivo D3D9.
		* @param pwcID cadena identificador único del botón.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.
		* @param pwcMainTextureFile cadena con la ubicación del archivo de textura principal.
		* @param pwcPressedTextureFile cadena con la ubicación del archivo de textura secundario.
		* @param pwcText cadena con el texto del botón.
		* @param pwcFontName nombre de la fuente.
		* @param iFontSize tamaño de la fuente.
		*/
		Button(IDirect3DDevice9* pD3Ddevice,const WCHAR* pwcID, int iXpos, int iYpos, const WCHAR* pwcMainTextureFile, const WCHAR* pwcPressedTextureFile, const WCHAR* pwcText, const WCHAR* pwcFontName, int iFontSize);

		/**
		* Dibuja el botón.
		*/
		void draw();	

		/**
		* Destructor del botón.
		*/
		~Button(void);

		/**
		* Manejador de los eventos generados por el interfaz de usuario.	
		* @param pUIState puntero a la estructura que guarda el estado del interfaz.
		* @return evento respuesta del componente.
		* @see UIComponent
		*/
		EVENT_ID OnMouseAction(UIState* pUIState);

	private:

		bool m_bIsPressed;	
		std::wstring m_wsText;

		Bitmap* m_pMainBitmap;
		Bitmap* m_pPressedBitmap;
		ui::Text* m_pText;		

		/**
		* Cambia el estado del botón entre "presionado" y "no presionado".
		* @param bPressed true si se quiere pasar al estado "presionado" | false en otro caso.
		*/
		void setPressed(bool bPressed);
	};
}
#endif
