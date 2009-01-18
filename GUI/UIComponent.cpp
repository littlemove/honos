#include "DXUT.h"
#include "UIComponent.h"

#include <sstream>

using namespace ui;

UIComponent::UIComponent(const WCHAR* wcpID,int iXpos,int iYpos,int iHeight, int iWidth){
	m_wsID = wcpID;
	m_iXpos = iXpos;
	m_iYpos = iYpos;	
	m_iHeight = iHeight;
	m_iWidth = iWidth;
	m_bVisible = true;
}

UIComponent::~UIComponent(void){}

bool UIComponent::setProperty(std::wstring wsName, std::wstring wsValue){
	if(wsName == L"xpos"){
		setXPosition(convertToInt(wsValue));
		return true;
	}
	else if(wsName == L"ypos"){
		setYPosition(convertToInt(wsValue));
		return true;
	}
	else if(wsName == L"width"){
		setWidth(convertToInt(wsValue));
		return true;
	}
	else if(wsName == L"heigth"){
		setHeight(convertToInt(wsValue));
		return true;
	}
	else if(wsName == L"visible"){
		int iValue = convertToInt(wsValue);
		if(iValue == 1) setVisible(true);
		else if(iValue == 0) setVisible(false);
	}

	return false;
}

bool UIComponent::getProperty(std::wstring wsName, int* piValue){
	if(wsName == L"xpos"){
		*piValue = getXPosition();
		return true;
	}
	else if(wsName == L"ypos"){
		*piValue = getYPosition();
		return true;
	}
	else if(wsName == L"width"){
		*piValue = getWidth();
		return true;
	}
	else if(wsName == L"height"){
		*piValue = getHeight();
		return true;
	}
	//Ufff...
	else if(wsName == L"visible"){
		if(isVisible()) *piValue = 1;
		else *piValue = 0; 
	}

	return false;
}

bool UIComponent::getProperty(std::wstring wsName, double* pdValue){
	if(wsName == L"xpos"){
		*pdValue = getXPosition();
		return true;
	}
	else if(wsName == L"ypos"){
		*pdValue = getYPosition();
		return true;
	}
	else if(wsName == L"width"){
		*pdValue = getWidth();
		return true;
	}
	else if(wsName == L"heigth"){
		*pdValue = getHeight();
		return true;
	}
	//Ufff...
	else if(wsName == L"visible"){
		if(isVisible()) *pdValue = 1.0;
		else *pdValue = 0.0; 
	}

	return false;
}

void UIComponent::setXPosition(int iXpos){
	m_iXpos = iXpos;	
}

void UIComponent::setYPosition(int iYpos){	
	m_iYpos = iYpos;	
}

void UIComponent::setWidth(int iWidth){
	m_iWidth = iWidth;
}

void UIComponent::setHeight(int iHeight){
	m_iHeight = iHeight;
}

void UIComponent::setVisible(bool bVisible){
	m_bVisible = bVisible;
}

int UIComponent::getXPosition() const{
	return m_iXpos;
}

int UIComponent::getYPosition() const{
	return m_iYpos;
}

int UIComponent::getHeight() const{
	return m_iHeight;
}

int UIComponent::getWidth() const{
	return m_iWidth;
}

bool UIComponent::isVisible() const{
	return m_bVisible;
}

const WCHAR* UIComponent::getID() const{
	return m_wsID.c_str();
}

void UIComponent::draw(){}

EVENT_ID UIComponent::OnMouseAction(UIState* pUIState){
	/*if(pUIState->evMouse == E_BUTTON_DOWN) OutputDebugStringW(L"E_BUTTON_DOWN \n");
	else if(pUIState->evMouse == E_BUTTON_UP) OutputDebugStringW(L"E_BUTTON_UP \n");

	if(pUIState->evHot == E_AREA_ENTER) OutputDebugStringW(L"E_AREA_ENTER \n");
	else if(pUIState->evHot == E_AREA_OFF) OutputDebugStringW(L"E_AREA_OFF \n");
	else if(pUIState->evHot == E_AREA_IN) OutputDebugStringW(L"E_AREA_IN \n");	*/	
	
	return E_NO_EVENT;
}

bool UIComponent::isOver(int iXpos, int iYpos) const{
	if((m_iXpos < iXpos) && (iXpos < (m_iXpos + m_iWidth))){
		if((m_iYpos < iYpos) && (iYpos < (m_iYpos + m_iHeight))) return true;
	}
	return false;
}
