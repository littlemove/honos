#include "LocalPolicies.h"
#include "ConfigLoader.h"

using namespace core;

LocalPolicies::LocalPolicies(){
	ConfigLoader cl("resources/config/config.xml");
	cl.localPoliciesLoader(this);	
}

PoliticalActivity* LocalPolicies::getCurrentTreaty(){
	if(!m_policyList.empty())return (*m_pCurrentPolicyIter);
	else return NULL;
}

void LocalPolicies::addPolicy(core::PoliticalActivity *pPA){
	m_policyList.push_back(pPA);
	m_pCurrentPolicyIter = m_policyList.begin();
}

void LocalPolicies::deletePolicy(int iPosition){
	std::vector<PoliticalActivity*>::iterator iter = m_policyList.begin();
	for(int i = 0; i != iPosition; i++){
		++iter;
	}
	delete (*iter);
	m_policyList.erase(iter);
}

void LocalPolicies::next(){
	m_pCurrentPolicyIter++;
	if(m_pCurrentPolicyIter == m_policyList.end()){
		m_pCurrentPolicyIter = m_policyList.begin();
	}
}

LocalPolicies::~LocalPolicies(){
	std::vector<PoliticalActivity*>::iterator iter;
	for(iter = m_policyList.begin(); iter != m_policyList.end(); ++iter){
		delete (*iter);
	}
}
