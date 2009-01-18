#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include <map>
#include <list>
#include "EventsIDs.h"
#include "UIComponent.h"

namespace ui{

	/**
	* Esta estructura almacena la infomación sobre un evento: tipo e identificador del componente que lo provoco.
	*/
	struct EventListNode{
		EVENT_ID eventID;
		const WCHAR* pwcComponentID;
	};

	/**
	* Esta clase se encarga de agrupar y gestionar todos lo componentes que conforman el interfaz de usuario.
	* 
	* UIManager mantiene un registro de los componentes creados, traduce los eventos generados por el hardware en información que los componentes
	* pueden procesar, envía dicha información a los componente ya actua como puente para la intercomunicación de los mismos. Además define y 
	* controla la posición Z de los componentes.
	* 
	*/
	class UIManager{

	public:
		/**
		* Constructor de UIManager.
		*/
		UIManager(void);

		/**
		* Registra un componente creado y le asigna una posición Z. Se asegura de que no se insertes componentes con el mismo identificador.
		* @param pUIComponent puntero al componente.
		* @param iZpos posición Z.
		*/
		void addUIComponent(UIComponent* pUIComponent, int iZpos);

		/**
		* Elimina un componente del registro y se asegura de que se liberen los recursos.
		* @param pUIComponent puntero al componente.	
		*/
		void deleteUIComponent(UIComponent* pUIComponent);

		/**
		* Elimina un componente del registro y se asegura de que se liberen los recursos.
		* @param wsUIComponentID identificador del componente.	
		*/
		void deleteUIComponent(std::wstring  wsUIComponentID);	

		/**
		* Elimina un componente del registro y se asegura de que se liberen los recursos.
		* @param pwcUIComponentID identificador del componente.	
		*/
		void deleteUIComponent(WCHAR* pwcUIComponentID);

		/**
		* Modifica la posición Z de un componente.
		* @param wsComponetID identificador del componente.	
		* @param iZValue nueva posición Z.
		*/
		void changeUIComponentZ(std::wstring wsComponetID, int iZValue);

		/**
		* Modifica el valor de una propiedad del componente si existe.
		* @param wsComponetID identificador del componente.	
		* @param wsName nombre de la propiedad.
		* @param wsValue cadena que representa el nuevo valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool setProperty(std::wstring wsComponentID, std::wstring wsName, std::wstring wsValue);	

		/**
		* Accede al valor de una propiedad del componente si existe y coloca su valor en una dirección de memoria indicada.
		* @param wsComponetID identificador del componente.	
		* @param wsName nombre de la propiedad.
		* @param pdValue dirección donde guardar el valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool getProperty(std::wstring wsComponentID, std::wstring wsName, int* piValue);

		/**
		* Accede al valor de una propiedad del componente si existe y coloca su valor en una dirección de memoria indicada.
		* @param wsComponetID identificador del componente.	
		* @param wsName nombre de la propiedad.
		* @param pdValue dirección donde guardar el valor de la propiedad.
		* @return true si la propiedad existe | false en otro caso.
		* @see UIComponent
		*/
		bool getProperty(std::wstring wsComponentID, std::wstring wsName, double* piValue);

		void drawUI();

		/**
		* Cambia el valor de la posició Z de un UIComponent para que se pinte por encima del resto.
		*
		* @param pUIComponent puntero al UIComponent que se quiere llevar al frente.
		* @return entero con la diferencia entre la antigua y la nueva Z.
		*/
		int moveToFront(UIComponent* pUIComponent);

		/**
		* Procesa las señales emitidas por el ratón y las evnvía todos los componentes de la interfaz de usuario.
		* @param bLeftButtonDown true si el botón izquierdo del ratón está pulsado.
		* @param bRightButtonDown true si el botón derecho del ratón está pulsado.
		* @param bMiddleButtonDown true si el botón central del ratón está pulsado.
		* @param nMouseWheelDelta número de pasos de la rueda del ratón.
		* @param iXpos posición X del ratón.
		* @param iYpos psición Y del ratón.
		* @return número de eventos nuevos añadidos a la lista de eventos (m_eventList).
		*/
		int OnMouseAction(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, int nMouseWheelDelta, int iXpos, int iYpos);

		std::list<EventListNode>* getEventList();

		/**
		* Destructor.
		*/
		~UIManager(void);

	private:	
		std::multimap<int,UIComponent*> m_componentList;
		std::list<EventListNode> m_eventList;
		UIState m_uistate;	
	};
}
#endif