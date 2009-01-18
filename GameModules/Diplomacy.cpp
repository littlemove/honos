#include "Diplomacy.h"
#include "ConfigLoader.h"

using namespace core;

Diplomacy::Diplomacy(){
	ConfigLoader cl("resources/config/config.xml");
	cl.diplomacyLoader(this);
	cl.treatiesLoader();

	update();
}

void Diplomacy::addForeignCountry(ForeignCountry* pForeignCountry){
	m_countryList.push_back(pForeignCountry);
}

void Diplomacy::calculateOpinion(double dProductionState, double dSocialServicesState, double dPopulationState){
	m_dOpinion = 0;
	std::vector<ForeignCountry*>::iterator iter;
	for(iter = m_countryList.begin(); iter != m_countryList.end(); ++iter){
		m_dOpinion += (*iter)->calculateOpinion(dProductionState,dSocialServicesState,dPopulationState);
	}
	m_dOpinion /= m_countryList.size();
}

ForeignCountry* Diplomacy::accesForeignCountry(foreignCountryID ID){
	return m_countryList.at(ID);
}

void Diplomacy::update(){
	std::vector<ForeignCountry*>::iterator iter;
	for(iter = m_countryList.begin(); iter != m_countryList.end(); ++iter){
		(*iter)->update();
	}	
	saveState();
}

DiplomacyState Diplomacy::getState() const{
	return m_state;
}

void Diplomacy::saveState(){
	m_state.englandState = m_countryList.at(ENGLAND)->getState();
	m_state.franceState = m_countryList.at(FRANCE)->getState();
	m_state.usaState = m_countryList.at(USA)->getState();
}


std::wstring Diplomacy::toString() const{
	std::wstring wst;
	std::vector<ForeignCountry*>::const_iterator iter;
	for(iter = m_countryList.begin(); iter != m_countryList.end(); ++iter){
		wst += (*iter)->toString();
	}	
	return wst;
}

Diplomacy::~Diplomacy(){
	std::vector<ForeignCountry*>::iterator iter;
	for(iter = m_countryList.begin(); iter != m_countryList.end(); ++iter){
		delete (*iter);
	}	
}
