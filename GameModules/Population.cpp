#include "Population.h"
#include "ConfigLoader.h"
#include <exception>

using namespace core;

Population::Population(int iSize){
	m_iSize = iSize;		
	m_dHappiness = 0.5;

	ConfigLoader cl("resources/config/config.xml");
	cl.populationLoader(this);
	update();	
}

void Population::addPopulationGroup(PopulationGroup* pPopulationGroup){
	m_populationGroupList.push_back(pPopulationGroup);	
}

void Population::setConsumption(productID ID, double dPriceVariation, double dPPS) {
	std::vector<PopulationGroup*>::iterator iter;
	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){
		(*iter)->calculateConsumption(dPriceVariation,ID, dPPS);
	}
}

void Population::setSocialServiceQuality(socialServiceID ID,double dQuality){
	std::vector<PopulationGroup*>::iterator iter;
	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){
		(*iter)->setSocialServiceQuality(ID,dQuality);
	}
}

int Population::getSize() const{
	return m_iSize;
}

void Population::setProperty(std::wstring wsName, double dValue){
	int iPos = wsName.find('_');
	std::wstring wsTarget = wsName.substr(0,iPos);
	std::wstring wsParam = wsName.substr(iPos+1);
	if(wsTarget == L"conservatives") m_populationGroupList.at(CONSERVATIVES)->setProperty(wsParam,dValue);
	else if(wsTarget == L"ultrademocrats") m_populationGroupList.at(ULTRADEMOCRATS)->setProperty(wsParam,dValue);
	else if(wsTarget == L"aislanders") m_populationGroupList.at(AISLANDERS)->setProperty(wsParam,dValue);
	else if(wsTarget == L"greens") m_populationGroupList.at(GREENS)->setProperty(wsParam,dValue);

	else outputDbgString(wsTarget+L" not found");
}
	


void Population::update(){	
	std::vector<PopulationGroup*>::const_iterator iter;	
	m_dFoodConsumption = 0;
	m_dEnergyConsumption = 0;
	m_dManufacturedConsumption = 0;
	m_dHappiness = 0;	

	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){

		(*iter)->update();
		m_dHappiness += (*iter)->getState().dLastTurnHappiness;
	}

	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){
		PopulationGroupState pgState = (*iter)->getState();
		m_dFoodConsumption += pgState.dFoodConsumption * pgState.dSize;// / 5.0;
		m_dEnergyConsumption += pgState.dEnergyConsumption * pgState.dSize;// / 5.0;
		m_dManufacturedConsumption += pgState.dManufacturedConsumption * pgState.dSize;// / 5.0;
	}

	m_dHappiness /= m_populationGroupList.size();
	saveState();
}

std::wstring Population::toString() const{
	std::wstring wst;
	std::vector<PopulationGroup*>::const_iterator iter;
	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){
		wst += (*iter)->toString();
	}	
	return wst;
}

PopulationState Population::getState() const{
	return m_populationState;
}

void Population::saveState(){
	m_populationState.dHappiness = m_dHappiness;
	m_populationState.dSize = m_iSize;
	m_populationState.dEnergyConsumption = m_dEnergyConsumption;
	m_populationState.dFoodConsumption = m_dFoodConsumption;
	m_populationState.dManufacturedConsumption = m_dManufacturedConsumption;

	m_populationState.aislandersState = m_populationGroupList.at(AISLANDERS)->getState();
	m_populationState.conservativesState = m_populationGroupList.at(CONSERVATIVES)->getState();
	m_populationState.ultrademocratsState = m_populationGroupList.at(ULTRADEMOCRATS)->getState();
	m_populationState.greensState = m_populationGroupList.at(GREENS)->getState();
	m_populationState.merchantsState = m_populationGroupList.at(MERCHANTS)->getState();
	/*m_populationState.dLastTurnHappiness = m_dLastTurnHappiness;	
	m_populationState.dSize = m_dSize;
	m_populationState.dConsumptionPower = m_dConsumptionPower;*/
}

Population::~Population(void){
	std::vector<PopulationGroup*>::iterator iter;
	for(iter = m_populationGroupList.begin(); iter != m_populationGroupList.end(); ++iter){
		delete (*iter);
	}
}


