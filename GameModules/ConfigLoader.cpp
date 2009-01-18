#include "ConfigLoader.h"
using namespace core;

ConfigLoader::ConfigLoader(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();	

	if (bLoadOk){
		TiXmlElement* pElement = document.FirstChildElement("configuration");
		pElement = pElement->FirstChildElement("config");
		while(pElement != NULL){			
			std::string sAttribute = pElement->Attribute("type");
			std::string sValue = pElement->GetText();
			loadConfigurationFromXML(sAttribute,sValue);
			pElement = pElement->NextSiblingElement();			
		}		
	}
	else{
		outputDbgString(L"Failed to load configuration file");
		throw std::ios_base::failure("File " + sFile + " not found.");
	}
}

void ConfigLoader::localPoliciesLoader(LocalPolicies *pLocalPolicies){
	m_pLocalPolicies = pLocalPolicies;
	loadPoliciesFromXML(m_sPoliciesConfig);
}

void ConfigLoader::diplomacyLoader(Diplomacy* pDiplomacy){
	m_pDiplomacy = pDiplomacy;
	loadDiplomacyFromXML(m_sDiplomacyConfig);
}

void ConfigLoader::populationLoader(Population* pPopulation){
	m_pPopulation = pPopulation;
	loadPopulationFromXML(m_sPopulationConfig);
}

void ConfigLoader::treatiesLoader(){
	loadTreatiesFromXML(m_sTreatiesConfig);
}

void ConfigLoader::productionLoader(Production* pProduction){
	m_pProduction = pProduction;
	loadProductionFromXML(m_sProductionConfig);
}

void ConfigLoader::socialServicesLoader(SocialServices* pSocialServices){
	m_pSocialServices = pSocialServices;
	loadSocialServicesFromXML(m_sSociaServicesConfig);
}

void ConfigLoader::loadConfigurationFromXML(std::string sName, std::string sValue){
	if(sName == "production") m_sProductionConfig = sValue;
	else if(sName == "population") m_sPopulationConfig = sValue;
	else if(sName == "socialServices") m_sSociaServicesConfig = sValue;
	else if(sName == "diplomacy") m_sDiplomacyConfig = sValue;	
	else if(sName == "treaties") m_sTreatiesConfig = sValue;
	else if(sName == "policies") m_sPoliciesConfig = sValue;
}

void ConfigLoader::loadPoliciesFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sErrorDesc = document.ErrorDesc();

	double dMoney = -1;
	std::string sName("");
	std::string sDescription("");	

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("policiesList");
		pElement = pElement->FirstChildElement("policy");

		while(pElement != NULL){	
			sName = pElement->Attribute("name");
			pElement->QueryDoubleAttribute("money",&dMoney);
			sDescription = pElement->Attribute("description");		

			std::wstringstream ssName;
			ssName << sName.c_str();					
			std::wstringstream ssDescription;
			ssDescription << sDescription.c_str();
			PoliticalActivity* pPA = new PoliticalActivity(ssName.str(),ssDescription.str(),dMoney);

			std::string sType("");			
			double dValue = -1;
			double dInterval = -1;
			TiXmlElement* pChildren = pElement->FirstChildElement("requeriment");

			while(pChildren != NULL){
				sType = pChildren->Attribute("type");
				pChildren->QueryDoubleAttribute("value",&dValue);
				pChildren->QueryDoubleAttribute("interval",&dInterval);
				std::wstringstream ssType;
				ssType << sType.c_str();
				pPA->addRequeriment(ssType.str(),dValue,dInterval);

				pChildren = pChildren->NextSiblingElement("requeriment");
			}

			std::string sTypeE("");			
			double dValueE = -1;			
			pChildren = pElement->FirstChildElement("effect");

			while(pChildren != NULL){
				sTypeE = pChildren->Attribute("type");
				pChildren->QueryDoubleAttribute("value",&dValueE);				
				std::wstringstream ssTypeE;
				ssTypeE << sTypeE.c_str();
				pPA->addEffect(ssTypeE.str(),dValueE);
				pChildren = pChildren->NextSiblingElement("effect");
			}

			///////////////////////////////////////////////////////////////
			m_pLocalPolicies->addPolicy(pPA);			
			///////////////////////////////////////////////////////////////
			pElement = pElement->NextSiblingElement();
		}		
	}
}

