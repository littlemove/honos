#include "CountryState.h"

using namespace core;

CountryState::CountryState(Production* pProduction, Population* pPopulation, SocialServices* pSocialServices, Diplomacy* pDiplomacy, LocalPolicies* pLocalPolicies){
	m_iTurn = -1;
	m_dTotalHappiness = 0;
	m_dTotalMoney = 0;
	m_pProduction = pProduction;
	m_pPopulation = pPopulation;
	m_pSocialServices = pSocialServices;	
	m_pDiplomacy = pDiplomacy;
	m_pLocalPolicies = pLocalPolicies;

	update();
}


double CountryState::getCurrentValue(std::wstring wsParam) const{
	std::map<std::wstring, double>::const_iterator iter;
	iter = m_countryStateInfo.find(wsParam);
	if(iter != m_countryStateInfo.end()) return iter->second;

	else return NOT_FOUND;
}

int CountryState::getCurrentTurn() const{
	return m_iTurn;
}
double CountryState::getTotalMoney() const{
	return m_dTotalMoney;
}
void CountryState::calculateHappiness(){
	m_dTotalHappiness += m_populationStates.at(m_iTurn).dHappiness;	
}

void CountryState::calculateMoney(){
	double dSssExpenses = m_socialServicesStates.at(m_iTurn).healthCareState.dTurnSalaryExpenses + m_socialServicesStates.at(m_iTurn).educationState.dTurnSalaryExpenses + m_socialServicesStates.at(m_iTurn).justiceState.dTurnSalaryExpenses;
	dSssExpenses += m_socialServicesStates.at(m_iTurn).healthCareState.dTurnResourcesExpenses + m_socialServicesStates.at(m_iTurn).educationState.dTurnResourcesExpenses + m_socialServicesStates.at(m_iTurn).justiceState.dTurnResourcesExpenses;
	double dProductionExpenses = m_productionStates.at(m_iTurn).foodState.dLlastTurnGain + m_productionStates.at(m_iTurn).energyState.dLlastTurnGain + m_productionStates.at(m_iTurn).manufacturedState.dLlastTurnGain;

	m_dTotalMoney += dSssExpenses + (-1.0*dProductionExpenses);
}

void CountryState::update(){
	m_iTurn++;

	m_populationStates.push_back(m_pPopulation->getState());
	m_productionStates.push_back(m_pProduction->getState());
	m_socialServicesStates.push_back(m_pSocialServices->getState());
	m_diplomacyStates.push_back(m_pDiplomacy->getState());	
	fillCountryStateInfo();

	calculateMoney();

	updatePoliticalActivities();
	applyPoliticalActivities();
}

void CountryState::updatePoliticalActivities(){	
	// Para las relaciones diplomáticas:
	//Por cada país.
	for(int i = 0; i < 3;i++){
		bool bActivateTreaty = true;		
		ForeignCountry* pFc = m_pDiplomacy->accesForeignCountry(i);
		//Por cada actividad política
		for(int i = 0; i < pFc->m_treatyList.size(); i++){
			PoliticalActivity* pPa = pFc->m_treatyList.at(i);
			std::map<std::wstring, ReqValue>::iterator iter;
			std::map<std::wstring, ReqValue> temp = pPa->getRequeriments();
			//Por cada requerimiento
			for(iter = temp.begin(); iter != temp.end(); ++iter){
				double dCurrent = getCurrentValue((*iter).first);
				if(dCurrent <= (*iter).second.dValue  || dCurrent > (*iter).second.dInterval){
					bActivateTreaty = false;						
					break;
				}
			}
			pPa->setActive(bActivateTreaty);

			if(!bActivateTreaty) pPa->setSigned(false);		
			bActivateTreaty = true;
		}
	}
	/////////////////////////////////////////

	// Para las políticas locales	
	bool bActivatePolicy = true;
	int i = 0;
	for(i = 0; i < m_pLocalPolicies->m_policyList.size(); i++){
		PoliticalActivity* pPa = m_pLocalPolicies->m_policyList.at(i);
		std::map<std::wstring, ReqValue>::iterator iter;
		std::map<std::wstring, ReqValue> temp = pPa->getRequeriments();
		//Por cada requerimiento
		for(iter = temp.begin(); iter != temp.end(); ++iter){
			double dCurrent = getCurrentValue((*iter).first);
			if(dCurrent <= (*iter).second.dValue  || dCurrent > (*iter).second.dInterval){
				bActivatePolicy = false;						
				break;
			}
		}
		pPa->setActive(bActivatePolicy);
		
		if(!bActivatePolicy) pPa->setSigned(false);	
		bActivatePolicy = true;
	}	
}

