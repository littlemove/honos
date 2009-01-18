#include "SocialService.h"
#include <cmath>
#include <sstream>

using namespace core;

SocialService::SocialService(const wchar_t* pwcName,const wchar_t* pwcDescription, double dSalaryOP, double dResourcesExpensesOP, double dPersonalImportance, double dResourcesImportance){	
	m_wsName = pwcName;
	m_wsDescription = pwcDescription;
	m_dSalaryOP = dSalaryOP;
	m_dResourcesExpensesOP = dResourcesExpensesOP;
	m_dPersonalImportance =boundaryCheck(0,1,dPersonalImportance);
	m_dResourcesImportance =boundaryCheck(0,1,dResourcesImportance);

	if((m_dPersonalImportance + dResourcesImportance) != 1){
		m_dPersonalImportance = 0.5;
		m_dResourcesImportance = 0.5;
		outputDbgString(L"Invalid importance values");
	}

	m_dSalary = 0.0;
	m_dResourcesCost = 0.0;

	m_dPersonalOP = 0.0005;
	m_dResourcesOP = 0.005;

	m_dPersonal = 0.5;
	m_dResources = 0.5;

	saveState();
}

SocialServiceState SocialService::getState() const{
	return m_state;
}

double SocialService::calculateSalaryExpenses() const{
	return m_dSalary * m_dSalaryOP * m_dPersonal * m_dPersonalOP;
}

double SocialService::calculateResourcesExpenses() const{
	return m_dResourcesCost * m_dResourcesExpensesOP * m_dResources * m_dResourcesOP;
}

double SocialService::calculateServiceQuality() const{
	double dPersonalQuality =  m_dPersonalImportance * calculatePersonalProductivity() * m_dPersonal;
	double dResourcesQuality = m_dResourcesImportance * calculateResourcesProductivity() * m_dResources; 
	
	if(dPersonalQuality == 0.0 || dResourcesQuality == 0.0) return 0.0;
	else return dPersonalQuality + dResourcesQuality;
}

double SocialService::calculatePersonalProductivity() const{
	double dExp = log(1 - m_dPersonalImportance) / log(0.5);	
	
	return powl(m_dSalary,dExp);	
}

double SocialService::calculateResourcesProductivity() const{
	double dExp = log(1- m_dResourcesImportance) / log(0.5);	
	
	return powl(m_dResourcesCost,dExp);	
}

void SocialService::setSalary(double dIndex){
	m_dSalary =boundaryCheck(0,1,dIndex);
}

void SocialService::setResourcesCost(double dIndex){
	m_dResourcesCost =boundaryCheck(0,1,dIndex);
}

void SocialService::setProperty(std::wstring wsName, double dValue){
	if(wsName == L"personal") setPersonal(m_dPersonal + (m_dPersonal*dValue));
	else if(wsName == L"resources") setResources(m_dResources + (m_dResources*dValue));
	else if(wsName == L"salary") m_dSalaryOP = (m_dSalaryOP + (m_dSalaryOP*dValue));
	else if(wsName == L"resourcesCostOP") m_dResourcesExpensesOP = (m_dResourcesExpensesOP + (m_dResourcesExpensesOP*dValue));
	else if(wsName == L"salaryOP") m_dSalaryOP = (m_dSalaryOP + (m_dSalaryOP*dValue));

	else outputDbgString(L"Property not found");
}

void SocialService::setPersonal(double dValue){
	m_dPersonal = boundaryCheck(0,1,dValue);
}

void SocialService::setResources(double dValue){
	m_dResources = boundaryCheck(0,1,dValue);
}

void SocialService::update(){
	saveState();
}

void SocialService::saveState(){
	m_state.dPersonal = m_dPersonal;
	m_state.dResources = m_dResources;
	m_state.dSalary = m_dSalary;
	m_state.dResourcesCost = m_dResourcesCost;
	m_state.dSalaryOP = m_dSalaryOP;
	m_state.dResourcesExpensesOP = m_dResourcesExpensesOP;
	m_state.dPersonalImportance = m_dPersonalImportance;
	m_state.dResourcesImportance = m_dResourcesImportance;
	m_state.dTurnSalaryExpenses = calculateSalaryExpenses();
	m_state.dTurnResourcesExpenses = calculateResourcesExpenses();
	m_state.dTurnPersonalProductivity = calculatePersonalProductivity();
	m_state.dTurnResourcesProductivity = calculateResourcesProductivity();
	m_state.dServiceQuality = calculateServiceQuality();
}

std::wstring SocialService::toString() const{
	std::wstringstream wss;
	wss << m_wsName << std::endl;
	wss << L"Personal: " << m_dPersonal << std::endl;
	wss << L"Resources: " << m_dResources << std::endl;	
	wss << L"Personal productivity: " << calculatePersonalProductivity() << std::endl;
	wss << L"Resources productivity: " << calculateResourcesProductivity() << std::endl;
	wss << L"Quality: " << calculateServiceQuality() << std::endl;
	wss << L"=============================="<< std::endl;
	wss << std::endl;

	return wss.str();
}

SocialService::~SocialService(){}
