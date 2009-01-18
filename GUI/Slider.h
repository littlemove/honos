#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "UIComponent.h"
#include "Bitmap.h"
#include "Button.h"

namespace ui{

	/**
	* Clase que define un Silder.
	* 
	* Permite definir un slider proporcionando dos archivos de textura: uno como fondo estático y otro como marcador móvil. Además permite
	* crear sliders horizontales y verticales de manera indistinta.
	*/
	class Slider : public UIComponent{

	public:
		/**
		* Constructor de slider.
		*
		* @param pD3Ddevice puntero a un dispositivo D3D9.
		* @param pwcID cadena identificador único del slider.
		* @param bVertical true si el slider es vertival | false si es horizontal.
		* @param wcpImageFilename cadena con la ruta de la imagen de fondo estática.
		* @param wcpButtonFilename cadena con la ruta de la imagen móvil.
		* @param iXpos posición de pintado X, en pixels.
		* @param iYpos posición de pintado Y, en pixels.
		*/
		Slider(IDirect3DDevice9* pD3Ddevice, const WCHAR* pwcID, bool bVertical, const WCHAR* wcpBarFilename, const WCHAR* wcpButtonFilename, int iXpos,int iYpos);

		/**
		* Dibuja el slider.
		*/
		void draw(void);

		/**
		* Manejador de los eventos generados por el interfaz de usuario.	
		* @param pUIState puntero a la estructura que guarda el estado del interfaz.
		* @return evento respuesta del componente.
		* @see UIComponent
		*/
		EVENT_ID OnMouseAction(UIState* pUIState);

		/**
		* Accede al valor de una propiedad del componente si existe y coloca su valor en una dirección de memoria indicada.
		* @param wsName nombre de la propiedad.
		* @param pdValue dirección donde guardar el valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool getProperty(std::wstring wsName, double* pdValue);

		/**
		* Modifica el valor de una propiedad del componente si existe.
		* @param wsName nombre de la propiedad.
		* @param wsValue cadena que representa el nuevo valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool setProperty(std::wstring wsName, std::wstring wsValue);	

		/**
		* Destructor.
		*/
		~Slider(void);

	private:
		int m_iButtonPosition;
		bool m_bIsVertical;
		int m_iMaxValue;
		int m_iMinValue;
		double m_dCurrentValue;

		Bitmap* m_pBackground; 
		Bitmap* m_pButton;

		/**
		* Configura la posición de la parte movil del slider para que represente el valor pasado como parámetro.
		* @param dValue [0-1] valor del slider.
		*/
		void setCurrentValue(double dValue);

		/**
		* Devuelve el valor actual del slider.
		* @return double [0-1] valor actual del slider.
		*/
		double getCurrentValue() const;
	};
}
#endif
