#include "Requeriments.h"

using namespace core;

Requeriments::Requeriments(){
	m_bFirstCut = false;	
}

void Requeriments::addRequeriment(std::wstring wsName, double dValue, double dInterval){	
	ReqValue values = {dValue, dInterval};
	m_info.insert(std::make_pair<std::wstring,ReqValue>(wsName,values));
}


std::map<std::wstring, ReqValue> Requeriments::getRequeriments(){
	return m_info;
}

Requeriments::~Requeriments(){}