void ConfigLoader::loadTreatiesFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sErrorDesc = document.ErrorDesc();

	std::string sCountry("");
	std::string sName("");
	std::string sDescription("");	

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("treatyList");
		pElement = pElement->FirstChildElement("treaty");

		while(pElement != NULL){	
			sName = pElement->Attribute("name");
			sCountry = pElement->Attribute("country");
			sDescription = pElement->Attribute("description");		

			std::wstringstream ssName;
			ssName << sName.c_str();
			std::wstringstream ssCountry;
			ssCountry << sCountry.c_str();		
			std::wstringstream ssDescription;
			ssDescription << sDescription.c_str();
			PoliticalActivity* pPA = new PoliticalActivity(ssName.str(),ssDescription.str());

			std::string sType("");			
			double dValue = -1;
			double dInterval = -1;
			TiXmlElement* pChildren = pElement->FirstChildElement("requeriment");

			while(pChildren != NULL){
				sType = pChildren->Attribute("type");
				pChildren->QueryDoubleAttribute("value",&dValue);
				pChildren->QueryDoubleAttribute("interval",&dInterval);
				std::wstringstream ssType;
				ssType << sType.c_str();
				pPA->addRequeriment(ssType.str(),dValue,dInterval);

				pChildren = pChildren->NextSiblingElement("requeriment");
			}

			std::string sTypeE("");			
			double dValueE = -1;			
			pChildren = pElement->FirstChildElement("effect");

			while(pChildren != NULL){
				sTypeE = pChildren->Attribute("type");
				pChildren->QueryDoubleAttribute("value",&dValueE);				
				std::wstringstream ssTypeE;
				ssTypeE << sTypeE.c_str();
				pPA->addEffect(ssTypeE.str(),dValueE);
				pChildren = pChildren->NextSiblingElement("effect");
			}

			///////////////////////////////////////////////////////////////
			if(sCountry == "england"){
				m_pDiplomacy->accesForeignCountry(ENGLAND)->addTreaty(pPA);
			}
			else if(sCountry == "usa"){
				m_pDiplomacy->accesForeignCountry(USA)->addTreaty(pPA);
			}
			else if(sCountry == "france"){
				m_pDiplomacy->accesForeignCountry(FRANCE)->addTreaty(pPA);
			}
			///////////////////////////////////////////////////////////////
			pElement = pElement->NextSiblingElement();
		}		
	}
}


void ConfigLoader::loadProductionFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sName("");									
	double dMoney = -1;	
	int iStorage= -1;
	double dNp= -1;
	double dCp= -1;				
	double dIi= -1;		
	int iMaxStorageCapacity= -1;
	double dMaxTotalProduct= -1;

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("production");
		pElement = pElement->FirstChildElement("product");		

		while(pElement != NULL){			
			sName = pElement->Attribute("name");	
			pElement->QueryDoubleAttribute("money",&dMoney);			
			pElement->QueryIntAttribute("storage",&iStorage);
			pElement->QueryDoubleAttribute("np",&dNp);
			pElement->QueryDoubleAttribute("cp",&dCp);
			pElement->QueryDoubleAttribute("ii",&dIi);
			pElement->QueryDoubleAttribute("maxTotalProduct",&dMaxTotalProduct);
			pElement->QueryIntAttribute("maxStorageCapacity",&iMaxStorageCapacity);

			addProduct(sName,"",dMoney,iStorage,dNp,dCp,dIi,iMaxStorageCapacity,dMaxTotalProduct);

			pElement = pElement->NextSiblingElement();	
			//Resetear valores
			sName = "";								
			dMoney = -1;	
			iStorage= -1;
			dNp= -1;
			dCp= -1;				
			dIi= -1;		
			iMaxStorageCapacity= -1;
			dMaxTotalProduct= -1;
		}		
	}
	else{ 
		outputDbgString(L"Failed to load configuration file");
		throw std::ios_base::failure("Failed to load configuration file. File " + sFile + " not found.");
	}
}

