#ifndef _DIPLOMACY_H_
#define _DIPLOMACY_H_

#include <vector>
#include "ForeignCountry.h"

namespace core{

	struct DiplomacyState{
		double dOpinion;

		ForeignCountryState englandState;
		ForeignCountryState franceState;
		ForeignCountryState usaState;
	};
	
	/**
	* Está clase representa el módulo de diplomacia.
	*/
	class Diplomacy{

	public:
		/**
		* Constructor.
		*/
		Diplomacy();
		
		/**
		* Añade un país con el que tener relaciones diplomáticas.
		* @param pForeignCountry puntero al país a añadir.
		*/
		void addForeignCountry(ForeignCountry* pForeignCountry);
		
		/**
		* Calcula la opinión actual de los paises con los que mantienes relaciones diplomáticas.
		*/
		void calculateOpinion(double dProductionState, double dSocialServicesState, double dPopulationState);
		
		ForeignCountry* accesForeignCountry(foreignCountryID ID);
		
		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update();
		
		/**
		* Devuelve el estado de la clase.
		* @return DiplomacyState.
		*/
		DiplomacyState getState() const;
		
		std::wstring toString() const;
		
		/**
		* Destructor
		*/
		~Diplomacy();

	private:
		DiplomacyState m_state;
		double m_dOpinion;
		std::vector<ForeignCountry*> m_countryList;

		void saveState();
	};
}
#endif