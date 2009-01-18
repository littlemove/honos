#ifndef _CONFIG_LOADER_H_
#define _CONFIG_LOADER_H_

#include <string>
#include <ios>
#include "Population.h"
#include "PopulationGroup.h"
#include "SocialService.h"
#include "Product.h"
#include "Production.h"
#include "SocialServices.h"
#include "Population.h"
#include "PoliticalActivity.h"
#include "Diplomacy.h"
#include "LocalPolicies.h"
#include "../libs/tinyxml/tinyxml/tinyxml.h"

namespace core{
	/**
	* Esta clase permite procesar ficheros de configuración XML para cargar los diferentes datos de la partida. Hace uso de la biblioteca
	* TinyXML para "parsear" el código.
	*/
	class ConfigLoader{

	public:
		/**
		* Lee del fichero de configuración las rutas a los ficheros XML con los recursos.
		* @param sFile ruta del fichero de configuración.
		*/
		ConfigLoader(std::string sFile) throw(std::ios_base::failure);
		
		/**
		* Carga un objeto de tipo Population con datos de partida.
		* @param pPopulation puntero a un objeto de tipo Population.
		*/
		void populationLoader(Population* pPopulation);

		/**
		* Carga un objeto de tipo Production con datos de partida.
		* @param pPopulation puntero a un objeto de tipo Population.
		*/
		void productionLoader(Production* pProduction);

		/**
		* Carga un objeto de tipo SocialServices con datos de partida.
		* @param pSocialServices puntero a un objeto de tipo SocialServices.
		*/
		void socialServicesLoader(SocialServices* pSocialServices);
		
		/**
		* Carga un objeto de tipo LocalPolicies con datos de partida.
		* @param pDiplomacy puntero a un objeto de tipo Diplomacy.
		*/		
		void diplomacyLoader(Diplomacy* pDiplomacy);

		/**
		* Carga un objeto de tipo Diplomacy con datos de partida.
		* @param pLocalPolicies puntero a un objeto de tipo LocalPolicies.
		*/
		void localPoliciesLoader(LocalPolicies* pLocalPolicies);

		/**
		* Carga los tratados internacionales del fichero XML correspondiente.		
		*/
		void treatiesLoader();
		
		/**
		* Destructor.
		*/
		~ConfigLoader();

	private:
		Production* m_pProduction;
		Population* m_pPopulation;
		SocialServices* m_pSocialServices;
		Diplomacy* m_pDiplomacy;
		LocalPolicies* m_pLocalPolicies;

		std::string m_sPopulationConfig;
		std::string m_sProductionConfig;
		std::string m_sSociaServicesConfig;
		std::string m_sDiplomacyConfig;
		std::string m_sTreatiesConfig;
		std::string m_sPoliciesConfig;
		
		/**
		* Función de apoyo para cargar la configuración general a partir de fichero.
		* @param sName tipo de configuración.
		* @param sValue valor.
		*/
		void loadConfigurationFromXML(std::string sName, std::string sValue) throw(std::ios_base::failure);
		
		/**
		* Función de apoyo para cargar la configuración de la población a partir de fichero.
		* @param sFile ruta al fichero con la configuración de Population.		
		*/
		void loadPopulationFromXML(std::string sFile) throw(std::ios_base::failure);
		
		/**
		* Función de apoyo para cargar la configuración de la producción a partir de fichero.
		* @param sFile ruta al fichero con la configuración de Production.		
		*/
		void loadProductionFromXML(std::string sFile) throw(std::ios_base::failure);
		
		/**
		* Función de apoyo para cargar la configuración de los servicios sociales a partir de fichero.
		* @param sFile ruta al fichero con la configuración de SocialServices.		
		*/
		void loadSocialServicesFromXML(std::string sFile) throw(std::ios_base::failure);

		/**
		* Función de apoyo para cargar la configuración de los paises a partir de fichero.
		* @param sFile ruta al fichero con la configuración de paises.		
		*/
		void loadDiplomacyFromXML(std::string sFile) throw(std::ios_base::failure);

		/**
		* Función de apoyo para cargar la configuración de los tratados a partir de fichero.
		* @param sFile ruta al fichero con la configuración de los tratados.		
		*/
		void loadTreatiesFromXML(std::string sFile) throw(std::ios_base::failure);

		/**
		* Función de apoyo para cargar la configuración de las políticas a partir de fichero.
		* @param sFile ruta al fichero con la configuración de las políticas.		
		*/
		void loadPoliciesFromXML(std::string sFile) throw(std::ios_base::failure);

		/**
		* Función auxiliar. Inserta un requerimiento en un tratado.			
		*/
		void addRequeiment(std::string type,		
			double dValue,
			double dInterval) throw(std::ios_base::failure);
		
		/**
		* Función auxiliar. Crea un grupo de población a partir de los parámetros y lo inserta en Población.			
		*/
		void addPopulationGroup(std::string ID,
			double dSize,
			double dPurchasingPower,
			double dHealthCareOpinion,
			double dEducationOpinion,
			double dJusticeOpinion,
			double dFoodStuffOpinion,
			double dEnergyConsumptionOpinion,
			double dManufacturedProductOpinion) throw(std::ios_base::failure);

		/**
		* Función auxiliar. Crea un servicio social a partir de los parámetros y lo inserta en SocialServices.			
		*/
		void addSocialService(std::string sName,
			std::string wsDescription,
			double dSalaryOP,
			double dResourcesExpensesOP,
			double dPersonalImportance,
			double dResourcesImportance) throw(std::ios_base::failure);

		/**
		* Función auxiliar. Crea un producto a partir de los parámetros y lo inserta en Production.			
		*/
		void addProduct(std::string sName,
			std::string sDescription,							
			double dMoney,		
			int iStorage,
			double dNp,
			double dCp,				
			double dIi,		
			int iMaxStorageCapacity,
			double dMaxTotalProduct) throw(std::ios_base::failure);

		/**
		* Función auxiliar. Crea un servicio social a partir de los parámetros y lo inserta en SocialServices.			
		*/
		void addForeignCountry(std::string sName,			
			double dProductionOpinion,
			double dSocialServicesOpinion,
			double dPopulationOpinion) throw(std::ios_base::failure);
	};
}
#endif