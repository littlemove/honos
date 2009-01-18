#include "DXUT.h"
#include "Bitmap.h"
#include "DXException.h"

using namespace ui;

Bitmap::Bitmap(IDirect3DDevice9* pD3Ddevice, const WCHAR* wcpFilename, int iXpos, int iYpos){	
	HRESULT hr = E_FAIL;	

	m_pD3Ddevice = pD3Ddevice;
	m_wsFileName = wcpFilename;	

	m_pTexture = NULL;
	m_pVertexBuffer = NULL;
	m_pVertexDeclarations = NULL;
	
	////////// Inicialización (OnCreateDevice) //////////
	//Textura (color de transparencia 0xffff00ff = Magenta)
	try {

	D3DXIMAGE_INFO imageInfo;
	V_RET(D3DXCreateTextureFromFileEx(m_pD3Ddevice, m_wsFileName.c_str(), 0, 0, 0,0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xffff00ff, &imageInfo, NULL,&m_pTexture));			
	//int iWidth = imageInfo.Width;
	//int iHeight = imageInfo.Height;		
	m_iWidth = imageInfo.Width;
	m_iHeight = imageInfo.Height;	
	m_iXpos = iXpos;
	m_iYpos = iYpos;

	//Vértices
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, sizeof(D3DXVECTOR3),  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},		
		D3DDECL_END()
	};

	V_RET( m_pD3Ddevice->CreateVertexDeclaration(VertexPosElements, &m_pVertexDeclarations ) );	
	V_RET( m_pD3Ddevice->CreateVertexBuffer(4 * sizeof(SVertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVertexBuffer, 0) );	

	SVertex* v = 0;
	V_RET( m_pVertexBuffer->Lock(0, 0, (void**)&v, 0) );	
	
	v[0] = SVertex(0.0f,0.0f,0.0f,0,0);
	v[1] = SVertex(m_iWidth, 0.0f,0.0f,1,0);	
	v[2] = SVertex( 0.0f, m_iHeight,0.0f,0,1);	
	v[3] = SVertex( m_iWidth, m_iHeight,0.0f,1,1);	

	V_RET( m_pVertexBuffer->Unlock(), std::exception() );
	}

	catch(...){	
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(m_pVertexBuffer);
		SAFE_RELEASE(m_pVertexDeclarations);	
		throw DXException(hr);
	}
}

Bitmap::Bitmap(IDirect3DDevice9* pD3Ddevice,int iXpos, int iYpos, int iWidth, int iHeight, const WCHAR* wcpFilename){
	HRESULT hr = E_FAIL;	

	m_pD3Ddevice = pD3Ddevice;
	m_wsFileName = wcpFilename;	

	m_pTexture = NULL;
	m_pVertexBuffer = NULL;
	m_pVertexDeclarations = NULL;
	
	////////// Inicialización (OnCreateDevice) //////////
	//Textura
	try {

	D3DXIMAGE_INFO imageInfo;
	V_RET(D3DXCreateTextureFromFileEx(m_pD3Ddevice, m_wsFileName.c_str(), 0, 0, 0,0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, &imageInfo, NULL,&m_pTexture));			
	
	//m_iWidth = imageInfo.Width;
	//m_iHeight = imageInfo.Height;

	m_iWidth = iWidth;
	m_iHeight = iHeight;	

	//Vértices
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, sizeof(D3DXVECTOR3),  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},		
		D3DDECL_END()
	};

	V_RET( m_pD3Ddevice->CreateVertexDeclaration(VertexPosElements, &m_pVertexDeclarations ) );	
	V_RET( m_pD3Ddevice->CreateVertexBuffer(4 * sizeof(SVertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVertexBuffer, 0) );	

	SVertex* v = 0;
	V_RET( m_pVertexBuffer->Lock(0, 0, (void**)&v, 0) );	
	
	v[0] = SVertex(0.0f,0.0f,0.0f,0,0);
	v[1] = SVertex(m_iWidth, 0.0f,0.0f,1,0);	
	v[2] = SVertex( 0.0f, m_iHeight,0.0f,0,1);	
	v[3] = SVertex( m_iWidth, m_iHeight,0.0f,1,1);	

	V_RET( m_pVertexBuffer->Unlock(), std::exception() );

	m_iXpos = iXpos;
	m_iYpos = iYpos;
	}

	catch(...){	
		SAFE_RELEASE(m_pTexture);
		SAFE_RELEASE(m_pVertexBuffer);
		SAFE_RELEASE(m_pVertexDeclarations);	
		throw DXException(hr);
	}
}

void Bitmap::drawBitmapHere(int iXpos, int iYpos){
	HRESULT hr = E_FAIL;
	
		V_RET(m_pD3Ddevice->SetTexture(0, m_pTexture), std::exception());	
		D3DXMATRIX translationMatrix;
		D3DXMatrixTranslation(&translationMatrix,iXpos,iYpos,0);
		V_RET(m_pD3Ddevice->SetTransform(D3DTS_WORLD, &translationMatrix), std::exception());
		V_RET( m_pD3Ddevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(SVertex) ), std::exception() );
		V_RET( m_pD3Ddevice->SetVertexDeclaration( m_pVertexDeclarations ), std::exception() );
		V_RET( m_pD3Ddevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ), std::exception() );	
}

void Bitmap::draw(void){
	HRESULT hr = E_FAIL;	

	V_RET(m_pD3Ddevice->SetTexture(0, m_pTexture), std::exception());	
		D3DXMATRIX translationMatrix;
		D3DXMatrixTranslation(&translationMatrix,m_iXpos,m_iYpos,0);
		V_RET(m_pD3Ddevice->SetTransform(D3DTS_WORLD, &translationMatrix), std::exception());
		V_RET( m_pD3Ddevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(SVertex) ), std::exception() );
		V_RET( m_pD3Ddevice->SetVertexDeclaration( m_pVertexDeclarations ), std::exception() );
		V_RET( m_pD3Ddevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ), std::exception() );	
}

int Bitmap::getXPosition(void) const{
	return m_iXpos;
}

int Bitmap::getYPosition(void) const{
	return m_iYpos;
}

int Bitmap::getWidth() const{
	return m_iWidth;
}

int Bitmap::getHeight() const{
	return m_iHeight;
}

void Bitmap::setXPosition(int iXpos){
	m_iXpos = iXpos;
}

void Bitmap::setYPosition(int iYpos){
	m_iYpos = iYpos;
}

Bitmap::~Bitmap(void){

	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexDeclarations);	
	
}
