#include "PoliticalActivity.h"

using namespace core;

PoliticalActivity::PoliticalActivity(std::wstring wsName, std::wstring wsDescription){
	m_wsName = wsName;
	m_wsDescription = wsDescription;
	m_bActive = false;
	m_bSigned = false;
	m_dMoney = 0;
}

PoliticalActivity::PoliticalActivity(std::wstring wsName, std::wstring wsDescription, double dMoney){
	m_wsName = wsName;
	m_wsDescription = wsDescription;
	m_bActive = false;
	m_bSigned = false;
	m_dMoney = dMoney;
}

void PoliticalActivity::addRequeriment(std::wstring wsName, double dValue, double dInterval){
	m_requeriments.addRequeriment(wsName, dValue, dInterval);
}

void PoliticalActivity::addEffect(std::wstring wsName, double dValue){
	m_effects.addEffect(wsName,dValue);
}

std::map<std::wstring, ReqValue> PoliticalActivity::getRequeriments(){
	return m_requeriments.getRequeriments();
}

std::map<std::wstring, double> PoliticalActivity::getEffects(){
	return m_effects.getEffects();
}

void PoliticalActivity::setActive(bool bParam){ m_bActive = bParam; }

void PoliticalActivity::setSigned(bool bParam){ m_bSigned = bParam; }

std::wstring PoliticalActivity::getName() const{ return m_wsName; }

std::wstring PoliticalActivity::getDescription() const { return m_wsDescription; }

double PoliticalActivity::getMoney() const { return m_dMoney;}

bool PoliticalActivity::isActive() const{ return m_bActive; }

bool PoliticalActivity::isSigned() const{ return m_bSigned; }

PoliticalActivity::~PoliticalActivity(){}
