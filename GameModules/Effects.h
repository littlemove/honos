#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include <vector>
#include <map>
#include "Base.h"

namespace core{	

	/**
	* Esta clase almacena los datos necesarios para modelar efectos de una relación diplomática o polítca.
	*/
	class Effects{

	public:
		Effects();
		
		void addEffect(std::wstring wsName, double dValue);		

		std::map<std::wstring, double> getEffects();

		~Effects();

	private:
		std::map<std::wstring, double> m_info;					
	};
}
#endif
