#include "ForeignCountry.h"
#include <sstream>

using namespace core;

ForeignCountry::ForeignCountry(const wchar_t* pwcName, double dProductionImportance, double dSocialServicesImportance, double dPopulationImportance){
	m_wsName = pwcName;
	m_dProductionImportance = boundaryCheck(0,1,dProductionImportance);
	m_dSocialServicesImportance = boundaryCheck(0,1,dSocialServicesImportance);
	m_dPopulationImportance =  boundaryCheck(0,1,dPopulationImportance);

	if((m_dPopulationImportance + m_dSocialServicesImportance + m_dProductionImportance) > 1){
		m_dProductionImportance = 0.33;
		m_dSocialServicesImportance = 0.33;
		m_dPopulationImportance =  0.33;
		outputDbgString(L"Invalid importance values");
	}
	m_dOpinion = 0;	

	saveState();
}

void ForeignCountry::addTreaty(core::PoliticalActivity *pPA){
	m_treatyList.push_back(pPA);
	m_pCurrentTreatyIter = m_treatyList.begin();
}

void ForeignCountry::update(){
	saveState();
}

double ForeignCountry::calculateOpinion(double dProductionState, double dSocialServicesState, double dPopulationState){
	m_dOpinion = (dProductionState * m_dProductionImportance) + (dSocialServicesState * m_dSocialServicesImportance) + (dPopulationState * m_dPopulationImportance);
	return m_dOpinion;
}

PoliticalActivity* ForeignCountry::getCurrentTreaty(){
	if(!m_treatyList.empty())return (*m_pCurrentTreatyIter);
	else return NULL;
}

void ForeignCountry::next(){
	m_pCurrentTreatyIter++;
	if(m_pCurrentTreatyIter == m_treatyList.end()){
		m_pCurrentTreatyIter = m_treatyList.begin();
	}
}

ForeignCountryState ForeignCountry::getState() const{
	return m_state;
}

std::wstring ForeignCountry::toString() const{
	std::wstringstream wss;
	wss << m_wsName << std::endl;
	wss << L"Opinion: " << m_dOpinion << std::endl;
	wss << L"-------------" << std::endl;
	return wss.str();
}

void ForeignCountry::saveState(){
	m_state.dOpinon = m_dOpinion;
}

ForeignCountry::~ForeignCountry(){
	std::vector<PoliticalActivity*>::iterator iter;
	for(iter = m_treatyList.begin(); iter != m_treatyList.end(); ++iter){
		delete (*iter);
	}
}
