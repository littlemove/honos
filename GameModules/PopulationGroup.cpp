#include "PopulationGroup.h"
#include <cmath>


using namespace core;

PopulationGroup::PopulationGroup(const wchar_t* pwcName, double dSize, double dConsumptionPower, double dHealthCareOpinion, double dEducationOpinion, double dJusticeOpinion, double dFoodStuffOpinion, double dEnergyConsumptionOpinion, double dManufacturedProductOpinion){
	m_wsName = pwcName;
	m_dSize = dSize;
	m_dConsumptionPower = dConsumptionPower;
	m_dHealthCareOpinion = dHealthCareOpinion;
	m_dEducationOpinion =dEducationOpinion;
	m_dJusticeOpinion = dJusticeOpinion;
	m_dFoodStuffOpinion = dFoodStuffOpinion;
	m_dEnergyConsumptionOpinion = dEnergyConsumptionOpinion;
	m_dManufacturedProductOpinion = dManufacturedProductOpinion;

	m_dFoodConsumption = 1;
	m_dEnergyConsumption = 1;
	m_dManufacturedConsumption = 1;

	m_dHealthQuality = 0.5;
	m_dEducationQuality = 0.5;
	m_dJusticeQuality = 0.5;

	m_dLastTurnHappiness = 0;
	m_dHappinessBonus = 0;

	saveState();
}

PopulationGroup::PopulationGroup(wchar_t* pwcName, double dSize, double dConsumptionPower){
	m_wsName = pwcName;
	m_dSize = dSize;
	m_dConsumptionPower = dConsumptionPower;

	m_dFoodConsumption = 1;
	m_dEnergyConsumption = 1;
	m_dManufacturedConsumption = 1;
	m_dLastTurnHappiness = 0;

	saveState();
}

double PopulationGroup::calculateTurnHappiness(){

	double dConsuptionHappiness = (m_dFoodConsumption*m_dFoodStuffOpinion + m_dEnergyConsumption*m_dEnergyConsumptionOpinion + m_dManufacturedConsumption*m_dManufacturedProductOpinion) / 3;
	double dSocialServicesHappiness = (m_dHealthCareOpinion*m_dHealthQuality + m_dEducationOpinion*m_dEducationQuality + m_dJusticeOpinion*m_dJusticeQuality) / 3;
	m_dLastTurnHappiness = boundaryCheck(0.0,1.0, dConsuptionHappiness + dSocialServicesHappiness + m_dHappinessBonus);
	return m_dLastTurnHappiness;
}

void PopulationGroup::setSocialServiceQuality(socialServiceID ID, double dQuality){
	switch(ID){
		case HEALTHCARE:
			m_dHealthQuality = dQuality;
			break;
		case EDUCATION:
			m_dEducationQuality = dQuality;
			break;
		case JUSTICE:
			m_dJusticeQuality = dQuality;
			break;
	}
}


void PopulationGroup::calculateConsumption(double dPriceChange, productID ID,double dPPS){

	double dConsumption = 0;
	switch(ID){
		case FOOD:
			dConsumption = m_dFoodConsumption;
			break;
		case ENERGY:
			dConsumption = m_dEnergyConsumption;
			break;
		case MANUFACTURED:
			dConsumption = m_dManufacturedConsumption;
			break;
	}

	
if(dPriceChange >= 0) dConsumption = priceRiseReaction(dPriceChange) * dPPS;
		else dConsumption = priceLowerReaction(dPriceChange) * dPPS;

		switch(ID){
		case FOOD:
			m_dFoodConsumption = dConsumption;
			break;
		case ENERGY:
			m_dEnergyConsumption = dConsumption;
			break;
		case MANUFACTURED:
			m_dManufacturedConsumption = dConsumption;
			break;
		}		
}

double PopulationGroup::priceRiseReaction(double dPriceVariation){
	if(dPriceVariation > 1) dPriceVariation = 1;

	double dExp = log(1-m_dConsumptionPower) / log(0.5);	
	
	return 1-powl(dPriceVariation,dExp);
}
/// TODO: implementación real.
double PopulationGroup::priceLowerReaction(double dPriceVariation){
	//m_dConsumptionPower += 0.1;
	return 1.0;
}

void PopulationGroup::saveState(){
	m_populationGroupState.dEnergyConsumption = m_dEnergyConsumption;
	m_populationGroupState.dFoodConsumption = m_dFoodConsumption;
	m_populationGroupState.dManufacturedConsumption = m_dManufacturedConsumption;
	m_populationGroupState.dLastTurnHappiness = m_dLastTurnHappiness;	
	m_populationGroupState.dSize = m_dSize;
	m_populationGroupState.dConsumptionPower = m_dConsumptionPower;
}

PopulationGroupState PopulationGroup::getState() const{
	return m_populationGroupState;
}

void PopulationGroup::happinessBonus(double dValue){
	m_dHappinessBonus += dValue;
}

void PopulationGroup::setProperty(std::wstring wsName, double dValue){
	if(wsName == L"happiness") happinessBonus(dValue);
	else{
	outputDbgString(L"Property not found");
	}
}

void PopulationGroup::update(){
	calculateTurnHappiness();
	m_dHappinessBonus = 0;
	saveState();
}

std::wstring PopulationGroup::toString() const{
	std::wstringstream wss;
	wss << m_wsName << "\n";
	wss << "Last turn happiness: " << m_dLastTurnHappiness << "\n";
	wss << "Consumption power: " << m_dConsumptionPower << "\n";
	wss << "Food Consumption: " << m_dFoodConsumption << "\n";
	wss << std::endl;

	return wss.str();
}

PopulationGroup::~PopulationGroup(void){}
