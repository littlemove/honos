#include "DXUT.h"
#include "Slider.h"

#include <memory>

using namespace ui;

Slider::Slider(IDirect3DDevice9* pD3Ddevice, const WCHAR* pwcID, bool bVertical, const WCHAR* wcpBarFilename, const WCHAR* wcpButtonFilename, int iXpos,int iYpos) : UIComponent(pwcID,iXpos,iYpos){
	HRESULT hr;	
	
	std::auto_ptr<Bitmap> autopBackgroundBitmap(new Bitmap(pD3Ddevice,wcpBarFilename,iXpos,iYpos));
	std::auto_ptr<Bitmap> autopButtonBitmap(new Bitmap(pD3Ddevice,wcpButtonFilename,iXpos,iYpos));
	
	m_pBackground = autopBackgroundBitmap.release();
	m_pButton = autopButtonBitmap.release();

	m_bIsVertical = bVertical;
	if(bVertical){
		int iHeight = m_pBackground->getHeight();
		int iWidth = m_pButton->getWidth();
		//m_pButton->setXPosition(getXPosition());

		setHeight(iHeight);
		setWidth(iWidth);
	}

	else{
		int iHeight = m_pButton->getHeight();
		int iWidth = m_pBackground->getWidth();		
		//m_pButton->setYPosition(getYPosition());

		setHeight(iHeight);
		setWidth(iWidth);
	}	

	//m_dCurrentValue = 1.0;
}

void Slider::draw(){
	m_pBackground->draw();
	m_pButton->draw();
	/*int iButtonPosition = getXPosition() + (getWidth() * m_dCurrentValue) - (m_pButton->getWidth() / 2);
	if(iButtonPosition < getXPosition()) iButtonPosition = getXPosition();
	else if(iButtonPosition > (getXPosition() + getWidth() - m_pButton->getWidth())) iButtonPosition = getXPosition() + getWidth() - (m_pButton->getWidth());


	if(m_bIsVertical) m_pButton->drawBitmapHere(getXPosition(),m_iButtonPosition - m_pButton->getHeight() / 2);

	else m_pButton->drawBitmapHere(iButtonPosition,getYPosition());*/
}

EVENT_ID Slider::OnMouseAction(UIState* pUIState){
	if(pUIState->pwcHot == getID() && pUIState->evMouse == E_BUTTON_DOWN && pUIState->pwcActive == NULL){
		pUIState->pwcActive = getID();
	}

	if(pUIState->pwcActive == getID() && (pUIState->bLeftButtonDown || pUIState->evMouse == E_BUTTON_DOWN)){
		int iNewValue = pUIState->iMouseXpos;
		int iMaxValue;
		int iMinValue;
		if(!m_bIsVertical){
			iNewValue = pUIState->iMouseXpos - m_pButton->getWidth() / 2;			
			iMaxValue = getXPosition() + getWidth() - m_pButton->getWidth();
			iMinValue = getXPosition();	
		}
		else{
			iMaxValue = getYPosition() + getHeight();
			iMinValue = getYPosition();
		}
		
		if(iNewValue > iMaxValue) iNewValue = iMaxValue;
		else if(iNewValue < iMinValue) iNewValue = iMinValue;	

		m_pButton->setXPosition(iNewValue);
		return E_BUTTON_CLICK;
	}

	else if(pUIState->pwcActive == getID() && pUIState->evMouse == E_BUTTON_UP){
		pUIState->pwcActive = NULL;
	}	
	
	return E_NO_EVENT;
}

bool Slider::getProperty(std::wstring wsName, double* pdValue){
	bool bResult = UIComponent::getProperty(wsName, pdValue);
	if(!bResult){
		if(wsName == L"value"){
			*pdValue = getCurrentValue();
			bResult = true;
		}
	}

	return bResult;
}

bool Slider::setProperty(std::wstring wsName, std::wstring wsValue){

	bool bResult = UIComponent::setProperty(wsName, wsValue);

	if(!bResult){
		if(wsName == L"value"){
			setCurrentValue(convertToDouble(wsValue));
			bResult = true;
		}
	}

	return bResult;
}

void Slider::setCurrentValue(double dValue){

	if(!m_bIsVertical){
		m_pButton->setXPosition(dValue * (getWidth() - m_pButton->getWidth()) + getXPosition());
	}
}

double Slider::getCurrentValue() const{
	double dValue = 0.0;

	if(!m_bIsVertical){
		dValue = (((double)m_pButton->getXPosition() - (double)getXPosition()) / (double)((double)getWidth() - m_pButton->getWidth()));
	}	

	return dValue; 	
}

Slider::~Slider(void){
	delete m_pBackground;
	delete m_pButton;
}
