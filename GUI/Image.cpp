#include "DXUT.h"
#include "Image.h"

#include <memory>

using namespace ui;

Image::Image(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, int iHeight, int iWidth, const WCHAR* pwcBitmapFile) : UIComponent(wcpID,iXpos,iYpos,iHeight,iWidth){
	m_pBitmap = NULL;		
	std::wstring temp = pwcBitmapFile;

	if(temp != L""){
	std::auto_ptr<Bitmap> autopBitmap(new Bitmap(pD3Ddevice, iXpos, iYpos, iWidth, iHeight, pwcBitmapFile));
	m_pBitmap = autopBitmap.release();	
	}

	setXPosition(iXpos);
	setYPosition(iYpos);
	setHeight(iHeight);
	setWidth(iWidth);

}

Image::Image(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, const WCHAR* pwcBitmapFile) : UIComponent(wcpID,iXpos,iYpos){
	m_pBitmap = NULL;				

	std::auto_ptr<Bitmap> autopBitmap(new Bitmap(pD3Ddevice,pwcBitmapFile,iXpos,iYpos));
	m_pBitmap = autopBitmap.release();	

	setXPosition(iXpos);
	setYPosition(iYpos);
	setHeight(m_pBitmap->getHeight());
	setWidth(m_pBitmap->getWidth());
}

void Image::draw(){
	if(m_pBitmap != NULL) m_pBitmap->draw();
}

EVENT_ID Image::OnMouseAction(UIState* pUIState){

	EVENT_ID evReturn = E_NO_EVENT;	

	if((pUIState->pwcHot == getID() ) && (pUIState->pwcActive == NULL) && (pUIState->evMouse == E_BUTTON_DOWN) ){
		//m_bIsPressed = true;
		pUIState->pwcActive = getID();
	}
	else if((pUIState->pwcHot == getID()) && (pUIState->pwcActive == getID()) && (pUIState->evMouse == E_BUTTON_UP)){
		OutputDebugStringW(L"Image Click \n");
		//m_bIsPressed = false;
		pUIState->pwcActive = NULL;
		evReturn = E_BUTTON_CLICK;
	}
	else if((pUIState->pwcHot != getID()) && (pUIState->pwcActive == getID()) && (pUIState->evMouse == E_BUTTON_UP)){
		//m_bIsPressed = false;
		pUIState->pwcActive = NULL;
	}		

	return evReturn;	
}

Image::~Image(void){
	delete m_pBitmap;
}
