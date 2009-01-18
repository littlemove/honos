#ifndef _UILOADER_H_
#define _UILOADER_H_

#include <string>
#include <exception>
#include "UIManager.h"
#include "Button.h"
#include "Image.h"
#include "Slider.h"
#include "TextArea.h"
#include "UIManager.h"
#include "../libs/tinyxml/tinyxml/tinyxml.h"

namespace ui{
	/**
	* Esta clase se encarga de crear los componentes que componen la interfaz de usuario, ya sea vía archivo XML
	* o "programaticamente".
	*/
	class UILoader{

	public:
		/**
		* Constructor de UILoader.
		* @param pUIManager puntero a UIManager.
		* @param pd3dDevice puntero a un device de DX válido.
		*/
		UILoader(UIManager* pUIManager, IDirect3DDevice9* pd3dDevice);
		
		/**
		* Crea un componente del tipo y características especificados.
		* @param wsType tipo del componente.
		* @param wsID identificador único del componente.
		* @param iXpos posición X del componente.
		* @param iYpos posición Y del componente.
		* @param iZpos posición Z del componente.
		* @param iHeight altura del componente.
		* @param iWidth anchura del componente.
		* @param wsTexture1 ruta a fichero de textura.
		* @param wsTexture2 ruta a fichero de textura.
		* @param wsText texto.
		*/
		void addUIComponent(std::wstring wsType,
			std::wstring wsID,
			int iXpos,
			int iYpos,
			int iZpos,
			int iHeight,
			int iWidth,
			std::wstring wsTexture1,
			std::wstring wsTexture2,
			std::wstring wsText);

		void loadFromXML(std::string sFile);

		~UILoader();

	private:
		UIManager* m_pUIManger;
		IDirect3DDevice9* m_pd3dDevice;
		
		/**
		* Crea un componente de tipo Botón.	
		* @param wsID identificador único del componente.
		* @param iXpos posición X del componente.
		* @param iYpos posición Y del componente.
		* @param iZpos posición Z del componente.		
		* @param wsMainTexture ruta a fichero de textura principal.
		* @param wsPressedTexture ruta a fichero de textura secundario.
		* @param wsText texto.
		*/
		void addButton( std::wstring wsID,
			int iXpos,
			int iYpos,
			int iZpos,
			std::wstring wsMainTexture,
			std::wstring wsPressedTexture,
			std::wstring wsText) throw(std::exception);

		/**
		* Crea un componente de tipo Imagen.	
		* @param wsID identificador único del componente.
		* @param iXpos posición X del componente.
		* @param iYpos posición Y del componente.
		* @param iZpos posición Z del componente.		
		* @param wsMainTexture ruta a fichero de textura principal.		
		*/
		void addImage( std::wstring wsID,
			int iXpos,
			int iYpos,
			int iZpos,
			int iHeight,
			int iWidth,
			std::wstring wsMainTexture) throw(std::exception);

		/**
		* Crea un componente del tipo Area de texto.
		* @param wsType tipo del componente.
		* @param wsID identificador único del componente.
		* @param iXpos posición X del componente.
		* @param iYpos posición Y del componente.
		* @param iZpos posición Z del componente.
		* @param iHeight altura del componente.
		* @param iWidth anchura del componente.
		* @param wsTexture ruta a fichero de textura.		
		* @param wsText texto.
		*/
		void addTextArea(std::wstring wsID,
			int iXpos,
			int iYpos,
			int iZpos,
			int iHeight,
			int iWidth,
			std::wstring wsTexture,
			std::wstring wsText) throw(std::exception);

		/**
		* Crea un componente de tipo Slider.	
		* @param wsID identificador único del componente.
		* @param iXpos posición X del componente.
		* @param iYpos posición Y del componente.
		* @param iZpos posición Z del componente.		
		* @param wsImageTexture ruta a fichero de textura de la barra.
		* @param wsButtonTexture ruta a fichero de textura del botón o marcador.
		* @param wsText texto.
		*/
		void addSlider(std::wstring wsID,
			int iXpos,
			int iYpos,
			int iZpos,
			std::wstring wsImageTexture,
			std::wstring wsButtonTexture) throw(std::exception);

		int processXMLAtribute(TiXmlElement* pElement);

		void processXMLNode(TiXmlNode* pParent);
	};
}
#endif
