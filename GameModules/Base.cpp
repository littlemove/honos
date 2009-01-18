#include "Base.h"
#include <iostream>

namespace core{

	void outputDbgString(std::wstring wsDebugString){
#ifdef _DEBUG
		std::wcout << "Warning!: " << wsDebugString << std::endl;
#endif
	}

	double boundaryCheck(double dDown, double dUp, double dVar){
		double dResult = dVar;

		if(dResult > dUp){
			dResult = dUp;
			outputDbgString(L"Up boundary exceed");
		}
		else if(dResult < dDown){
			dResult = dDown;
			outputDbgString(L"Down boundary exceed");
		}

		return dResult;

	}
}