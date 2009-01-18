#ifndef _COUNTRY_STATE_H_	
#define _COUNTRY_STATE_H_

#include "Population.h"
#include "SocialServices.h"
#include "Production.h"
#include "Diplomacy.h"
#include "LocalPolicies.h"

#include <vector>
#include <map>

namespace core{
	
	/**
	* Esta clase almacena y controla el estado del país y es el nexo de comunicación entre lode distintos módulos que desarrollan la lógica de juego y el interfaz.
	*/
	class CountryState{

	public:
		/**
		* Cosntructor.
		*/
		CountryState(Production* pProduction, Population* pPopulation, SocialServices* pSocialServices, Diplomacy* pDiplomacy, LocalPolicies* pLocalPolicies);		

		/**
		* Devuelve el valor en el turno actual de cierto parámetro, si existe.
		* @param wsParam nombre del parámetro.
		* @return valor del parámetro.
		*/
		double getCurrentValue(std::wstring wsParam) const;			
		
		/**
		* Devuelve el valor en el turno actual.	
		* @return valor del turno.
		*/
		int getCurrentTurn() const;		
		
		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update();
		
		/**
		* Destructor.
		*/
		~CountryState();

		double getTotalMoney() const;

		double m_dTotalHappiness;

		double m_dTotalMoney;

	private:
		int m_iTurn;		

		std::map<std::wstring,double> m_countryStateInfo;
		Production* m_pProduction;
		Population* m_pPopulation;
		SocialServices* m_pSocialServices;
		Diplomacy* m_pDiplomacy;
		LocalPolicies*	m_pLocalPolicies;
		
		std::vector<ProductionState> m_productionStates;
		std::vector<SocialServicesState> m_socialServicesStates;
		std::vector<PopulationState> m_populationStates;	
		std::vector<DiplomacyState> m_diplomacyStates;

		void fillCountryStateInfo();
		void updatePoliticalActivities();
		void applyPoliticalActivities();

		void calculateHappiness();
		void calculateMoney();
	};
}
#endif