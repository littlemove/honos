#ifndef _SOCIAL_SERVICE_H_
#define _SOCIAL_SERVICE_H_

#include "Base.h"
#include <string>

namespace core{

	struct SocialServiceState{
		double dPersonal;
		double dResources;
		double dSalary;
		double dResourcesCost;
		double dSalaryOP;
		double dResourcesExpensesOP;
		double dPersonalImportance;
		double dResourcesImportance;
		double dTurnSalaryExpenses;
		double dTurnResourcesExpenses;
		double dTurnPersonalProductivity;
		double dTurnResourcesProductivity;
		double dServiceQuality;
	};

	/**
	* Esta clase modela un servicios social: cuenta con un personal y unos recursos que hay que mantener con dinero estatal. El estado 
	* e improtancia de ambos determian la calidad del servicio en un turno dado.
	*/
	class SocialService{

	public:
		/**
		* Constructor de SocialService.
		* @param pwcName nombre del servicio.
		* @param pwcDescription descripción del servicio.
		* @param dSalaryOP gasto óptimo en salarios.
		* @param dResourcesExpensesOP gasto óptimo en recursos materiales.
		* @param dPersonalImportance porcentaje de importancia que supone el personal para el servicio.
		* @param dResourcesImportance porcentaje de importancia que suponen los recursos materiales para el servicio.
		*/
		SocialService(const wchar_t* pwcName,
			const wchar_t* pwcDescription,
			double dSalaryOP,
			double dResourcesExpensesOP,
			double dPersonalImportance,
			double dResourcesImportance);

		/**
		* Devuelve el estado de SociaService.
		* @return SocialServiceState estructura con el estado de SocialService.
		*/
		SocialServiceState getState() const;

		/**
		* Calcula los gastos en salarios de un turno que tendrá en el estado actual (para obtener un valor que sea humanamente entendible hay que 
		* multiplicar el resultado por el tamaño de población).
		* @return double gastos en salarios.
		*/
		double calculateSalaryExpenses() const;

		/**
		* Calcula los gastos en un turno que tendrá en el estado actual (para obtener un valor que sea humanamente entendible hay que 
		* multiplicar el resultado por el tamaño de población).
		* @return double gastos en recursos.
		*/
		double calculateResourcesExpenses() const;

		/**
		* Calcula la calidad del servicio en el estado actual.
		* @return double [0,1] siendo 1-> sinónimo de lamejro calidad.
		*/
		double calculateServiceQuality() const;

		/**
		* Modifica el porcentaje del salario óptimo que está recibiendo el personal.
		* @param dIndex double [0,1] siendo 1-> 100% del salario óptimo.
		*/
		void setSalary(double dIndex);

		/**
		* Modifica el porcentaje del gasto óptimo que están recibiendo ls recursos.
		* @param dIndex double [0,1] siendo 1-> 100% del gasto óptimo.
		*/
		void setResourcesCost(double dIndex);
		
		/**
		* Asigna un valor a una propiedad del objeto especificada (si existe).
		* @param wsName nombre de la propiedad.
		* @param dValue valor a asignar.
		*/
		void setProperty(std::wstring wsName, double dValue);
		
		/**
		* Modifica el porcentaje de personal asignado al servicio.
		* @param dValue double [0,1] siendo 1-> 100% del personal óptimo.
		*/
		void setPersonal(double dValue);

		/**
		* Modifica el porcentaje de recursos asignado al servicio.
		* @param dValue double [0,1] siendo 1-> 100% de recursos óptimo.
		*/
		void setResources(double dValue);

		/**
		* Actualiza para avanzar al siguiente turno.
		*/
		void update();

		std::wstring toString() const;
		
		/**
		* Destructor.
		*/
		~SocialService();

	private:
		SocialServiceState m_state;
		std::wstring m_wsName;
		std::wstring m_wsDescription;

		double m_dPersonal;
		double m_dSalary;
		double m_dSalaryOP;
		double m_dPersonalImportance;
		double m_dPersonalOP;

		double m_dResources;
		double m_dResourcesCost;
		double m_dResourcesExpensesOP;	
		double m_dResourcesImportance;	
		double m_dResourcesOP;

		double calculateResourcesProductivity() const;
		double calculatePersonalProductivity() const;
		void saveState();
	};

}
#endif