void ConfigLoader::loadSocialServicesFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sName("");									
	double dSalaryOP= -1;	
	double dResourcesExpensesOP= -1;
	double dPersonalImportance= -1;				
	double dResourcesImportance= -1;

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("socialServices");
		pElement = pElement->FirstChildElement("socialService");		

		while(pElement != NULL){			
			sName = pElement->Attribute("name");	
			pElement->QueryDoubleAttribute("salaryop",&dSalaryOP);			
			pElement->QueryDoubleAttribute("resourcesop",&dResourcesExpensesOP);
			pElement->QueryDoubleAttribute("personalImportance",&dPersonalImportance);
			pElement->QueryDoubleAttribute("resourcesImportance",&dResourcesImportance);			

			addSocialService(sName,"",dSalaryOP,dResourcesExpensesOP,dPersonalImportance,dResourcesImportance);

			pElement = pElement->NextSiblingElement();		
			//Resetear valores
			sName="";									
			dSalaryOP= -1;	
			dResourcesExpensesOP= -1;
			dPersonalImportance= -1;				
			dResourcesImportance= -1;
		}		
	}
	else{
		outputDbgString(L"Failed to load  socialServices configuration file");
		throw std::ios_base::failure("Failed to load  socialServices configuration file. File " + sFile + " not found.");
	}
}
void ConfigLoader::loadPopulationFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sName("");
	double dSize = -1;
	double dPurchasingPower = -1;
	double dHealth = -1;
	double dEducation = -1;
	double dJustice = -1;
	double dFood = -1;
	double dEnergy = -1;
	double dManufactured = -1;

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("population");
		pElement = pElement->FirstChildElement("populationGroup");		

		while(pElement != NULL){			
			sName = pElement->Attribute("name");	
			pElement->QueryDoubleAttribute("size",&dSize);			
			pElement->QueryDoubleAttribute("purchasingPower",&dPurchasingPower);

			TiXmlElement* pChildren = pElement->FirstChildElement("opinion");
			while(pChildren != NULL){
				std::stringstream ss(pChildren->GetText());
				double dValue;
				ss >> dValue;
				std::string sType = pChildren->Attribute("type");				 
				if(sType == "health") dHealth = dValue;
				else if(sType == "education") dEducation = dValue;
				else if(sType == "justice") dJustice = dValue;
				else if(sType == "food") dFood = dValue;
				else if(sType == "energy") dEnergy = dValue;
				else if(sType == "manufactured") dManufactured = dValue;

				pChildren = pChildren->NextSiblingElement();				
			}
			addPopulationGroup(sName,dSize,dPurchasingPower,dHealth,dEducation,dJustice,dFood,dEnergy,dManufactured);
			//Resetear valores;
			sName = "";
			dSize = -1;
			dPurchasingPower = -1;
			dHealth = -1;
			dEducation = -1;
			dJustice = -1;
			dFood = -1;
			dEnergy = -1;
			dManufactured = -1;
			pElement = pElement->NextSiblingElement();			
		}		
	}
	else{
		outputDbgString(L"Failed to load configuration file");
		throw std::ios_base::failure("Failed to load configuration file. File " + sFile + " not found.");
	}
}

void ConfigLoader::loadDiplomacyFromXML(std::string sFile){
	TiXmlDocument document(sFile.c_str());
	bool bLoadOk = document.LoadFile();
	std::string sName("");									
	double dProductionOpinion= -1;	
	double dSocialServicesOpinion= -1;
	double dPopulationOpinion= -1;					

	if (bLoadOk){		
		TiXmlElement* pElement = document.FirstChildElement("diplomacy");
		pElement = pElement->FirstChildElement("foreignCountry");		

		while(pElement != NULL){			
			sName = pElement->Attribute("name");	
			pElement->QueryDoubleAttribute("production",&dProductionOpinion);			
			pElement->QueryDoubleAttribute("ssss",&dSocialServicesOpinion);
			pElement->QueryDoubleAttribute("population",&dPopulationOpinion);				

			addForeignCountry(sName,dProductionOpinion,dSocialServicesOpinion,dPopulationOpinion);			

			pElement = pElement->NextSiblingElement();		
			//Resetear valores
			sName="";									
			dProductionOpinion= -1;	
			dSocialServicesOpinion= -1;							
			dPopulationOpinion= -1;
		}		
	}
	else{
		outputDbgString(L"Failed to load  diplomacy configuration file");
		throw std::ios_base::failure("Failed to load  diplomacy configuration file. File " + sFile + " not found.");
	}
}

