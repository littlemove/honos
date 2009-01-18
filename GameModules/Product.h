#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>
#include "Base.h"

namespace core{

	struct ProductState{
		double dPPS;
		double dMoney;
		double dStateMoney;
		double dStorage;
		double dNp;
		double dCp;
		double dPriceVariation;
		double dNi;
		double dCi;
		double dIb;
		double dIi;
		double dConsumption;	
		double dExportation;
		double dMaxStorageCapacity;
		double dMaxTotalProduct;	
		double dLastTurnConsumption;
		double dLastTurnMoney;
		double dLlastTurnGain;
		double dLastTurnTaxes;
	};
	
	/**
	* Esta clase representa uno de los productos que conforma la produción del país del jugador.
	*/
	class Product {

	public:
		/*
		* Constructor.
		* @param pwcName nombre del producto.
		*/
		Product(const wchar_t* pwcName);
		
		/*
		* Constructor.
		* @param pwcName nombre del producto.
		* @param dMoney 
		* @param dNp estabilidad de la producción.
		* @param dCp coste de producción.
		* @param dIi índice de impuestos.
		* @param iMaxStorageCapacity
		* @param dMaxTotalProduct		
		*/
		Product(const wchar_t* pwcName,										
			double dMoney,		
			int iStorage,
			double dNp,
			double dCp,				
			double dIi,		
			int iMaxStorageCapacity,
			double dMaxTotalProduct);		

		/**
		* Asigna un valor a una propiedad del objeto especificada (si existe).
		* @param wsName nombre de la propiedad.
		* @param dValue valor a asignar.
		*/
		void setProperty(std::wstring wsName, double dValue);

		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update(void);	

		int setNp(double NP);

		int setNi(double NI);

		int setCp(double CP);

		int setCi(double CI);

		int setIb(double IB);

		int setIi(double II);

		void setConsumption(double dConsumption);

		int setExportation(double exportation);

		int setStateMoney(double m_stateMoney);

		void setPPS(double dPPS);

		double getConsumption() const;

		double getNp() const;
		
		/**
		* Devuelve el estado de la clase.
		* @return ProductState.
		*/
		ProductState getState() const;

		double getProductionState() const;

		std::wstring toString();

		~Product(void);

	private:
		const double ALPHA_PRICE;
		double m_dTurn;
		std::wstring m_wsName;
		std::wstring m_wsDescription;
		struct ProductState m_state;
		double m_dPriceVariation;
		double m_dInitialPrice;
		double m_dPPS; //Production Power State
		double m_dMoney;
		double m_dStateMoney;
		int m_iStorage;
		double m_dNp;
		double m_dCp;
		double m_dNi;
		double m_dCi;
		double m_dIb;
		double m_dIi;
		double m_dConsumption;
		double m_dExportation;
		int m_iMaxStorageCapacity;
		double m_dMaxTotalProduct;
		double m_dCpVariation;

		double m_dLastTurnConsumption;
		double m_dLastTurnMoney;
		double m_dLlastTurnGain;
		double m_dLastTurnTaxes;

		void analyze(void);
		void increaseProduct(double dNp);
		void decreaseProduct(double dDecrease);
		int setMoney(double dMoney);
		int setStorage(int iStorage);
		int saveState();

	};
}

#endif