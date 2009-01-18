#include "DXUT.h"
#include "TextArea.h"

#include <memory>

using namespace ui;

TextArea::TextArea(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpID, int iXpos, int iYpos, int iHeight, int iWidth, const WCHAR* pwcFontName, int iFontSize,int iFontWeigth, DWORD wFormat, const WCHAR* pwcText, const WCHAR* pwcBackgroundFile, bool bStrechtBackground) : UIComponent(wcpID, iXpos, iYpos, iHeight, iWidth){
	m_pBitmap = NULL;
	m_pText = NULL;
	
	std::auto_ptr<Text> autopText(new Text(pD3Ddevice, iXpos, iYpos, iHeight, iWidth, iFontSize, iFontWeigth, false, wFormat, pwcFontName, pwcText));
	if(pwcBackgroundFile != NULL){
				
		if(!bStrechtBackground){
		std::auto_ptr<Bitmap> autopBitmap(new Bitmap(pD3Ddevice, pwcBackgroundFile, iXpos, iYpos));
			m_pBitmap = autopBitmap.release();	
		}
		else{
			std::auto_ptr<Bitmap> autopBitmap(new Bitmap(pD3Ddevice, iXpos, iYpos, iWidth, iHeight, pwcBackgroundFile));
			m_pBitmap = autopBitmap.release();	
		}		
	}

	m_pText = autopText.release();	
	
}

void TextArea::draw(void){
	if(m_pBitmap != NULL) m_pBitmap->draw();
	m_pText->draw();
}

bool TextArea::setProperty(std::wstring wsName, std::wstring wsValue){
	bool bResult = UIComponent::setProperty(wsName, wsValue);

	if(!bResult){
		if(wsName.compare(L"text") == 0){
			m_pText->setText(wsValue.c_str());
			bResult = true;
		}
		else if(wsName.compare(L"weight") == 0){
			m_pText->setFontWeight(convertToInt(wsValue.c_str()));
			bResult = true;
		}
		else if(wsName.compare(L"size") == 0){
			m_pText->setFontSize(convertToInt(wsValue.c_str()));
			bResult = true;
		}
		else if(wsName.compare(L"color") == 0){
			fontColor fc = WHITE;
			if(wsValue.compare(L"green") == 0) fc = GREEN;
			else if (wsValue.compare(L"red") == 0) fc = RED;

			m_pText->setFontColor(fc);
			bResult = true;
		}
	}

	return bResult;
}

TextArea::~TextArea(void){
	delete m_pText;
	delete m_pBitmap;
}
