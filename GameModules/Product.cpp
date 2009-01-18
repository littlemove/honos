#include "Product.h"
#include "ErrorBase.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <memory>
#include <cmath>

using namespace core;

Product::Product(const wchar_t* pwcName) : ALPHA_PRICE(0.05){
	m_wsName = pwcName;
	m_dPPS = 1;
	m_dMoney = 10;	
	m_dLastTurnMoney = 10;	
	m_dStateMoney = 0;
	m_iStorage = 0;
	m_dNp = 1;
	m_dNi = 0;
	m_dCp = 1;
	m_dCi = 1;
	m_dLastTurnConsumption = 0;
	m_dExportation = 0;
	m_dIb = 0.5;
	m_dIi = 0;
	m_dLlastTurnGain = 0;
	m_dLastTurnTaxes = 0;
	m_iMaxStorageCapacity = 10;
	m_dMaxTotalProduct = 5;	
	m_dConsumption = 0;	
	m_dCpVariation = 0;

	m_dPriceVariation = 0;
	m_dInitialPrice = (m_dCp + (m_dCp * m_dIb) - (m_dCp * m_dIi));

	saveState();
}

Product::Product(const wchar_t* pwcName,										
				 double dMoney,		
				 int iStorage,
				 double dNp,
				 double dCp,				
				 double dIi,		
				 int iMaxStorageCapacity,
				 double dMaxTotalProduct) : ALPHA_PRICE(0.05){
					m_dTurn = 0.0;
					 m_wsName = pwcName;
					 m_dPPS = 1;
					 m_dMoney = dMoney;	
					 m_dLastTurnMoney = 10;	
					 m_dStateMoney = 0.0;
					 m_iStorage = iStorage;
					 m_dNp = dNp;
					 m_dNi = 0;
					 m_dCp = dCp;
					 m_dCi = dCp * 1.5;
					 m_dLastTurnConsumption = 0;
					 m_dExportation = 0;
					 m_dIb = 0.5;
					 m_dIi = 0.0;
					 m_dLlastTurnGain = 0;
					 m_dLastTurnTaxes = 0;
					 m_iMaxStorageCapacity = iMaxStorageCapacity;
					 m_dMaxTotalProduct = 100.0;	
					 m_dConsumption = 0;	
					 m_dCpVariation = 0;

					 m_dPriceVariation = 0;
					 m_dInitialPrice = (m_dCp + (m_dCp * m_dIb)) - (m_dCp * m_dIi);

					 saveState();

}

void Product::setProperty(std::wstring wsName, double dValue){
	if(wsName == L"money") setMoney(m_dMoney + dValue);
	else if(wsName == L"cp") setCp(m_dCp + (m_dCp*dValue));
	else if(wsName == L"ci") setCi(m_dCi + (m_dCi*dValue));
	else if(wsName == L"np") setNp(m_dNp + (m_dNp*dValue));
	else if(wsName == L"ni") setNp(m_dNp + (m_dNi*dValue));

	else outputDbgString(L"Property not found");
}


Product::~Product(void){}


void Product::update(void){	
	

	m_dPPS = abs(cos(m_dTurn/m_dNp));
	
	m_dPriceVariation = abs(sin(m_dTurn/(101.0-m_dCp)));
	double dModifier = m_dStateMoney - m_dIi;
	m_dPriceVariation -= (m_dPriceVariation * (dModifier));

	double dMoneyGained = m_dConsumption * m_dPPS * m_dIi * m_dCp;
	double dMoneyLost = m_dPPS * m_dStateMoney * m_dCp;

	m_dLlastTurnGain = dMoneyGained - dMoneyLost;

	saveState();
	m_dTurn++;
}

