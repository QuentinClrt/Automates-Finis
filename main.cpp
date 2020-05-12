/**
 *
 * 	@mainpage 	Projet AUTOMATES - M. LE BERRE
 *
 *	@file 		main.cpp
 *	@author 	COLLART Quentin
 *
 *	@brief 		Projet intégralement en c permettant la manipulation d'automates.
 *	@details	Fichier principal. Utilisé pour effectuer les tests.
 *
*/

#include "algorithm.h"
using namespace std;


/**
 *	@brief Fonction d'affichage de l'aide.
 *
 *	@param int mode : type d'aide à afficher
 */
void help(int mode){

	cout << "Syntaxe : ./lanceur [0-3] [AUTOMATE1.txt AUTOMATE2.txt ...]" << endl << endl;

	if(mode == 1)
		cout << "\tVérifier le nombre d'arguments en paramètres." << endl << endl;

	if(mode == 2){
		cout << "---------------------------- 4 MODES possibles ---------------------------- " << endl << endl;
		cout << "\t0 : lecture d'une liste de mots par un automate (déterministe ou non)" << endl;
		cout << "\t1 : minimisation d'un automate déterministe" << endl;
		cout << "\t2 : déterminisation d'un automate" << endl;
		cout << "\t3 : suppression des e-transitions" << endl << endl << "---------------------------------------------------------------------------" << endl;
	}
	else if(mode == 3)
		cout << "\tVérifier les arguments en paramètres." << endl << endl;

	if(mode != 2)
		cout << "HELP : './lanceur help' " << endl;

	return;
}


/**
 *	MAIN FUNCTION
 *
 *	@brief La fonction main contient le choix des modes et la gestion des arguments.
 *	@param int argc, char **argv
 *
 *	@details retour 0 : OK, retour 1 : erreur mode 0, retour 2 : erreur mode 1, retour 3 : erreur mode 2, retour 4 : erreur mode 3, retour 5 : problème de syntaxe/argument
 */
int main(int argc, char * argv[]){

	if(argc < 2){
		help(1);
		return 1;
	}
	else{

		//Modes
		if(argv[1][0] == '0'){

			cout << "Mode 0 : Lecture d'une liste de mots par un automate (AFD | AFN)" << endl << endl;

			if(argc == 5){

				//Génération de l'automate fini
				CAutomate automate = create_FA(string(argv[2]));

				//Vérification de l'acceptation du mot
				if(!verify_wordlist(automate, string(argv[3]), string(argv[4])))
					return 1;
				else
					cout << "Fichier créé avec succès.";
			
			}
			else{
				cerr << "Vérifier les arguments." << endl;
				return 5;
			}
		}
		else if(argv[1][0] == '1'){
			cout << "Mode 1 : Minimisation d'un AFD" << endl << endl;
			if(argc == 4){

				//Lecture de l'automate déterministe fini
				CAutomate automate = create_FA(string(argv[2]));

				//Minimisation de l'automate
				CAutomate automate_minimized = minimize(automate);

				//Ecriture de l'automate minimisé
				if(!write_automate(automate_minimized, string(argv[3]))){
					cerr << "Erreur lors de l'écriture du nouvel automate." << endl;
					return 3;
				}
				else
					cout << "Fichier créé avec succès.";
			}
			else{
				cerr << "Vérifier les arguments." << endl;
				return 5;
			}
		}
		else if(argv[1][0] == '2'){
			cout << "Mode 2 : Déterminisation d'un AFN" << endl << endl;
			if(argc == 4){

				//Lecture automate fini
				CAutomate automate = create_FA(string(argv[2]));

				//======================= DEBUG =======================

				#ifdef DEBUG
				cout << "==================== AUTOMATE ====================" << endl;
				cout << endl << "\tNombre d'états : " << automate.get_number_state() << endl;
				cout << "\tAlphabet : ";
				for (auto it = automate.get_alphabet().cbegin(); it != automate.get_alphabet().cend(); it++)
					cout << *it << ", ";
				cout << endl << endl << endl;

				cout << "Etats composant l'automate :" << endl << endl;

				CState * test = automate.get_states(), test2;

				CTransition * test3, test4;

				for(int i=0; i < automate.get_number_state(); i++){
					test2 = test[i];
					cout << "---------------------------------------" <<endl;
					cout << "\tID Etat : " << test2.get_id_state() << endl << endl;
					cout << "Etat départ : " << test2.get_id_start_state() << endl;
					cout << "Etat final : " << test2.get_id_final_state() << endl;
					cout << endl << "Nombre de transitions : " << test2.get_transitions_number() << " ---->" << endl << endl;

					test3 = test2.get_transitions();
					for(int j=0; j < test2.get_transitions_number(); j++){
						cout << "Transition " << j << endl;
						cout << "Etiquette : " << test3[j].get_tag() << endl;
						cout << "Vers -> " << test3[j].get_id_to_state() << endl << endl;
					}
				}
				cout << "=================================================" << endl << endl;
				#endif

				//===================================================

				//Déterminisation
				CAutomate automate_deterministic = determinize(automate);

				//Ecriture de l'automate déterministe dans le fichier de sortie
				if(!write_automate(automate_deterministic, argv[3])){
					cerr << "Erreur lors de l'écriture du nouvel automate." << endl;
					return 3;
				}
				else
					cout << "Fichier créé avec succès.";
			}
			else{
				cerr << "Vérifier les arguments." << endl;
				return 5;
			}
		}
		else if(argv[1][0] == '3'){
			cout << "Mode 3 : Suppression des E-Transitions" << endl << endl;
			if(argc == 4){
				cout << "Pas disponible pour le moment..." << endl;
			}
			else{
				cerr << "Vérifier les arguments." << endl;
				return 5;
			}
		}

		//Help
		else if(strcmp(argv[1], "help") == 0){
			help(2);
			return 5;
		}
		
		//Erreur dans les arguments
		else{
			help(3);
			return 5;
		}
	}

	cout << endl;
	return 0;
}