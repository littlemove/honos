#ifndef _H_POPULATION_GROUP_H_
#define _H_POPULATION_GROUP_H_

#include <sstream>
#include <string>
#include "Base.h"

namespace core{

	struct PopulationGroupState{	
		double dFoodConsumption;
		double dEnergyConsumption;
		double dManufacturedConsumption;	
		double dLastTurnHappiness;
		double dSize;
		double dConsumptionPower;
	};

	/**
	* Esta clase modela cada uno de los grupos poblacionales que componen os habitantes del país del jugador.
	*/
	class PopulationGroup{
	public:
		PopulationGroup(const wchar_t* pwcName,
			double dSize,
			double dPurchasingPower,
			double dHealthCareOpinion,
			double dEducationOpinion,
			double dJusticeOpinion,
			double dFoodStuffOpinion,
			double dEnergyConsumptionOpinion,
			double dManufacturedProductOpinion);

		/**
		* Constructor.
		* @param pwcName nombre del grupo.
		* @param dSize porcentaje de población que representa el grupo.
		* @param dConsumptionPower porcentaje de la riqueza que almacena.
		*/
		PopulationGroup(wchar_t* pwcName, double dSize, double dConsumptionPower);
		
		/**
		* Calcula la felicidad alcanzada en el último turno.
		* @return double con la felicidad del turno.
		*/
		double calculateTurnHappiness();

		/**
		* Calcula el consumo.
		* @param double indicando la variación de precio.
		* @param productID
		* @return double entre 0 y 1 indicando la capacidad de consumo en ese turno.
		*/
		void calculateConsumption(double dPriceChange, productID ID, double dPPS); 
		

		void setSocialServiceQuality(socialServiceID ID,double dQuality);

		std::wstring toString() const;
		
		/**
		* Asigna un valor a una propiedad del objeto especificada (si existe).
		* @param wsName nombre de la propiedad.
		* @param dValue valor a asignar.
		*/
		void setProperty(std::wstring wsName, double dValue);

		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update();
		
		/**
		* Devuelve el estado de la clase.
		* @return PopulationGroupState.
		*/
		PopulationGroupState getState() const;
		
		/**
		* Destructor.
		*/
		~PopulationGroup();

	private:
		PopulationGroupState m_populationGroupState;
		double m_dHappinessBonus;

		std::wstring m_wsName;
		std::wstring m_wsDescription;

		double m_dTotalHappiness;
		double m_dLastTurnHappiness;

		double m_dHealthQuality;
		double m_dEducationQuality;
		double m_dJusticeQuality;

		///  Valores entre 0 y 1 que indica cuan satisfechas están las diferentes necesidades de consumo. 0-> completamente insatisfechas, 1-> completamente satisfechas.
		double m_dFoodConsumption;
		double m_dEnergyConsumption;
		double m_dManufacturedConsumption;

		double m_dSize;
		double m_dConsumptionPower;

		double m_dHealthCareOpinion;
		double m_dEducationOpinion;
		double m_dJusticeOpinion;

		double m_dFoodStuffOpinion;
		double m_dEnergyConsumptionOpinion;
		double m_dManufacturedProductOpinion;

		void saveState();
		double priceRiseReaction(double dPriceVariation);
		double priceLowerReaction(double dPriceVariation);

		void happinessBonus(double dValue);
	};
}
#endif