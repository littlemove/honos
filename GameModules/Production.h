#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_

#include <vector>
#include "Product.h"
#include "Base.h"

namespace core{

	struct ProductionState{
		double dPPS;
		double dFoodPPS;
		double dEnergyPPS;
		double dManufacturedPPS;
		double dFoodPriceVariation;
		double dEnergyPriceVariation;
		double dManufacturedPriceVariation;

		ProductState foodState;
		ProductState energyState;
		ProductState manufacturedState;
	};

	/**
	* Esta clase modela la producción del país del jugador.
	*/
	class Production{

	public:
		/**
		* Cosntructor.
		*/
		Production();
		
		/**
		* Añade un producto pasado como parámetro a la producción.
		* @param pProduct puntero al producto a añadir.
		*/
		void addProduct(Product* pProduct);

		/**
		* Obtiene el estado actual de un producto dado.
		* @param ID identificador del producto.
		* @return ProductState estructura con el estado del producto.	
		*/
		ProductState getProductState(productID ID) const;

		/**
		* Modifica la subvención estatal de un producto.
		* @param ID identificador del producto.
		* @param dMoney cantidad de la subvención.
		*/
		void setStateMoney(productID ID, double dMoney);

		/**
		* Modifica los impuestos sobre un producto.
		* @param ID identificador del producto.
		* @param dTaxIndex [0,1) 0-> no hay impuestos | 0.5-> el impuesto es igual a la mitad del precio del producto.
		*/
		void setTax(productID ID, double dTaxIndex);
		
		/**
		* Asigna un valor a una propiedad del objeto especificada (si existe).
		* @param wsName nombre de la propiedad.
		* @param dValue valor a asignar.
		*/
		void setProperty(std::wstring wsName, double dValue);
		
		/**
		* Calcula la potencia de la producción para un tamaño de población dado.
		* @param dPopulationSize tamaño de la población.		
		*/
		void setPPS(double dPopulationSize);	
		
		/**
		* Modifica el consumo sobre un producto.
		* @param ID identificador del producto.
		* @param dConsumption [0,1) 0-> no hay consumo.
		*/
		void setConsumption(productID ID, double dConsumption);
		
		/**
		* Devuelve el estado de la clase.
		* @return ProductionState.
		*/
		ProductionState getState() const;
		
		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update();

		std::wstring toString() const;
		
		/**
		* Destructor.
		*/
		~Production();

	private:
		std::vector<Product*> m_productList;
		ProductionState m_state;
		double m_dPPS;
		double m_dFoodPPS;
		double m_dEnergyPPS;
		double m_dManufacturedPPS;

		double m_dFoodPriceVariation;
		double m_dEnergyPriceVariation;
		double m_dManufacturedPriceVariation;

		void saveState();
	};
}
#endif