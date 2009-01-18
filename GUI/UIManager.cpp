#include "DXUT.h"
#include "UIManager.h"

using namespace ui;

UIManager::UIManager(void){

	m_uistate.pwcHot = NULL;
	m_uistate.pwcActive = NULL;
	m_uistate.bLeftButtonDown = false;
}

UIManager::~UIManager(void){	
	std::multimap<int,UIComponent*>::iterator iter;
	
	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		delete iter->second;
	}
}

void UIManager::addUIComponent(UIComponent *pUIComponent, int iZpos){
	std::multimap<int,UIComponent*>::iterator iter;
	std::wstring wsCurrent;
	std::wstring wsNew = pUIComponent->getID();

	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		wsCurrent = iter->second->getID();
		if(wsCurrent == wsNew){
			throw std::exception("Elementos con el mimso identificador");
		}
		//if(iter->second->getID() == pUIComponent->getID()) throw std::exception();
	}
	m_componentList.insert(std::make_pair(iZpos,pUIComponent));
}


void UIManager::deleteUIComponent(UIComponent* pUIComponent){
	std::multimap<int,UIComponent*>::iterator iter;
	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		if(iter->second == pUIComponent){
			m_componentList.erase(iter);
			delete pUIComponent;
			break;
		}
	}	
}

/**
* Para que todos los recursos queden liberados hay que eliminar el objeto UIComponent de la lista de componentes y de memoria.
*/
void UIManager::deleteUIComponent(std::wstring wsUIComponentID){
	std::multimap<int,UIComponent*>::iterator iter;
	UIComponent* pTemp = NULL;
	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		std::wstring wsCurrent = iter->second->getID();
		if(wsCurrent == wsUIComponentID){
			pTemp = iter->second;
			m_componentList.erase(iter);
			delete pTemp;
			break;
		}
	}	
}

void UIManager::deleteUIComponent(WCHAR* pwcUIComponentID){
	std::wstring wsTemp = pwcUIComponentID;
	deleteUIComponent(wsTemp);
}

void UIManager::changeUIComponentZ(std::wstring wsComponetID, int iZValue){
	std::multimap<int,UIComponent*>::iterator iter;
	std::wstring wsCurrent;
	UIComponent* pUIComponent = NULL;

	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		wsCurrent = iter->second->getID();
		if(wsCurrent == wsComponetID){
			pUIComponent = iter->second;
			m_componentList.erase(iter);
			addUIComponent(pUIComponent,iZValue);
			break;
		}
	}
}


void UIManager::drawUI(void){
	std::multimap<int,UIComponent*>::iterator iter;
	
	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		bool bVisible = iter->second->isVisible();
		if(bVisible) iter->second->draw();
	}
}

int UIManager::OnMouseAction(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, int nMouseWheelDelta, int iXpos, int iYpos){

	/***************************Preprocesado del envío de DXUT************************************/	

	EVENT_ID evCurrentButton = E_NO_EVENT;
	EVENT_ID evCurrentHot = E_NO_EVENT;

	m_uistate.iMouseXpos = iXpos;
	m_uistate.iMouseYpos = iYpos;

	/////////// Cambios de estado en el botón  ///////////
	if(bLeftButtonDown && !m_uistate.bLeftButtonDown){
		
		m_uistate.evMouse = E_BUTTON_DOWN;
		
	}
	
	else if(!bLeftButtonDown && m_uistate.bLeftButtonDown){
		
		m_uistate.evMouse = E_BUTTON_UP;
		
	}

	m_uistate.bLeftButtonDown = bLeftButtonDown;

	/////////// Cambios de estado de hot  ///////////	

	std::multimap<int,UIComponent*>::reverse_iterator revIter;	

	for(revIter = m_componentList.rbegin() ; revIter != m_componentList.rend(); ++revIter){
		if(revIter->second->isVisible() && revIter->second->isOver(iXpos, iYpos)){
			if(m_uistate.pwcHot == NULL) m_uistate.evHot = 0;

			else if(m_uistate.pwcHot != revIter->second->getID()) m_uistate.evHot = 0;

			else if(m_uistate.pwcHot == revIter->second->getID())	m_uistate.evHot = E_NO_EVENT;			

			m_uistate.pwcHot = revIter->second->getID(); 
			break;
		}
		else{			
			m_uistate.pwcHot = NULL;
		}
	}	
	
	/***************************************************************************************/

	// Envío de eventos de ratón a los componentes y almacenamiento en la lista de eventos:
	std::multimap<int,UIComponent*>::iterator iter;
	m_eventList.clear();
	iter =  m_componentList.end();
	int iNewEventCounter = 0;
	while(iter != m_componentList.begin()){
		EVENT_ID evID;
		const WCHAR* pwcUIComponentID;
		--iter;

		evID = iter->second->OnMouseAction(&m_uistate);

		if(evID != E_NO_EVENT){
			pwcUIComponentID = iter->second->getID();
			EventListNode e = {evID,pwcUIComponentID};
			m_eventList.push_back(e);
			iNewEventCounter++;
		}
	}	

	return iNewEventCounter;
}

int UIManager::moveToFront(UIComponent* pUIComponent){
	std::multimap<int,UIComponent*> temp;
	std::multimap<int,UIComponent*>::iterator iter;

	m_componentList.swap(temp);

	m_componentList.empty();
	int iOldZ = -1;
	int i = 0;
	for(iter = temp.begin(); iter != temp.end(); ++iter){
		if(iter->second != pUIComponent){
			addUIComponent(iter->second,i);
			i++;
		}
		else{
			iOldZ = iter->first;
		}
	}
	addUIComponent(pUIComponent,i);
	return (i - iOldZ);
}


bool UIManager::setProperty(std::wstring wsComponentID, std::wstring wsName, std::wstring wsValue){

	bool bResult = false;
	std::multimap<int,UIComponent*>::iterator iter;

	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		std::wstring wsCurrent = iter->second->getID();
		if(wsCurrent.compare(wsComponentID) == 0){
			if(iter->second->setProperty(wsName, wsValue)){
				bResult = true;
			}
			break;
		}
	}
	
	return bResult;
}

bool UIManager::getProperty(std::wstring wsComponentID, std::wstring wsName, int *piValue){
	bool bResult = false;
	std::multimap<int,UIComponent*>::iterator iter;

	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		std::wstring wsCurrent = iter->second->getID();
		if(wsCurrent.compare(wsComponentID) == 0){
			if(iter->second->getProperty(wsName, piValue)){
				bResult = true;
			}
			break;
		}
	}
	
	return bResult;
}

bool UIManager::getProperty(std::wstring wsComponentID, std::wstring wsName, double *pdValue){
	bool bResult = false;
	std::multimap<int,UIComponent*>::iterator iter;

	for(iter = m_componentList.begin(); iter != m_componentList.end(); ++iter){
		std::wstring wsCurrent = iter->second->getID();
		if(wsCurrent.compare(wsComponentID) == 0){
			if(iter->second->getProperty(wsName, pdValue)){
				bResult = true;
			}
			break;
		}
	}
	
	return bResult;
}

std::list<EventListNode>* UIManager::getEventList(){
	return &m_eventList;
}