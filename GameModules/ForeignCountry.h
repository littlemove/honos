#ifndef _FOREIGN_COUNTRY_H_
#define _FOREIGN_COUNTRY_H_

#include <string>
#include <vector>
#include "Base.h"
#include "PoliticalActivity.h"

namespace core{

	struct ForeignCountryState{
		double dOpinon;
	};

	/**
	* Esta clase define un estado no manejado por el jugador.
	*/
	class ForeignCountry{

	public:
		ForeignCountry(const wchar_t* pwcName, double dProductionImportance, double dSocialServicesImportance, double dPopulationImportance);
		
		/**
		* Añade una actividad política pasada como parámetro.
		* @param pPA puntero a PoliticalActivity
		*/
		void addTreaty(PoliticalActivity* pPA);
		
		/**
		* Actualiza el estado del país.
		*/ 
		void update();
		
		/**
		* Calcula la opinión de la potencia extranjera respecto al estado del país del jugador.
		* @param dProductionState estado de la producción.
		* @param dSocialServicesState estado de los servicios sociales.
		* @param dPopulationState estado de la población.
		*/
		double calculateOpinion(double dProductionState, double dSocialServicesState, double dPopulationState);
		
		/**
		* Devuelve una lista con los tratados posibles para el país.
		* @return std::vector<PoliticalActivity*>
		*/
		std::vector<PoliticalActivity*> getPossibleTreatyList();
		
		/**
		* Devuelve una lista con los tratados activos para el país.
		* @return std::vector<PoliticalActivity*>
		*/
		std::vector<PoliticalActivity*> getActiveTreatyList();
		
		/**
		* Devuelve un puntero al tratado selecionado actualmente.
		* @return puntero a PoliticalActivity
		*/
		PoliticalActivity* getCurrentTreaty();
		
		/**
		* Avanza currentTreaty al siguiente tratado. Si no quedan más vuelve al inicio.
		*/
		void next();
		
		/**
		* Devuelve el estado de la clase.
		* @return ForeignCountryState.
		*/
		ForeignCountryState getState() const;

		std::wstring toString() const;
		
		/**
		* Destructor.
		*/
		~ForeignCountry();
		
		std::vector<PoliticalActivity*> m_treatyList;
	private:
		ForeignCountryState m_state;		
		std::wstring m_wsName;
		std::wstring m_wsDescription;
		
		double m_dOpinion;
		double m_dProductionImportance;
		double m_dPopulationImportance;
		double m_dSocialServicesImportance;

		std::vector<PoliticalActivity*>::iterator m_pCurrentTreatyIter;

		void saveState();
	};
}
#endif