void ConfigLoader::addForeignCountry(std::string sName, double dProductionOpinion, double dSocialServicesOpinion, double dPopulationOpinion){
	if(dProductionOpinion >= 0 && dSocialServicesOpinion >= 0 && dPopulationOpinion >= 0){
		std::wstringstream ss;
		ss << sName.c_str();
		ForeignCountry* fc = new ForeignCountry(ss.str().c_str(),dProductionOpinion,dSocialServicesOpinion,dPopulationOpinion);
		m_pDiplomacy->addForeignCountry(fc);
	}
	else{
		outputDbgString(L"Bad foreignCountry data");
		throw std::ios_base::failure("Malformed foreignCountry" + sName);
	}	
}

void ConfigLoader::addPopulationGroup(std::string ID, double dSize, double dPurchasingPower, double dHealthCareOpinion, double dEducationOpinion, double dJusticeOpinion, double dFoodStuffOpinion, double dEnergyConsumptionOpinion, double dManufacturedProductOpinion){
	if(dSize >= 0 && 
		dPurchasingPower >= 0 && 
		dHealthCareOpinion  >= 0 && 
		dEducationOpinion >= 0 && 
		dJusticeOpinion >= 0 &&
		dFoodStuffOpinion >= 0 &&
		dEnergyConsumptionOpinion >= 0 &&
		dManufacturedProductOpinion >= 0){
			std::wstringstream ss;
			ss << ID.c_str();
			PopulationGroup* populationGroup = new PopulationGroup(ss.str().c_str(),dSize,dPurchasingPower,dHealthCareOpinion,dEducationOpinion,dJusticeOpinion,dFoodStuffOpinion,dEnergyConsumptionOpinion,dManufacturedProductOpinion);
			m_pPopulation->addPopulationGroup(populationGroup);
	}
	else{
		outputDbgString(L"Bad population group data");
		throw std::ios_base::failure("Malformed population group:" + ID);
	}
}

void ConfigLoader::addProduct(std::string sName,
							  std::string sDescription,											  
							  double dMoney,		
							  int iStorage,
							  double dNp,
							  double dCp,				
							  double dIi,		
							  int iMaxStorageCapacity,
							  double dMaxTotalProduct){

								  if(dMoney>= 0 &&		
									  iStorage >= 0 &&
									  dNp >= 0 &&
									  dCp >= 0 &&				
									  dIi >= 0 &&		
									  iMaxStorageCapacity >= 0 &&
									  dMaxTotalProduct >= 0){

										  std::wstringstream ss;
										  ss << sName.c_str();
										  Product* product = new Product(ss.str().c_str(),dMoney,iStorage,dNp,dCp,dIi,iMaxStorageCapacity,dMaxTotalProduct);
										  m_pProduction->addProduct(product);
								  }
								  else{
									  outputDbgString(L"Bad product data");
									  throw std::ios_base::failure("Malformed product" + sName);
								  }
}

void ConfigLoader::addSocialService(std::string sName, std::string wsDescription, double dSalaryOP, double dResourcesExpensesOP, double dPersonalImportance, double dResourcesImportance){
	if(dSalaryOP >= 0 && dResourcesExpensesOP >= 0 && dPersonalImportance >= 0 && dResourcesImportance >= 0){
		std::wstringstream ss;
		ss << sName.c_str();
		SocialService* socialService = new SocialService(ss.str().c_str(),L"",dSalaryOP,dResourcesExpensesOP,dPersonalImportance,dResourcesImportance);
		m_pSocialServices->addSocialService(socialService);
	}
	else{
		outputDbgString(L"Bad socialService data");
		throw std::ios_base::failure("Malformed socialService" + sName);
	}
}


ConfigLoader::~ConfigLoader(){}
