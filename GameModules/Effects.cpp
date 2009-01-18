#include "Effects.h"

using namespace core;

Effects::Effects(){}

void Effects::addEffect(std::wstring wsName, double dValue){
	m_info.insert(std::make_pair<std::wstring,double>(wsName,dValue));
}

std::map<std::wstring, double> Effects::getEffects(){
	return m_info;
}

Effects::~Effects(void){}