void CountryState::applyPoliticalActivities(){
	// Para las relaciones diplomáticas:
	for(int i = 0; i < 3;i++){
		bool bActivateTreaty = false;
		ForeignCountry* pFc = m_pDiplomacy->accesForeignCountry(i);
		for(int i = 0; i < pFc->m_treatyList.size(); i++){
			PoliticalActivity* pPa = pFc->m_treatyList.at(i);
			// Si el tratado está firmado, aplicamos todos los efectos:
			if(pPa->isActive() && pPa->isSigned()){
				std::map<std::wstring, double>::iterator iter;
				std::map<std::wstring, double> temp = pPa->getEffects();

				for(iter = temp.begin(); iter != temp.end(); ++iter){
					std::wstring wsType = (*iter).first;
					double dValue = (*iter).second;

					int iPos = wsType.find('_');
					std::wstring wsTarget = wsType.substr(0,iPos);
					std::wstring wsParam = wsType.substr(iPos+1);
					if(wsTarget == L"pr") m_pProduction->setProperty(wsParam,dValue);
					else if(wsTarget == L"po")  m_pPopulation->setProperty(wsParam,dValue);
					else if(wsTarget == L"ss")  m_pSocialServices->setProperty(wsParam,dValue);				
				}
			}			
		}
	}
	/////////////////////////////////////////

	//Para las políticas locales		
	for(int i = 0; i < m_pLocalPolicies->m_policyList.size(); i++){
		PoliticalActivity* pPa = m_pLocalPolicies->m_policyList.at(i);
		// Si el tratado está firmado, aplicamos todos los efectos:
		if(pPa->isActive() && pPa->isSigned()){
			std::map<std::wstring, double>::iterator iter;
			std::map<std::wstring, double> temp = pPa->getEffects();

			for(iter = temp.begin(); iter != temp.end(); ++iter){
				std::wstring wsType = (*iter).first;
				double dValue = (*iter).second;

				int iPos = wsType.find('_');
				std::wstring wsTarget = wsType.substr(0,iPos);
				std::wstring wsParam = wsType.substr(iPos+1);
				if(wsTarget == L"pr") m_pProduction->setProperty(wsParam,dValue);
				else if(wsTarget == L"po")  m_pPopulation->setProperty(wsParam,dValue);
				else if(wsTarget == L"ss")  m_pSocialServices->setProperty(wsParam,dValue);	

				m_dTotalMoney += pPa->getMoney();
			}
		}
	}	
}

