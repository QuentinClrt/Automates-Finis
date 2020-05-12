#ifndef __AUTOMATE_H__
#define __AUTOMATE_H__

/**
 *
 *	@file 		automate.h
 *	@author		COLLART Quentin
 *	@version	1.0
 *	@date		12-04-2020
 *	@brief		Ce fichier contient toutes les fonctions et structures nécessaires pour la simulation d'automates.
 *	@details	Automates finis, déterministes, E-automates...
 *
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;


//macros
#define TRANSITIONS_MAX 15 /**< Nombre maximum de transitions.*/
#define STATES_MAX 20 /**< Nombre maximum d'états.*/



#define DEBUG /**< COMMENT THIS LINE TO ENTER INTO THE DEBUG MODE. */



/**
 *
 * Classe représentant une transition.
 *
*/
class CTransition {

	protected :

		//Membres
		char m_tag; /**< Etiquette. */
		int m_id_to_state; /**< ID de l'état vers lequel la transition va. */

	//Méthodes
	public :

		CTransition();
		CTransition(char tag, int id_to_state);
		virtual ~CTransition();

		//Getters/setters
		char get_tag();
		int get_id_to_state();

		//Fonctions
		void set_tag(int tag);
		void set_id_to_state(int id_to_state);
};


/**
 *
 * Classe représentant un état.
 *
*/
class CState {

	protected :

		//Membres
		int m_id_state; /**< ID état. */
		int m_id_start_state; /**< 1 si initial, 0 sinon. */
		int m_id_final_state; /**< 1 si acceptant, 0 sinon. */

		int m_transitions_number; /**< Nombre de transitions que possède l'état. */

		CTransition * m_transitions; /**< Transitions. */

	//Méthodes
	public :
		CState();
		CState(int id_state, int id_start_state, int id_final_state);
		virtual ~CState();

		//Getters/setters
		int get_id_state();
		int get_id_start_state();
		int get_id_final_state();
		int get_transitions_number();
		CTransition * get_transitions();

		//Fonctions
		void set_id_state(int id_state);
		void set_id_start_state(int id_start_state);
		void set_id_final_state(int id_final_state);
		void set_transitions_number(int transitions_number);
		void set_transitions(CTransition * transitions);
};


/**
 *
 * Classe représentant un automate.
 *
*/
class CAutomate {

	protected :

		//Membres
		int m_number_state; /**< Nombre d'états que contient l'automate. */
		vector<char> m_alphabet; /**< Alphabet de l'automate. */

		CState * m_states; /**< Liste de tous les états de l'automate. */

	//Méthodes
	public :

		CAutomate();
		CAutomate(int number_state);
		virtual ~CAutomate();

		//Getters/setters
		int get_number_state();
		vector<char>& get_alphabet();
		CState * get_states();

		//Fonctions
		void set_number_state(int number_state);
		void set_alphabet(vector<char> alphabet);
		void set_states(CState * states);
};

#endif
