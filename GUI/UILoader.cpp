#include "DXUT.h"
#include "UILoader.h"

#include <sstream>

using namespace ui;

UILoader::UILoader(UIManager* pUIManager,IDirect3DDevice9* pd3dDevice){
	m_pUIManger = pUIManager;
	m_pd3dDevice = pd3dDevice;
}

void UILoader::addUIComponent(std::wstring wsType, std::wstring wsID, int iXpos, int iYpos, int iZpos,int iHeight, int iWidth, std::wstring wsTexture1, std::wstring wsTexture2, std::wstring wsText){
	try{
		if(wsType == L"button"){
			addButton(wsID,iXpos,iYpos,iZpos,wsTexture1,wsTexture2,wsText);
		}
		else if(wsType == L"textArea"){
			addTextArea(wsID,iXpos,iYpos,iZpos,iHeight,iWidth,wsTexture1,wsText);
		}
		else if(wsType == L"slider"){
			addSlider(wsID,iXpos,iYpos,iZpos,wsTexture1,wsTexture2);
		}
		else if(wsType == L"image"){
			addImage(wsID,iXpos,iYpos,iZpos,iHeight,iWidth,wsTexture1);
		}
	}
	catch(ui::DXException& dxe){
		OutputDebugStringW(dxe.what());
	}
}

void UILoader::loadFromXML(std::string sFile){
	
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();	
	
	if (bLoadOk){
		std::stringstream ss;
		ss << sFile.c_str() << "\n";
		OutputDebugStringA(ss.str().c_str());
		processXMLNode( &document ); 
	}
	else{
		OutputDebugStringA("Failed to load file");
	}
	
}

void UILoader::processXMLNode( TiXmlNode* pParent ){
	if ( !pParent ) return;
	std::stringstream ss;
	TiXmlNode* pChild;
	TiXmlText* pText;
	int iType = pParent->Type();	
	int iNum;

	switch (iType){
	case TiXmlNode::DOCUMENT:
		OutputDebugStringA( "Document" );
		break;

	case TiXmlNode::ELEMENT:		
		ss << "Element [" << pParent->Value()<<"]";
		OutputDebugStringA(ss.str().c_str());
		iNum = processXMLAtribute(pParent->ToElement());
		switch(iNum){
			case 0:  OutputDebugStringA( " (No attributes)"); break;
			case 1:  OutputDebugStringA( "attribute"); break;
			default:
				{
					ss.clear();
					ss <<  iNum << " attributes";
					OutputDebugStringA(ss.str().c_str()); break;
				}
		}
		break;

	case TiXmlNode::COMMENT:
		ss.clear();
		ss << "Comment: ["<<pParent->Value()<<"]";
		OutputDebugStringA(ss.str().c_str());
		break;

	case TiXmlNode::UNKNOWN:
		OutputDebugStringA( "Unknown" );
		break;

	case TiXmlNode::TEXT:
		pText = pParent->ToText();
		ss.clear();
		ss <<  "Text: ["<<pText->Value()<<"]"; 
		OutputDebugStringA(ss.str().c_str());
		break;

	case TiXmlNode::DECLARATION:
		OutputDebugStringA( "Declaration" );
		break;
	default:
		break;
	}
	OutputDebugStringA( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
		processXMLNode(pChild);
	}
}