void Product::analyze(void){	

	double dTotalProduct = m_dNp + m_dNi;
	/* ************Estrategia 1
	//Aumenta el consumo (hay más demanda)
	if(m_dNp < m_dConsumption){
	setNp(m_dNp + 1);
	}
	//Disminuye el consumo
	else if(m_dNp > m_dConsumption){
	setNp(m_dNp - 1);
	setIb(m_dIb - 0.05);			
	}
	//Corregir pérdida de dinero
	if(m_dLastTurnMoney > m_dMoney){
	setIb(m_dIb + 0.05);
	}
	**************************/

	//Pierde dinero y baja el consumo: reduce producción y aumenta precios:
	if(m_state.dLlastTurnGain < 0 && (m_state.dConsumption >= m_dConsumption)){
		decreaseProduct(m_dConsumption);
		setIb(m_dIb + ALPHA_PRICE*m_dCp);
	}
	//Gana dinero y sube el consumo: aumenta producción:
	else if(m_state.dLlastTurnGain > 0 && (m_state.dConsumption < m_dConsumption)){
		increaseProduct(m_dConsumption);		
	}
	//Gana dinero y baja el consumo: baja el precio:
	else if(m_state.dLlastTurnGain > 0 && (m_state.dConsumption > m_dConsumption)){
		setIb(m_dIb - ALPHA_PRICE*m_dCp);
	}
	////Aumento de la demanda
	//double	dConsumption = (m_dConsumption * m_dNp);
	//if(dTotalProduct < dConsumption){
	//	//setNp(m_dNp + 1);
	//	increaseProduct(dConsumption);
	//	setIb(m_dIb + ALPHA_PRICE*m_dCp);
	//}
	////Disminición de la demanda
	//else if(dTotalProduct > dConsumption){
	//	//setNp(m_dNp - 1);
	//	decreaseProduct(dConsumption);
	//	setIb(m_dIb - ALPHA_PRICE*m_dCp);			
	//}				
	////Pérdidas
	//else if(m_dLlastTurnGain < 0){
	//	setIb(m_dIb + ALPHA_PRICE*m_dCp);
	//}

}

void Product::increaseProduct(double dNp){

	if(dNp > m_dMaxTotalProduct) dNp = m_dMaxTotalProduct;
	// ¿Es más barato importar que producir ayudado por el estado?
	double dCostProduct = (m_dCp - (m_dCp * m_dStateMoney)) * dNp;
	double dCostImportation = m_dCi * dNp;

	if(dCostImportation < (dCostProduct)){
		setNi(dNp - m_dNp);
	}		
	else{
		double dDifference = (dNp - (m_dNp + m_dNi));			
		double dIndex = dDifference / dNp;
		double dCost = m_dCp * dIndex;
		m_dMoney -= dCost;
		setNp(dNp - m_dNi);
	}

}

void Product::decreaseProduct(double dDecrease){

	// Si hay importación:
	if(m_dNi > 0){
		// ¿Es más barato importar que producir ayudado por el estado?
		//double dNewProduct = (m_dNp + m_dNi) - dDecrease;
		double dCostProduct = (m_dCp - (m_dCp * m_dStateMoney));
		double dCostImportation = m_dCi;

		if(dCostImportation > (dCostProduct)){
			setNi(m_dNi - 1);
		}
		else{
			setNp(m_dNp - 1);
		}
	}
	else{
		setNp(m_dNp - 1);
	}

}

int Product::setCi(double ci){

	if(ci >= 0){
		m_dCi = ci;			
	}
	else{
		m_dCi = 0;
	}
	return RET_OK;	

}

void Product::setConsumption(double dConsumption){

	m_dConsumption = dConsumption;	
}

int Product::setStateMoney(double dStateMoney){

	if(dStateMoney >= 0){
		m_dStateMoney = dStateMoney;						
	}
	else{
		m_dStateMoney = 0;
	}
	return RET_OK;	
}

int Product::setCp(double cp){

	if(cp >= 0){
		m_dCp = cp;			
	}
	else{
		m_dCp = 0;			
	}
	return RET_OK;
}

int Product::setExportation(double exportation){


	if(exportation >= 0){
		m_dExportation = exportation;
		return RET_OK;
	}
	else{
		m_dExportation = 0;			
	}
	return RET_OK;


}

int Product::setIb(double ib){


	if(ib >= 0){
		m_dIb = ib;		
		return RET_OK;
	}
	else{
		m_dIb = 0;
	}
	return RET_OK;


}

int Product::setIi(double ii){


	if(ii >= 0 && ii <= 1){
		m_dIi = ii;					
	}
	else{
		m_dIi = 0;
	}
	return RET_OK;


}

int Product::setNi(double ni){


	if(ni >= 0){
		m_dNi = ni;		
	}
	else{
		m_dNi = 0;
	}
	return RET_OK;


}

