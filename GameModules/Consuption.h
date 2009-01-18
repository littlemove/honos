#ifndef _CONSUPTION_H_
#define _CONSUPTION_H_

class Consuption{

public:
	Consuption(int iPopulationSize);

	double calculateConsuption(double dProductPrice) const;

	double calculateRealConsuption(double dProductPrice) const;

	int setPopulationSize(int dPopulationSize);

	int setSalary(int iSalary);

	~Consuption(void);

private:
	int m_iPopulationSize;	
	double m_dPurchasingPowerIndex;	
};

#endif
