#ifndef _EVENTSIDS_H_
#define _EVENTSIDS_H_

namespace ui{
	/**
	* Este fichero proporciona una serie de identificadores de los eventos que los componentes de la libreria pueden lanzar.
	*/

	typedef int EVENT_ID;

	const int E_NO_EVENT = 0;

	const int E_BUTTON_CLICK = 10;
	const int E_BUTTON_DOWN = 11;
	const int E_BUTTON_UP = 12;

	const int E_AREA_ENTER = 21;
	const int E_AREA_OFF = 22;
	const int E_AREA_IN = 23;
	const int E_AREA_OUT = 24;

	const int E_HOT = 31;
	const int E_NOT_HOT = 32;
	const int E_ACTIVE = 33;
	const int E_NOT_ACTIVE = 34;
}
#endif