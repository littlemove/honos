#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <string>
#include <exception>
#include "UIBase.h"

namespace ui{

struct SVertex
{
	SVertex() {}
	SVertex(float x, float y, float z, float tu, float tv):pos(x,y,z), u(tu), v(tv){}
	D3DXVECTOR3 pos;	
	float u;
	float v;	
};

/**
* Esta clase implementa la estructura más simple de la biblioteca gráfica, un bitmap. Encapsula funcionalidad mínima para poder pintar en pantalla un objeto 2D simple.
* Se trata de uno de los mayores puntos de cohesión de la biblioteca con el motor de render, y por lo tanto candidata a la reimplementación si este varia.
*/
class Bitmap{

public:	
	/**
	* Constructor de Bitmap. Construye un bitmap de tamaño, en pixels, igual al de la textura que recibe como parámetro.
	* @param pD3Ddevice puntero a un dispositivo D3D9.
	* @param pwcFilename puntero a una cadena de caracteres que representa la ubicación del archivo de textura.
	* @param iXpos posición de pintado X, en pixels.
	* @param iYpos posición de pintado Y, en pixels.
	*/
	Bitmap(IDirect3DDevice9* pD3Ddevice, const WCHAR* pcwFilename, int iXpos = 0, int iYpos = 0) throw(std::exception);
	
	/**
	* Constructor de Bitmap.
	* @param pD3Ddevice puntero a un dispositivo D3D9.
	* @param pwcFilename puntero a una cadena de caracteres que representa la ubicación del archivo de textura.
	* @param iXpos posición de pintado X, en pixels.
	* @param iYpos posición de pintado Y, en pixels.
	* @param iWidth ancho en pixels del bitmap.
	* @param iHeight alto en pixels del bitmap.
	*/
	Bitmap(IDirect3DDevice9* pD3Ddevice,int iXpos, int iYpos, int iWidth, int iHeight, const WCHAR* wcpFilename) throw(std::exception);

	void drawBitmapHere(int iXpos, int iYpos);

	/**
	* Dibuja el bitmap.
	*/
	void draw();

	/**
	* Devuelve el ancho del bitmap en pixels.
	* @return ancho del bitmap, en pixels.
	*/
	int getWidth() const;

	/**
	* Devuelve el largo del bitmap en pixels.
	* @return largo del bitmap, en pixels.
	*/
	int getHeight() const;

	/**
	* Devuelve la posición X del bitmap en pixels.
	* @return posición X del bitmap en pixels.
	*/
	int getXPosition() const;

	/**
	* Devuelve la posición Y del bitmap en pixels.
	* @return posición Y del bitmap en pixels.
	*/
	int getYPosition() const;

	/**
	* Modifica la posición X de pintado.
	* @param iXpos posición X, en pixels.
	*/
	void setXPosition(int iXpos);

	/**
	* Modifica la posición Y de pintado.
	* @param iYpos posición Y, en pixels.
	*/
	void setYPosition(int iYpos);

	/**
	* Destructor.
	*/
	~Bitmap(void);

private:	
	int m_iXpos;
	int m_iYpos;
	int m_iWidth;
	int m_iHeight;

	std::wstring m_wsFileName;
	SVertex m_vertex;
	IDirect3DDevice9* m_pD3Ddevice;
	IDirect3DTexture9* m_pTexture;
	IDirect3DVertexDeclaration9* m_pVertexDeclarations;
	IDirect3DVertexBuffer9* m_pVertexBuffer;

};
}
#endif