int UILoader::processXMLAtribute(TiXmlElement* pElement){
	if (!pElement) return 0;

	std::wstring wsType = L"";
	std::wstring wsID = L"";
	int iX = -1;
	int iY = -1;
	int iZ = -1;
	int iHeigth = -1;
	int iWidth = -1;
	std::wstring wsTexture1 = L"";
	std::wstring wsTexture2 = L"";
	std::wstring wsText = L"";
	

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int iVal;
	double dVal;
	
	OutputDebugStringA("\n");
	while (pAttrib){
		std::stringstream ss;
		ss << pAttrib->Name() << " value = "<<pAttrib->Value();
		OutputDebugStringA(ss.str().c_str());

		std::wstringstream wss;	
		std::string sAttribName(pAttrib->Name());
		if(sAttribName == "type"){
			wss.clear();
			wss << pAttrib->Value();
			wsType = wss.str();
		}
		else if(sAttribName == "id"){
			wss.clear();
			wss << pAttrib->Value();
			wsID = wss.str();
		}
		else if(sAttribName == "x"){
			pAttrib->QueryIntValue(&iX);			
		}
		else if(sAttribName == "y"){
			pAttrib->QueryIntValue(&iY);			
		}
		else if(sAttribName == "z"){
			pAttrib->QueryIntValue(&iZ);			
		}
		else if(sAttribName == "h"){
			pAttrib->QueryIntValue(&iHeigth);			
		}
		else if(sAttribName == "w"){
			pAttrib->QueryIntValue(&iWidth);			
		}
		else if(sAttribName == "texture1"){
			wss.clear();
			wss << pAttrib->Value();
			wsTexture1 = wss.str();
		}
		else if(sAttribName == "texture2"){
			wss.clear();
			wss << pAttrib->Value();
			wsTexture2 = wss.str();
		}
		else if(sAttribName == "text"){
			wss.clear();
			wss << pAttrib->Value();
			wsText = wss.str();
		}

		if (pAttrib->QueryIntValue(&iVal)==TIXML_SUCCESS){
			ss.clear();
			ss <<  "int="<< iVal;
			OutputDebugStringA(ss.str().c_str());
		}
		if (pAttrib->QueryDoubleValue(&dVal)==TIXML_SUCCESS){
			ss.clear();
			ss <<  "d="<< dVal;
			OutputDebugStringA( ss.str().c_str());
		}
		OutputDebugStringA( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	addUIComponent(wsType, wsID, iX, iY, iZ, iHeigth, iWidth, wsTexture1, wsTexture2, wsText);
	return i;
}


void UILoader::addButton(std::wstring wsID, int iXpos, int iYpos, int iZpos, std::wstring wsMainTexture, std::wstring wsPressedTexture, std::wstring wsText) {
	try{
		Button* pButton = new Button(m_pd3dDevice,wsID.c_str(),iXpos,iYpos,wsMainTexture.c_str(),wsPressedTexture.c_str(),wsText.c_str());
		m_pUIManger->addUIComponent(pButton,iZpos);
	}catch(ui::DXException& dxe){
		dxe.addMoreInfo(L"ID:"+wsID);
		throw dxe;
	}
}

void UILoader::addImage(std::wstring wsID, int iXpos, int iYpos, int iZpos,int iHeight, int iWidth, std::wstring wsMainTexture) {
	try{
		Image* pImage;
		if(iHeight == -1){
		pImage = new Image(m_pd3dDevice,wsID.c_str(),iXpos,iYpos,wsMainTexture.c_str()); 
		}
		else{
			pImage = new Image(m_pd3dDevice,wsID.c_str(),iXpos, iYpos, iHeight,iWidth,L"");
		}
		m_pUIManger->addUIComponent(pImage,iZpos);
	}catch(ui::DXException& dxe){
		dxe.addMoreInfo(L"ID:"+wsID);
		throw dxe;
	}
}

void UILoader::addTextArea(std::wstring wsID, int iXpos, int iYpos, int iZpos,int iHeight, int iWidth, std::wstring wsTexture, std::wstring wsText) {
	try{
		TextArea* pTextArea = new TextArea(m_pd3dDevice,wsID.c_str(),iXpos, iYpos,iHeight,iWidth,L"Arial",16,3,DT_LEFT | DT_WORDBREAK,wsText.c_str());
		m_pUIManger->addUIComponent(pTextArea,iZpos);
	}catch(ui::DXException& dxe){
		dxe.addMoreInfo(L"ID:"+wsID);
		throw dxe;
	}
}

void UILoader::addSlider(std::wstring wsID, int iXpos, int iYpos, int iZpos, std::wstring wsImageTexture, std::wstring wsButtonTexture) {
	try{
		Slider* pSlider = new Slider(m_pd3dDevice,wsID.c_str(),false,wsImageTexture.c_str(),wsButtonTexture.c_str(),iXpos,iYpos);
		m_pUIManger->addUIComponent(pSlider,iZpos);
	}catch(ui::DXException& dxe){
		dxe.addMoreInfo(L"ID:"+wsID);
		throw dxe;
	}
}

UILoader::~UILoader(){
}
