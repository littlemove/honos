#ifndef _LOCAL_POLICIES_H
#define _LOCAL_POLICIES_H

#include <string>
#include <vector>
#include "Base.h"
#include "PoliticalActivity.h"

namespace core{
	
	/**
	* Esta clase modela las actividades políticas internas del país del jugador.
	*/
	class LocalPolicies{

	public:
		/**
		* Constructor.
		*/
		LocalPolicies();
		
		/**
		* Destructor.
		*/
		~LocalPolicies();

		/**
		* Añade una actividad política pasada como parámetro.
		* @param pPA puntero a PoliticalActivity
		*/
		void addPolicy(PoliticalActivity* pPA);

		/**
		* Devuelve un puntero al tratado selecionado actualmente.
		* @return puntero a PoliticalActivity
		*/
		PoliticalActivity* getCurrentTreaty();

		/**
		* Avanza m_pCurrentPolicyIter al siguiente tratado. Si no quedan más vuelve al inicio.
		*/
		void next();

		/**
		* Borra una política situada en la posición iPosition de la lista.
		* iPostion posición de la política a borrar.
		*/
		void deletePolicy(int iPosition);
		
		/**
		* Devuelve una lista con todas las políticas locales.		
		*/
		std::vector<PoliticalActivity*> m_policyList;

	private:
		std::vector<PoliticalActivity*>::iterator m_pCurrentPolicyIter;	
	};
}
#endif