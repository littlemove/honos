#include "SocialServices.h"
#include "ConfigLoader.h"

using namespace core;

SocialServices::SocialServices(){
	ConfigLoader cl("resources/config/config.xml");
	cl.socialServicesLoader(this);

	update();
}

void SocialServices::addSocialService(SocialService* pSocialService){
	m_socialServicesList.push_back(pSocialService);
}

void SocialServices::setSalary(socialServiceID ID, double dIndex){
	m_socialServicesList.at(ID)->setSalary(dIndex);
}

void SocialServices::setResourceCost(socialServiceID ID, double dIndex){
	m_socialServicesList.at(ID)->setResourcesCost(dIndex);
}

SocialServiceState SocialServices::getState(socialServiceID ID) const{
	return m_socialServicesList.at(ID)->getState();
}

void SocialServices::setProperty(std::wstring wsName, double dValue){
	int iPos = wsName.find('_');
	std::wstring wsTarget = wsName.substr(0,iPos);
	std::wstring wsParam = wsName.substr(iPos+1);
	if(wsTarget == L"healthcare") m_socialServicesList.at(HEALTHCARE)->setProperty(wsParam,dValue);
	else if(wsTarget == L"education") m_socialServicesList.at(EDUCATION)->setProperty(wsParam,dValue);
	else if(wsTarget == L"justice") m_socialServicesList.at(JUSTICE)->setProperty(wsParam,dValue);

	else outputDbgString(wsTarget+L" not found");
}

void SocialServices::update(){
	std::vector<SocialService*>::iterator iter;	
	m_dQuality = 0;
	for(iter = m_socialServicesList.begin(); iter != m_socialServicesList.end(); ++iter){
		(*iter)->update();
		m_dQuality += (*iter)->getState().dServiceQuality;
	}
	m_dQuality /= m_socialServicesList.size();

	saveState();
}

std::wstring SocialServices::toString() const{
	std::vector<SocialService*>::const_iterator iter;
	std::wstring ws;
	for(iter = m_socialServicesList.begin(); iter != m_socialServicesList.end(); ++iter){
		ws += (*iter)->toString();
	}
	ws += L"**********************************************\n";
	return ws;
}

SocialServicesState SocialServices::getState() const{
	return m_state;
}

void SocialServices::saveState(){
	m_state.dQuality = m_dQuality;
	m_state.educationState = m_socialServicesList.at(EDUCATION)->getState();
	m_state.healthCareState = m_socialServicesList.at(HEALTHCARE)->getState();
	m_state.justiceState = m_socialServicesList.at(JUSTICE)->getState();
}

SocialServices::~SocialServices(){
	std::vector<SocialService*>::iterator iter;

	for(iter = m_socialServicesList.begin(); iter != m_socialServicesList.end(); ++iter){
		delete (*iter);
	}
}
