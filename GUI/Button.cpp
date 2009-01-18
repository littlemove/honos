#include "DXUT.h"
#include "Button.h"
#include <memory>

using namespace ui;

Button::Button(IDirect3DDevice9* pD3Ddevice,const WCHAR* wcpID ,int iXpos, int iYpos, const WCHAR* wcpMainTextureFile, const WCHAR* wcpPressedTextureFile, const WCHAR* wcpText) : UIComponent(wcpID,iXpos,iYpos){
	HRESULT hr;	
	
	std::auto_ptr<Bitmap> autopMainBitmap(new Bitmap(pD3Ddevice, wcpMainTextureFile));
	std::auto_ptr<Bitmap> autopPressedBitmap(new Bitmap(pD3Ddevice, wcpPressedTextureFile));
	std::auto_ptr<ui::Text> autopText(new ui::Text(pD3Ddevice,12,1,false,L"Arial"));

	m_pMainBitmap = autopMainBitmap.release();
	m_pPressedBitmap = autopPressedBitmap.release();
	m_pText = autopText.release();

	setHeight(m_pMainBitmap->getHeight());
	setWidth(m_pMainBitmap->getWidth());
	
	setXPosition(iXpos);
	setYPosition(iYpos);
	m_wsText = wcpText;	
	m_bIsPressed = false;
}

Button::Button(IDirect3DDevice9* pD3Ddevice,const WCHAR* wcpID ,int iXpos, int iYpos, const WCHAR* wcpMainTextureFile, const WCHAR* wcpPressedTextureFile, const WCHAR* wcpText, const WCHAR* pwcFontName, int iFontSize) : UIComponent(wcpID,iXpos,iYpos){
	HRESULT hr;	
	
	std::auto_ptr<Bitmap> autopMainBitmap(new Bitmap(pD3Ddevice, wcpMainTextureFile));
	std::auto_ptr<Bitmap> autopPressedBitmap(new Bitmap(pD3Ddevice, wcpPressedTextureFile));
	std::auto_ptr<ui::Text> autopText(new ui::Text(pD3Ddevice,iFontSize,1,false,pwcFontName));

	m_pMainBitmap = autopMainBitmap.release();
	m_pPressedBitmap = autopPressedBitmap.release();
	m_pText = autopText.release();

	setHeight(m_pMainBitmap->getHeight());
	setWidth(m_pMainBitmap->getWidth());
	
	setXPosition(iXpos);
	setYPosition(iYpos);
	m_wsText = wcpText;	
	m_bIsPressed = false;
}

void Button::draw(){	

	if(m_bIsPressed) m_pPressedBitmap->drawBitmapHere(getXPosition(), getYPosition());
	else m_pMainBitmap->drawBitmapHere(getXPosition(), getYPosition());
	WCHAR* pwcTemp = new WCHAR[m_wsText.length() + 1];
	wcscpy(pwcTemp, m_wsText.c_str());
	m_pText->drawTextHere(getXPosition(), getYPosition(), getHeight(), getWidth(), pwcTemp, DT_CENTER | DT_VCENTER );
	delete pwcTemp;
}

void Button::setPressed(bool bPressed){
	m_bIsPressed = bPressed;
}

EVENT_ID Button::OnMouseAction(UIState* pUIState){

	EVENT_ID evReturn = E_NO_EVENT;	

	if((pUIState->pwcHot == getID() ) && (pUIState->pwcActive == NULL) && (pUIState->evMouse == E_BUTTON_DOWN) ){
		m_bIsPressed = true;
		pUIState->pwcActive = getID();
	}
	else if((pUIState->pwcHot == getID()) && (pUIState->pwcActive == getID()) && (pUIState->evMouse == E_BUTTON_UP)){
		OutputDebugStringW(L"Button Click \n");
		m_bIsPressed = false;
		pUIState->pwcActive = NULL;
		evReturn = E_BUTTON_CLICK;
	}
	else if((pUIState->pwcHot != getID()) && (pUIState->pwcActive == getID()) && (pUIState->evMouse == E_BUTTON_UP)){
		m_bIsPressed = false;
		pUIState->pwcActive = NULL;
	}		

	return evReturn;	
}

Button::~Button(void){
	delete m_pMainBitmap;
	delete m_pPressedBitmap;
	delete m_pText;
}