int Product::setNp(double np){

	if(np >= 0){			
		if(np > m_dMaxTotalProduct) m_dNp = m_dMaxTotalProduct;
		else m_dNp = np;
	}
	else{
		m_dNp = 0;
	}
	return RET_OK;


}

int Product::setMoney(double dMoney){			
	m_dMoney = dMoney;	
	return RET_OK;	
}


int Product::setStorage(int iStorage){

	if(iStorage >= 0){
		if(iStorage > m_iMaxStorageCapacity) m_iStorage = m_iMaxStorageCapacity;
		else m_iStorage = iStorage;			
	}
	else{
		m_iStorage = 0;
	}
	return RET_OK;


}

void Product::setPPS(double dPPS){

	if(dPPS >= 1){
		m_dPPS = 1;						
	}
	else{
		m_dPPS = dPPS;
	}	
}

double Product::getConsumption() const{
	return m_dConsumption;
}

double Product::getNp() const{
	return m_dNp;
}

ProductState Product::getState() const{
	return m_state;
}

// TODO: Falta implementación real
double Product::getProductionState() const{
	return 1.0;
}

int Product::saveState(){

	m_state.dPPS = m_dPPS;
	m_state.dCi = m_dCi;
	m_state.dConsumption = m_dConsumption;
	m_state.dCp = m_dCp;
	m_state.dPriceVariation = m_dPriceVariation;
	m_state.dExportation = m_dExportation;
	m_state.dIb = m_dIb;
	m_state.dIi = m_dIi;
	m_state.dLastTurnConsumption = m_dLastTurnConsumption;
	m_state.dLastTurnMoney = m_dLastTurnMoney;
	m_state.dLastTurnTaxes = m_dLastTurnTaxes;
	m_state.dLlastTurnGain = m_dLlastTurnGain;
	m_state.dMaxStorageCapacity = m_iMaxStorageCapacity;
	m_state.dMaxTotalProduct = m_dMaxTotalProduct;
	m_state.dMoney = m_dMoney;
	m_state.dNi = m_dNi;
	m_state.dNp = m_dNp;
	m_state.dStateMoney = m_dStateMoney;
	m_state.dStorage = m_iStorage;	

	return RET_OK;
}


std::wstring Product::toString(void){

	std::wstringstream strm;
	std::wstringstream wss;

	wss << std::setiosflags(std::ios::fixed) << std::setprecision(3);
	wss << m_wsName << "\n";
	wss << "------------------------" << "\n";
	wss << "PPS: " <<  m_dPPS << "\n";
	wss << "Last turn gain: "<< m_dLlastTurnGain << "\n";
	wss << "Last turn taxes: "<<  m_dLastTurnTaxes << "\n";
	wss << "************************" << "\n";
	wss << "Money: " <<  m_dMoney << "\n";
	wss << "(z)m_state money: " <<   m_dStateMoney << "\n";
	wss << "Storage: "<<  m_iStorage << "\n";	
	//wss << "(c)Consumption: " << m_dConsumption << "\n";
	wss << "Consumption: " << m_dConsumption << "\n";
	//wss << "(e)Exportation: "<<  m_dExportation << "\n";
	wss << "************************" << "\n";	
	wss << "Product:" << "\n";	
	//wss << "(n)Units Per Turn: "<<  m_dNp << " (p)Cost Unit Per Turn: " << m_dCp << "\n\n";	
	wss << "Units Per Turn: "<<  m_dNp << " (p)Cost Unit Per Turn: " << m_dCp << "\n\n";	
	wss << "Importation:" << "\n";
	//wss << "(i)Units Per Turn: "<<  m_dNi << " (m)Cost Unit Per Turn: " << m_dCi << "\n\n";
	wss << "Units Per Turn: "<<  m_dNi << " (m)Cost Unit Per Turn: " << m_dCi << "\n\n";
	wss << "Taxes & Profit:" << "\n";
	//wss << "(1)Profit Index: "<<  m_dIb << " (2)Tax Index: " << m_dIi << "\n";
	wss << "Profit Index: "<<  m_dIb << " (2)Tax Index: " << m_dIi << "\n";
	wss << "Price Variation: " <<  m_dPriceVariation << "\n";
	wss << "------------------------" << "\n";	

	return wss.str();	
}
