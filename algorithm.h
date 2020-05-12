#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

/**
 *
 *	@file 		algorithm.h
 *	@author		COLLART Quentin
 *	@version	1.0
 *	@date		12-04-2020
 *	@brief		Ce fichier contient toutes les fonctions et structures nécessaires pour les applications d'automates.
 *	@details	Algorithme de Moore, déterminisation, suppression des E-Transitions...
 *
*/

#include "automate.h"
using namespace std;



/**
 *	@brief 		Fonction créeant un automate fini (déterministe ou non-déterministe)
 *	@details	L'automate est crée à partir du fichier en paramètre et utilise les classes d'automate.
 *	@param		file_name le nom du fichier générant décrivant l'automate.
 */
CAutomate create_FA(string file_name);


/**
 *	@brief	Détermine si le mot passé en paramètre peut etre obtenu à l'aide de l'automate aussi en paramètre
 *	@param 	automate issu de la classe CAutomate
 *	@param 	word le mot à tester sur l'automate
 */
int accepted_or_not(CAutomate automate, string word);


/**
 *	@brief fonction qui vérifie si les mots contenus dans le fichier en entrée appartiennent ou non à l'automate
 *	@param automate issu de la classe CAutomate
 *	@param i_file le nom du fichier en entrée (fichier de mot)
 *	@param o_file le nom du fichier en sortie (fichier affichant les résultats)
 */
int verify_wordlist(CAutomate automate, string i_file, string o_file);


/**
 *	@brief fonction qui écrit l'automate en paramètre dans le fichier nommé en paramètre
 *	@param automate à écrire dans le fichier
 *	@param fichier de sortie
 */
int write_automate(CAutomate automate, string o_file);


/**
 *	@brief fonction qui récupère l'automate déterministe passé en paramètre et retourne le minimisé de celui-ci
 *	@param automate_input est l'automate déterministe à minimiser
 *	@param o_file est le nom du fichier de sortie contenant l'automate minimisé
 */
CAutomate minimize(CAutomate automate_input);


/**
 *	@brief déterminise l'automate passé en paramètre
 *	@param automate_input est l'automate à déterminiser
 *	@param o_file est le nom du fichier de sortie contenant l'automate déterminisé
 */
CAutomate determinize(CAutomate automate_input);


#endif