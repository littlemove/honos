#include "Consuption.h"
#include <math.h>
#include "ErrorBase.h"

Consuption::Consuption(int iPopulationSize){
	m_iPopulationSize = iPopulationSize;
	m_dPurchasingPowerIndex = 1;	
}

Consuption::~Consuption(void){}

double Consuption::calculateConsuption(double dProductPrice) const{	

		return m_iPopulationSize / exp(dProductPrice);	
}

double Consuption::calculateRealConsuption(double dProductPrice) const{
	
	return m_iPopulationSize / exp(dProductPrice - m_dPurchasingPowerIndex);
}

