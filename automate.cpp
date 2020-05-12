#include "automate.h"

/**
 *
 *	@file 		automate.cpp
 *	@author 	COLLART Quentin
 *	@brief 		Ce fichier contient toutes les fonctions déclarées dans le fichier 'automates.h'.
 *
 */


	//Constructeurs et destructeur

//classe Transition
CTransition::CTransition(){
	m_tag = 'a';
	m_id_to_state = -1;
}

CTransition::CTransition(char tag, int id_to_state){
	m_tag = tag;
	m_id_to_state = id_to_state;
}

CTransition::~CTransition(){
}

//classe State
CState::CState(){
	m_id_state = -1;
	m_id_start_state = -1;
	m_id_final_state = -1;
	m_transitions_number = 0;
}

CState::CState(int id_state, int id_start_state, int id_final_state){
	m_id_state = id_state;
	m_id_start_state = id_start_state;
	m_id_final_state = id_final_state;
}

CState::~CState(){
}

//classe Automate
CAutomate::CAutomate(){
	m_number_state = 0;
}

CAutomate::CAutomate(int number_state){
	m_number_state = number_state;
}

CAutomate::~CAutomate(){
}

	//Getters

//classe Transition
char CTransition::get_tag(){
	return m_tag;
}
int CTransition::get_id_to_state(){
	return m_id_to_state;
}

//classe State
int CState::get_id_state(){
	return m_id_state;
}
int CState::get_id_start_state(){
	return m_id_start_state;
}
int CState::get_id_final_state(){
	return m_id_final_state;
}
int CState::get_transitions_number(){
	return m_transitions_number;
}
CTransition * CState::get_transitions(){
	return m_transitions;
}

//classe Automate
int CAutomate::get_number_state(){
	return m_number_state;
}
vector<char>& CAutomate::get_alphabet(){
	return m_alphabet;
}
CState * CAutomate::get_states(){
	return m_states;
}


	//Setters

//classe Transition
void CTransition::set_tag(int tag){
	m_tag = tag;
	return;
}
void CTransition::set_id_to_state(int id_to_state){
	m_id_to_state = id_to_state;
	return;
}

//classe State
void CState::set_id_state(int id_state){
	m_id_state = id_state;
	return;
}
void CState::set_id_start_state(int id_start_state){
	m_id_start_state = id_start_state;
	return;
}
void CState::set_id_final_state(int id_final_state){
	m_id_final_state = id_final_state;
	return;
}
void CState::set_transitions_number(int transitions_number){
	m_transitions_number = transitions_number;
	return;
}
void CState::set_transitions(CTransition * transitions){
	m_transitions = transitions;
	return;
}

//classe Automate
void CAutomate::set_number_state(int number_state){
	m_number_state = number_state;
	return;
}
void CAutomate::set_alphabet(vector<char> alphabet){
	m_alphabet = alphabet;
	return;
}
void CAutomate::set_states(CState * states){
	m_states = states;
	return;
}