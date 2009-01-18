#ifndef _REQUERIMENTS_H_
#define _REQUERIMENTS_H_

#include <vector>
#include <map>
#include "Base.h"

namespace core{

	struct ReqValue{		
		double dValue;
		double dInterval;
	};

	/**
	* Esta clase almacena los datos necesarios para modelar un requerimiento de una relación diplomática o polítca.
	*/
	class Requeriments{

	public:
		Requeriments();
		/**
		* Añade un requerimiento. Esto es un par formado por el parámetro al que afecta el requerimiento y una estructura ReqValue 
		* que construimos mediante los parámetros.
		* @param wsName nombre del parámetro al que afecta el requerimiento.
		* @param dValue valor que se necesita cumplir para satisfacer el requerimiento.
		* @param dInterval [0-1] tanto por 1 sobre dValue indicando el rango donde puede variar un requerimiento una vez cumplido.
		*/
		void addRequeriment(std::wstring wsName, double dValue, double dInterval);		
		
		/**
		* Devuelve una map requerimiento valor.		
		* @return std::map<std::wstring, ReqValue>.
		*/
		std::map<std::wstring, ReqValue> getRequeriments();
		
		/**
		* Destructor.
		*/
		~Requeriments();

	private:
		std::map<std::wstring, ReqValue> m_info;
		bool m_bFirstCut;			
	};
}
#endif