void CountryState::fillCountryStateInfo(){
	typedef std::pair<std::wstring, double> pair;
	m_countryStateInfo.clear();
	// Production info
	m_countryStateInfo.insert(pair(L"pr_all_pps",m_productionStates.at(m_iTurn).dPPS));
	m_countryStateInfo.insert(pair(L"pr_all_energyPps",m_productionStates.at(m_iTurn).dEnergyPPS));
	m_countryStateInfo.insert(pair(L"pr_all_foodPps",m_productionStates.at(m_iTurn).dFoodPPS));
	m_countryStateInfo.insert(pair(L"pr_all_manufacturedPps",m_productionStates.at(m_iTurn).dManufacturedPPS));
	m_countryStateInfo.insert(pair(L"pr_all_foodConsuption",m_productionStates.at(m_iTurn).foodState.dConsumption));

	m_countryStateInfo.insert(pair(L"pr_food_np",m_productionStates.at(m_iTurn).foodState.dNp));
	m_countryStateInfo.insert(pair(L"pr_food_cp",m_productionStates.at(m_iTurn).foodState.dCp));
	m_countryStateInfo.insert(pair(L"pr_food_gain",m_productionStates.at(m_iTurn).foodState.dLlastTurnGain));
	m_countryStateInfo.insert(pair(L"pr_food_money",m_productionStates.at(m_iTurn).foodState.dMoney));
	m_countryStateInfo.insert(pair(L"pr_food_ni",m_productionStates.at(m_iTurn).foodState.dNi));
	m_countryStateInfo.insert(pair(L"pr_food_stateMoney",m_productionStates.at(m_iTurn).foodState.dStateMoney));
	m_countryStateInfo.insert(pair(L"pr_food_priceVariation",m_productionStates.at(m_iTurn).foodState.dPriceVariation));

	m_countryStateInfo.insert(pair(L"pr_energy_np",m_productionStates.at(m_iTurn).energyState.dNp));
	m_countryStateInfo.insert(pair(L"pr_energy_cp",m_productionStates.at(m_iTurn).energyState.dCp));
	m_countryStateInfo.insert(pair(L"pr_energy_gain",m_productionStates.at(m_iTurn).energyState.dLlastTurnGain));
	m_countryStateInfo.insert(pair(L"pr_energy_money",m_productionStates.at(m_iTurn).energyState.dMoney));
	m_countryStateInfo.insert(pair(L"pr_energy_ni",m_productionStates.at(m_iTurn).energyState.dNi));
	m_countryStateInfo.insert(pair(L"pr_energy_stateMoney",m_productionStates.at(m_iTurn).energyState.dStateMoney));
	m_countryStateInfo.insert(pair(L"pr_energy_priceVariation",m_productionStates.at(m_iTurn).energyState.dPriceVariation));
	m_countryStateInfo.insert(pair(L"pr_energy_consuption",m_productionStates.at(m_iTurn).energyState.dConsumption));

	m_countryStateInfo.insert(pair(L"pr_manufactured_np",m_productionStates.at(m_iTurn).manufacturedState.dNp));
	m_countryStateInfo.insert(pair(L"pr_manufactured_cp",m_productionStates.at(m_iTurn).manufacturedState.dCp));
	m_countryStateInfo.insert(pair(L"pr_manufactured_gain",m_productionStates.at(m_iTurn).manufacturedState.dLlastTurnGain));
	m_countryStateInfo.insert(pair(L"pr_manufactured_money",m_productionStates.at(m_iTurn).manufacturedState.dMoney));
	m_countryStateInfo.insert(pair(L"pr_manufactured_ni",m_productionStates.at(m_iTurn).manufacturedState.dNi));
	m_countryStateInfo.insert(pair(L"pr_manufactured_stateMoney",m_productionStates.at(m_iTurn).manufacturedState.dStateMoney));
	m_countryStateInfo.insert(pair(L"pr_manufactured_priceVariation",m_productionStates.at(m_iTurn).manufacturedState.dPriceVariation));
	m_countryStateInfo.insert(pair(L"pr_manufactured_consuption",m_productionStates.at(m_iTurn).manufacturedState.dConsumption));

	//Population info
	m_countryStateInfo.insert(pair(L"po_all_energy",m_populationStates.at(m_iTurn).dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_all_food",m_populationStates.at(m_iTurn).dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_all_manufactured",m_populationStates.at(m_iTurn).dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_all_happiness",m_populationStates.at(m_iTurn).dHappiness));
	m_countryStateInfo.insert(pair(L"po_all_size",m_populationStates.at(m_iTurn).dSize));

	m_countryStateInfo.insert(pair(L"po_conservatives_happiness",m_populationStates.at(m_iTurn).conservativesState.dLastTurnHappiness));
	m_countryStateInfo.insert(pair(L"po_conservatives_energy",m_populationStates.at(m_iTurn).conservativesState.dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_conservatives_consuptionPower",m_populationStates.at(m_iTurn).conservativesState.dConsumptionPower));
	m_countryStateInfo.insert(pair(L"po_conservatives_food",m_populationStates.at(m_iTurn).conservativesState.dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_conservatives_manufactured",m_populationStates.at(m_iTurn).conservativesState.dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_conservatives_size",m_populationStates.at(m_iTurn).conservativesState.dSize));

	m_countryStateInfo.insert(pair(L"po_merchants_happiness",m_populationStates.at(m_iTurn).merchantsState.dLastTurnHappiness));
	m_countryStateInfo.insert(pair(L"po_merchants_energy",m_populationStates.at(m_iTurn).merchantsState.dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_merchants_consuptionPower",m_populationStates.at(m_iTurn).merchantsState.dConsumptionPower));
	m_countryStateInfo.insert(pair(L"po_merchants_food",m_populationStates.at(m_iTurn).merchantsState.dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_merchants_manufactured",m_populationStates.at(m_iTurn).merchantsState.dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_merchants_size",m_populationStates.at(m_iTurn).merchantsState.dSize));

	m_countryStateInfo.insert(pair(L"po_ultrademocrats_happiness",m_populationStates.at(m_iTurn).ultrademocratsState.dLastTurnHappiness));
	m_countryStateInfo.insert(pair(L"po_ultrademocrats_energy",m_populationStates.at(m_iTurn).ultrademocratsState.dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_ultrademocrats_consuptionPower",m_populationStates.at(m_iTurn).ultrademocratsState.dConsumptionPower));
	m_countryStateInfo.insert(pair(L"po_ultrademocrats_food",m_populationStates.at(m_iTurn).ultrademocratsState.dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_ultrademocrats_manufactured",m_populationStates.at(m_iTurn).ultrademocratsState.dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_ultrademocrats_size",m_populationStates.at(m_iTurn).ultrademocratsState.dSize));

	m_countryStateInfo.insert(pair(L"po_aislanders_happiness",m_populationStates.at(m_iTurn).aislandersState.dLastTurnHappiness));
	m_countryStateInfo.insert(pair(L"po_aislanders_energy",m_populationStates.at(m_iTurn).aislandersState.dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_aislanders_consuptionPower",m_populationStates.at(m_iTurn).aislandersState.dConsumptionPower));
	m_countryStateInfo.insert(pair(L"po_aislanders_food",m_populationStates.at(m_iTurn).aislandersState.dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_aislanders_manufactured",m_populationStates.at(m_iTurn).aislandersState.dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_aislanders_size",m_populationStates.at(m_iTurn).aislandersState.dSize));

	m_countryStateInfo.insert(pair(L"po_greens_happiness",m_populationStates.at(m_iTurn).greensState.dLastTurnHappiness));
	m_countryStateInfo.insert(pair(L"po_greens_energy",m_populationStates.at(m_iTurn).greensState.dEnergyConsumption));
	m_countryStateInfo.insert(pair(L"po_greens_consuptionPower",m_populationStates.at(m_iTurn).greensState.dConsumptionPower));
	m_countryStateInfo.insert(pair(L"po_greens_food",m_populationStates.at(m_iTurn).greensState.dFoodConsumption));
	m_countryStateInfo.insert(pair(L"po_greens_manufactured",m_populationStates.at(m_iTurn).greensState.dManufacturedConsumption));
	m_countryStateInfo.insert(pair(L"po_greens_size",m_populationStates.at(m_iTurn).greensState.dSize));

	//Social services info
	m_countryStateInfo.insert(pair(L"ss_all_quality",m_socialServicesStates.at(m_iTurn).dQuality));

	m_countryStateInfo.insert(pair(L"ss_healthcare_personal",m_socialServicesStates.at(m_iTurn).healthCareState.dPersonal));
	m_countryStateInfo.insert(pair(L"ss_healthcare_resources",m_socialServicesStates.at(m_iTurn).healthCareState.dResources));
	m_countryStateInfo.insert(pair(L"ss_healthcare_salary",m_socialServicesStates.at(m_iTurn).healthCareState.dTurnSalaryExpenses));
	m_countryStateInfo.insert(pair(L"ss_healthcare_salaryIndex",m_socialServicesStates.at(m_iTurn).healthCareState.dSalary));
	m_countryStateInfo.insert(pair(L"ss_healthcare_resourcesCostIndex",m_socialServicesStates.at(m_iTurn).healthCareState.dResourcesCost));
	m_countryStateInfo.insert(pair(L"ss_healthcare_resourcesCost",m_socialServicesStates.at(m_iTurn).healthCareState.dTurnResourcesExpenses));
	m_countryStateInfo.insert(pair(L"ss_healthcare_quality",m_socialServicesStates.at(m_iTurn).healthCareState.dServiceQuality));
	m_countryStateInfo.insert(pair(L"ss_healthcare_resourcesCostOP",m_socialServicesStates.at(m_iTurn).healthCareState.dResourcesExpensesOP));
	m_countryStateInfo.insert(pair(L"ss_healthcare_salaryOP",m_socialServicesStates.at(m_iTurn).healthCareState.dSalaryOP));

	m_countryStateInfo.insert(pair(L"ss_education_personal",m_socialServicesStates.at(m_iTurn).educationState.dPersonal));
	m_countryStateInfo.insert(pair(L"ss_education_resources",m_socialServicesStates.at(m_iTurn).educationState.dResources));
	m_countryStateInfo.insert(pair(L"ss_education_salary",m_socialServicesStates.at(m_iTurn).educationState.dTurnSalaryExpenses));
	m_countryStateInfo.insert(pair(L"ss_education_resourcesCost",m_socialServicesStates.at(m_iTurn).educationState.dTurnResourcesExpenses));
	m_countryStateInfo.insert(pair(L"ss_education_quality",m_socialServicesStates.at(m_iTurn).educationState.dServiceQuality));
	m_countryStateInfo.insert(pair(L"ss_education_resourcesCostOP",m_socialServicesStates.at(m_iTurn).educationState.dResourcesExpensesOP));
	m_countryStateInfo.insert(pair(L"ss_education_salaryOP",m_socialServicesStates.at(m_iTurn).educationState.dSalaryOP));
	m_countryStateInfo.insert(pair(L"ss_education_salaryIndex",m_socialServicesStates.at(m_iTurn).educationState.dSalary));
	m_countryStateInfo.insert(pair(L"ss_education_resourcesCostIndex",m_socialServicesStates.at(m_iTurn).educationState.dResourcesCost));

	m_countryStateInfo.insert(pair(L"ss_justice_personal",m_socialServicesStates.at(m_iTurn).justiceState.dPersonal));
	m_countryStateInfo.insert(pair(L"ss_justice_resources",m_socialServicesStates.at(m_iTurn).justiceState.dResources));
	m_countryStateInfo.insert(pair(L"ss_justice_salary",m_socialServicesStates.at(m_iTurn).justiceState.dTurnSalaryExpenses));
	m_countryStateInfo.insert(pair(L"ss_justice_resourcesCost",m_socialServicesStates.at(m_iTurn).justiceState.dTurnResourcesExpenses));
	m_countryStateInfo.insert(pair(L"ss_justice_quality",m_socialServicesStates.at(m_iTurn).justiceState.dServiceQuality));
	m_countryStateInfo.insert(pair(L"ss_justice_resourcesCostOP",m_socialServicesStates.at(m_iTurn).justiceState.dResourcesExpensesOP));
	m_countryStateInfo.insert(pair(L"ss_justice_salaryOP",m_socialServicesStates.at(m_iTurn).justiceState.dSalaryOP));
	m_countryStateInfo.insert(pair(L"ss_justice_salaryIndex",m_socialServicesStates.at(m_iTurn).justiceState.dSalary));
	m_countryStateInfo.insert(pair(L"ss_justice_resourcesCostIndex",m_socialServicesStates.at(m_iTurn).justiceState.dResourcesCost));

	//Diplomacy info
	m_countryStateInfo.insert(pair(L"di_all_opinion",m_diplomacyStates.at(m_iTurn).dOpinion));

	m_countryStateInfo.insert(pair(L"di_england_opinion",m_diplomacyStates.at(m_iTurn).englandState.dOpinon));
	m_countryStateInfo.insert(pair(L"di_france_opinion",m_diplomacyStates.at(m_iTurn).franceState.dOpinon));
	m_countryStateInfo.insert(pair(L"di_usa_opinion",m_diplomacyStates.at(m_iTurn).usaState.dOpinon));

}

CountryState::~CountryState(){}
