#include "Production.h"
#include "ConfigLoader.h"

using namespace core;

Production::Production(){
	ConfigLoader cl("resources/config/config.xml");
	cl.productionLoader(this);	

	m_dFoodPriceVariation = 0;		
	m_dEnergyPriceVariation = 0;
	m_dManufacturedPriceVariation = 0;
	m_dFoodPPS = 1;
	m_dEnergyPPS = 1;
	m_dManufacturedPPS = 1;

	m_dPPS = 1;
	//update();
	saveState();
}

void Production::addProduct(Product *pProduct){
	m_productList.push_back(pProduct);
}

ProductionState Production::getState() const{
	return m_state;
}

void Production::setProperty(std::wstring wsName, double dValue){
	int iPos = wsName.find('_');
	std::wstring wsTarget = wsName.substr(0,iPos);
	std::wstring wsParam = wsName.substr(iPos+1);
	if(wsTarget == L"food") m_productList.at(FOOD)->setProperty(wsParam,dValue);
	else if(wsTarget == L"energy") m_productList.at(ENERGY)->setProperty(wsParam,dValue);
	else if(wsTarget == L"manufactured") m_productList.at(MANUFACTURED)->setProperty(wsParam,dValue);

	else outputDbgString(wsTarget+L" not found");
}

ProductState Production::getProductState(productID ID) const{
	return m_productList.at(ID)->getState();
}

void Production::setStateMoney(productID ID, double dMoney){
	m_productList.at(ID)->setStateMoney(dMoney);
}

void Production::setTax(productID ID, double dTaxIndex){
	
	m_productList.at(ID)->setIi(boundaryCheck(0,1,dTaxIndex));
}

void Production::setConsumption(productID ID , double dConsumption){
	m_productList[ID]->setConsumption(dConsumption);
}

void Production::setPPS(double dPopulationSize){
	std::vector<Product*>::iterator iter;
	for(iter = m_productList.begin(); iter != m_productList.end(); ++iter){		
		(*iter)->setPPS((*iter)->getNp() / dPopulationSize);
	}
}


void Production::saveState(){
	m_state.dEnergyPPS = m_dEnergyPPS;
	m_state.dFoodPPS = m_dFoodPPS;
	m_state.dManufacturedPPS = m_dManufacturedPPS;
	m_state.dFoodPriceVariation = m_dFoodPriceVariation;
	m_state.dEnergyPriceVariation =  m_dEnergyPriceVariation;
	m_state.dManufacturedPriceVariation = m_dManufacturedPriceVariation;
	m_state.dPPS = m_dPPS;

	m_state.energyState = m_productList.at(ENERGY)->getState();
	m_state.foodState = m_productList.at(FOOD)->getState();
	m_state.manufacturedState = m_productList.at(MANUFACTURED)->getState();
}


void Production::update(){
	std::vector<Product*>::iterator iter;	
	m_dPPS = 0;
	for(iter = m_productList.begin(); iter != m_productList.end(); ++iter){		
		(*iter)->update();
		m_dPPS += (*iter)->getState().dPPS;
	}
	m_dPPS /= m_productList.size();
	m_dFoodPriceVariation = m_productList.at(FOOD)->getState().dPriceVariation;
	m_dEnergyPriceVariation =  m_productList.at(ENERGY)->getState().dPriceVariation;
	m_dManufacturedPriceVariation = m_productList.at(MANUFACTURED)->getState().dPriceVariation;

	m_dFoodPPS = boundaryCheck(0.0,1.0, m_productList.at(FOOD)->getState().dPPS);
	m_dEnergyPPS =  boundaryCheck(0.0,1.0, m_productList.at(ENERGY)->getState().dPPS);
	m_dManufacturedPPS =  boundaryCheck(0.0,1.0, m_productList.at(MANUFACTURED)->getState().dPPS);

	saveState();
}

std::wstring Production::toString() const{
	std::wstring wst;
	std::vector<Product*>::const_iterator iter;
	for(iter = m_productList.begin(); iter != m_productList.end(); ++iter){
		wst += (*iter)->toString();
		break;
	}	
	return wst;
}

Production::~Production(){
	std::vector<Product*>::iterator iter;
	for(iter = m_productList.begin(); iter != m_productList.end(); ++iter){
		delete (*iter);
	}
}
