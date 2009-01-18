#ifndef _POLITICAL_ACTIVITY_H_
#define _POLITICAL_ACTIVITY_H_

#include <string>
#include "Base.h"
#include "Requeriments.h"
#include "Effects.h"

namespace core{
	/**
	* Esta clase modela una actividad política ya sea un tratado o una política local.
	*/
	class PoliticalActivity{

	public:
		/**
		* Constructor.
		* @param wsName nombre de la política.
		* @param wsDescription descripción de la política.
		*/
		PoliticalActivity(std::wstring wsName, std::wstring wsDescription);
		
		/**
		* Destructor.
		* @param wsName nombre de la política.
		* @param wsDescription descripción de la política.
		* @param dMoney coste de la política por turno.
		*/
		PoliticalActivity(std::wstring wsName, std::wstring wsDescription, double dMoney);
		
		/**
		* Añadir requerimiento.
		* @param wsName parámetro al que afecta el requerimiento.
		* @param dBottom límite inferior.
		* @param dTop límite superior.
		*/
		void addRequeriment(std::wstring wsName, double dBottom, double dTop);
		
		/**
		* Añadir efecto.
		* @param wsName parámetro al que afecta el efecto.
		* @param dValue efecto por turno.		
		*/
		void addEffect(std::wstring wsName, double dValue);		

		std::wstring getName() const;

		double getMoney() const;

		std::wstring getDescription() const;
		
		/**
		* Indica si una política está activa, es decir, si se cumplen los requerimientos.
		*/
		bool isActive() const;
		
		/**
		* Indica si una política está firmada, es decir, si actualmente se está aplicando.
		*/
		bool isSigned() const;

		void setActive(bool bParam);

		void setSigned(bool bParam);

		std::map<std::wstring, ReqValue> getRequeriments();

		std::map<std::wstring, double> getEffects();		

		/**
		* Destructor.
		*/
		~PoliticalActivity();

	private:
		std::wstring m_wsName;
		std::wstring m_wsDescription;
		bool m_bActive;
		bool m_bSigned;
		double m_dMoney;

		Requeriments m_requeriments;
		Effects m_effects;
	};
}
#endif
