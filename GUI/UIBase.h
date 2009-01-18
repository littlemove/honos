#ifndef _UI_BASE_H_
#define _UI_BASE_H_

namespace ui{

	typedef D3DCOLOR fontColor;

	static fontColor WHITE = D3DCOLOR_XRGB( 255, 255, 255 );
	static fontColor GREEN = D3DCOLOR_XRGB( 0, 255, 0 );
	static fontColor RED = D3DCOLOR_XRGB( 255, 0, 0 );

	/**
	* Este fichero proporciona una serie de macros para ayudar en la depuración con componentes de DirectX.
	*/

#if defined(DEBUG) || defined(_DEBUG)
#ifndef V_RET
#define V_RET(x) { hr = (x); if( FAILED(hr) ) throw ui::DXException(hr); }
#endif
#endif

#ifndef V_RET
#define V_RET(x)			{hr = x; if( FAILED(hr) ) { return; } }
#endif
}
#endif