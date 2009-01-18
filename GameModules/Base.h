#ifndef _BASE_H_
#define _BASE_H_

#include <string>

namespace core{

	typedef const int productID;
	typedef const int populationGroupID;
	typedef const int socialServiceID;
	typedef const int foreignCountryID;

	static productID ALL_PRODUCTS = -1;
	static productID FOOD = 0;
	static productID ENERGY = 1;
	static productID MANUFACTURED = 2;

	static populationGroupID ALL_GROUPS = -1;
	static populationGroupID CONSERVATIVES = 0;
	static populationGroupID MERCHANTS = 1;
	static populationGroupID ULTRADEMOCRATS = 1;
	static populationGroupID AISLANDERS = 3;
	static populationGroupID GREENS = 4;

	static socialServiceID ALL_SERVICES = -1;
	static socialServiceID HEALTHCARE = 0;
	static socialServiceID EDUCATION = 1;
	static socialServiceID JUSTICE = 2;

	static foreignCountryID ALL_COUNTRIES = -1;
	static foreignCountryID ENGLAND = 0;
	static foreignCountryID FRANCE = 1;
	static foreignCountryID USA = 2;

	static const double NOT_FOUND = -20000;

//#define outputDbgString(x) void(0)
	void outputDbgString(std::wstring wsDebugString);
//#define boundaryCheck(down, top, x) ((x) < (down)? (down) : (x) > (top)? (top) : (x))
	double boundaryCheck(double dDown, double dUp, double dVar); 
};

#endif