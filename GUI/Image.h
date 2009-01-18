#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "DXException.h"
#include "UIBase.h"
#include "Bitmap.h"
#include "EventsIDs.h"
#include "UIComponent.h"
#include <string>

namespace ui{

	/**
	* Esta clase define un componente gráfico "imagen", es decir, una area plana interactiva representada por una textura.
	*/
	class Image : public UIComponent {

	public:
		/**
		* Constructor de Image.
		* @param pD3Ddevice puntero a un dispositivo D3D9.	
		* @param pwcID cadena identificador único del botón.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.
		* @param iHeight alto en pixels del bitmap.
		* @param iWidth ancho en pixels del bitmap.	
		* @param pwcBitmapFile cadena con la ubicación del archivo de textura principal.	
		*/
		Image(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, int iHeight, int iWidth, const WCHAR* pwcBitmapFile);

		/**
		* Constructor de Image. 
		* 
		* El ancho y alto del componente se calcula automáticamente ajustándose al de la textura proporcionada.
		* @param pD3Ddevice puntero a un dispositivo D3D9.	
		* @param pwcID cadena identificador único del botón.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.	
		* @param pwcBitmapFile cadena con la ubicación del archivo de textura principal.	
		*/
		Image(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, const WCHAR* pwcBitmapFile);

		/**
		* Manejador de los eventos generados por el interfaz de usuario.	
		* @param pUIState puntero a la estructura que guarda el estado del interfaz.
		* @return evento respuesta del componente.
		* @see UIComponent
		*/
		EVENT_ID OnMouseAction(UIState* pUIState);

		/**
		* Dibuja el botón.
		*/
		void draw(void);

		/**
		* Destructor.
		*/
		~Image(void);

	private:
		Bitmap* m_pBitmap;
	};
}
#endif
