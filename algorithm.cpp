#include "algorithm.h"

/**
 *
 *	@file 		algorithm.cpp
 *	@author 	COLLART Quentin
 *	@brief 		Ce fichier contient toutes les fonctions déclarées dans le fichier 'algorithm.h'.
 *
 */


/************************************************
 *		Fonctions pour le premier mode
 ************************************************/

CAutomate create_FA(string file_name){

	ifstream file(file_name);	//Fichier à ouvrir
	string line; 				//Ligne pointée par le getline
	int line_counter = 1;		//Compteur de lignes
	int id_state = 0;			//ID de l'état courant
	int transitions_to_add = 0; //Nombre de transitions à ajouter

	string output;

	CAutomate automate; 														//Init automate
	CState * states = new CState [STATES_MAX], state;							//Etats à attribuer à l'automate
	CTransition * transitions = new CTransition [TRANSITIONS_MAX], transition;	//Transitions à attribuer aux états

  	if(file.is_open()){

		//Lecture du fichier et récupération des données concernant l'automate
		while (getline(file, line)){
			
			//Alphabet
			if(line_counter == 1){

				vector<char> alphabet;

				for(int i=0; i < line.length(); i++)
					alphabet.push_back(line[i]);
				
				automate.set_alphabet(alphabet);
			}

			//Nombre d'états
			else if(line_counter == 2){
				int state_number = stoi(line);

				automate.set_number_state(state_number);
				states = new CState [state_number];
			}

			else{
				//On ajoute le nouvel état
				stringstream line_split(line);
				int init = 0, fin = 0;

				for(int i=0; line_split >> output; i++){
					if(i==0)
						init = stoi(output);
					if(i==1)
						fin = stoi(output);
				}
				states[id_state] = CState(id_state, init, fin);


				//On prépare le tableau de transitions
				getline(file, line);

				try{
					transitions_to_add = stoi(line);

					states[id_state].set_transitions_number(transitions_to_add);

					transitions = new CTransition [transitions_to_add];
				}
				catch (const std::exception& e) {
						cerr << "\tErreur survenue : " << e.what() << " à la ligne " << line_counter << " du fichier." << endl;
						return automate;
				}

				//On ajoute les transitions

				int id_transition = 0;
				for (int i=0; i < transitions_to_add; i++){
					getline(file, line);

					stringstream line_split3(line);
					int id_to_state = 0;
					char tag = 0;

					for(int j=0; line_split3 >> output; j++){
						if(j == 0)
							id_to_state = stoi(output);
						if(j == 1)
							tag = output[0];
					}

					transitions[id_transition] = CTransition(tag, id_to_state);

					id_transition += 1;
				}

				states[id_state].set_transitions(transitions);

				id_state += 1;
			}
			line_counter += 1;
		}

		//Ajout des états dans l'automate
		automate.set_states(states);

		file.close();
  	}

  	else
  		cerr << "Impossible d'ouvrir le fichier." << endl;

	return automate;
}


int accepted_or_not(CAutomate automate, string word){

	//On récupère les états initiaux et finaux
	vector<int> id_begin_state, id_final_state;

	CState * states = automate.get_states();

	for(int i=0; i < automate.get_number_state(); i++){
		if(states[i].get_id_start_state() == 1)
			id_begin_state.push_back(states[i].get_id_state());
		if(states[i].get_id_final_state() == 1)
			id_final_state.push_back(states[i].get_id_state());
	}

	if(id_begin_state.size() > 0 && id_final_state.size() > 0){

		//Puis vérification de chaque lettre du mot
		vector<int> id_queue = id_begin_state, tmp;
		
		for(int i=0; i < word.size(); i++){

			tmp = id_queue;
			id_queue.clear();

			for(int j=0; j < tmp.size(); j++){
				CState current_state = states[tmp[j]];

				CTransition * transitions = current_state.get_transitions();

				for(int k=0; k < current_state.get_transitions_number(); k++){
					CTransition transition = transitions[k];

					if(word[i] == transition.get_tag())
						id_queue.push_back(transition.get_id_to_state());
				}
			}

			if(id_queue.empty())
				return 0;
		}

		//Vérification si le dernier état est acceptant ou non
		for(int i=0; i < id_queue.size(); i++){
			if(states[id_queue[i]].get_id_final_state() == 1)
				return 1;
		}
	}

	return 0;
}


int verify_wordlist(CAutomate automate, string i_file, string o_file){

	ifstream input_file(i_file);
	ofstream output_file(o_file);

  	if((input_file.is_open())&&(output_file.is_open())){

  		vector<string> wordlist;
  		string line;

  		while (getline (input_file, line))
  			wordlist.push_back(line);

  		if(wordlist.size() > 0){
  			for(int i=0; i < wordlist.size(); i++){
  				if(accepted_or_not(automate, wordlist[i]) == 1)
  					output_file << "1" << endl;
  				else
  					output_file << "0" << endl;
  			}
  		}
  		else
  			cerr << "Fichier de mots vide." << endl;

  		input_file.close();
  		output_file.close();
  	}
  	else{
  		cerr << "Impossible d'ouvrir les fichiers." << endl;
  		return 0;
  	}

  	return 1;
}



/************************************************
 *		Fonctions pour le deuxième mode
 ************************************************/

int write_automate(CAutomate automate, string o_file){

	ofstream output_file(o_file);

	if(output_file.is_open()){

		for (auto it = automate.get_alphabet().cbegin(); it != automate.get_alphabet().cend(); it++)
			output_file << *it;

		output_file << endl;
		output_file << automate.get_number_state() << endl;

		CState * states = automate.get_states(), state;

		CTransition * transitions, transition;

		for(int i=0; i < automate.get_number_state(); i++){

			state = states[i];

			output_file << state.get_id_start_state() << " " << state.get_id_final_state() << endl;
			output_file << state.get_transitions_number() << endl;

			transitions = state.get_transitions();

			for(int j=0; j < state.get_transitions_number(); j++){
				transition = transitions[j];
				output_file << transition.get_id_to_state() << " " << transition.get_tag() << endl;
			}
		}

		output_file.close();
  	}
  	else{
  		cerr << "Impossible d'écrire dans le fichier." << endl;
  		return 0;
  	}

  	return 1;
}


CAutomate minimize(CAutomate automate_input){

	CAutomate input = automate_input, output;

	output.set_alphabet(automate_input.get_alphabet());

	CState * states = input.get_states();

	int nb_state = input.get_number_state();

	//On récupère les états finaux et initiaux
	vector<int> id_final_state, id_begin_state;

	for(int i=0; i < nb_state; i++){
		if(states[i].get_id_final_state() == 1)
			id_final_state.push_back(1);
		else
			id_final_state.push_back(0);

		if(states[i].get_id_start_state() == 1)
			id_begin_state.push_back(1);
		else
			id_begin_state.push_back(0);
	}

	//Récupération des ID correspondant aux transitions par une lettre
	vector<char> alphabet = output.get_alphabet();
	int nb_alpha = alphabet.size();
	int iter_alphab[nb_state][nb_alpha+1];
	
	for(int i=0; i < nb_state; i++){
		cout << i << " : ";
		for(int j=0; j < nb_alpha; j++){
			iter_alphab[i][j] = states[i].get_transitions()[j].get_id_to_state();
			cout << iter_alphab[i][j] << ", ";
		}
		cout << endl;
	}

	//Iteration 0
	vector<int> iter = id_final_state, tmp;
	cout << "~0 : ";
	for(int i=0; i < nb_state; i++)
		cout << iter[i] << ", ";

	cout <<endl;

	//Pré-remplissage des transitions
	int iter_class[nb_state][nb_alpha];

	for(int i=0; i < nb_state; i++){
		for(int j=0; j < nb_alpha; j++)
			iter_class[i][j] = iter[states[i].get_transitions()[j].get_id_to_state()];
	}


	//Pour chaque itération, on répète tant que l'itération actuelle n'est pas
	//égale à la prochaine (stabilité)
	cout << endl << "Minimisation jusqu'à stabilité..." << endl;
	int memory_1[nb_state];
	for(int iteration_number = 1, stable = 0; (!stable)&&(iteration_number < 50000); iteration_number++){

		int memory[nb_state];
		int current_class = 0;

		for(int i=0; i < nb_state; i++){

			memory[i] = -1;

			for(int j=0; (j<i)&&(memory[i] == -1); j++){

				memory[i] = iter_class[i][nb_alpha-1];

				for(int k=0; k < nb_alpha; k++){

					if(iter_class[i][k] != iter_class[j][k]){
						memory[i] = -1;
						break;
					}
				}

			}

			if(memory[i] == -1){
				memory[i] = current_class;
				current_class++;
			}
		}

		//Comparer ~n et ~n-1
		stable = 1;
		for(int i=0; i < nb_state; i++){
			if(memory_1[i] != memory[i])
				stable = 0;
		}

		for(int i=0; i < nb_state; i++){
			memory_1[i] = memory[i];
		}
	}

	//Second algorithme commencé et modifié après...
	//(principe du cours avec n-uplets).
	//  --> Pas assez concluant

	//=======================================================
	/*
	for(int iteration_number = 1; iter != tmp; iteration_number++){

		tmp = iter; //tmp = iter -1 -> minimise

		vector<vector<int>> iter_alphab(alphabet.size(), vector<int> (nb_state, 0));

		for(int i=0; i < alphabet.size(); i++){

			cout << endl << alphabet[i] << " : ";

			for(int j=0; j < nb_state; j++){

				iter_alphab[i][j] = iter[states[j].get_transitions()[i].get_id_to_state()];
				cout << iter_alphab[i][j] << ", ";
			}
		}

		//On rassemble les n-uplets

		int count;
		for(int i=0; i < nb_state; i++){

			count = 0;
			for(int j=0; j < alphabet.size(); j++){

				count += iter_alphab[i][j];
			}
			iter[i] = count;
		}

		cout << endl << "~" << iteration_number << " : ";
		for(int i=0; i < nb_state; i++)
			cout << iter[i] << ", ";

	}*/
	//===================================================================


	//Création de l'automate minimisé une fois que l'algorithme trouve stabilité
	
	//Nombre d'états
	int number_states = 0;
	for(int i=0; i < nb_state; i++){
		if(memory_1[i] > number_states)
			number_states = memory_1[i];
	}
	number_states +=1;

	output.set_number_state(number_states);

	//On récupère la dernière itération
	int iter_class2[nb_state][nb_alpha];

	for(int i=0; i < nb_state; i++){
		for(int j=0; j < nb_alpha; j++){

			iter_class2[i][j] = memory_1[states[i].get_transitions()[j].get_id_to_state()];
		}
	}


	//Ajout des états
	CState * states_to_add, state_to_add;
	CTransition * transitions, transition;
	int id_state = 0, id_transition;

	for(int i=0; i < number_states; i++){

		for(int k = 0; k < nb_state; k++){
			if(memory_1[k] == i){
				//Etats
				state_to_add = CState(i, id_begin_state[k], id_final_state[k]);
				if(i==0) state_to_add.set_id_start_state(1);
				state_to_add.set_transitions_number(nb_alpha);
				states_to_add[i] = state_to_add;
				
				//Transitions
				transitions = new CTransition [nb_alpha];
				for(int j=0; j < nb_alpha; j++){
					CTransition transition(alphabet[j], iter_class2[k][j]);

					transitions[j] = transition;
				}
				states_to_add[i].set_transitions(transitions);
			}
		}
	}

	output.set_states(states_to_add);

	return output;
}


/************************************************
 *		Fonctions pour le troisième mode
 ************************************************/

CAutomate determinize(CAutomate automate_input){

	CAutomate input = automate_input, output;

	//Préparation de l'automate de sortie
	output.set_alphabet(input.get_alphabet()); //L'alphabet ne change pas
	int nb_alpha = input.get_alphabet().size();

	vector<char> alphabet = output.get_alphabet();

	//On récupère les états initiaux et finaux dés le départ pour vérifier
	//à la fin la composition des états de l'automate
	vector<int> start_states, final_states;

	CState * states = automate_input.get_states();

	for(int i=0; i < automate_input.get_number_state(); i++){

		if(states[i].get_id_start_state() == 1)
			start_states.push_back(states[i].get_id_state());

		if(states[i].get_id_final_state() == 1)
			final_states.push_back(states[i].get_id_state());
	}

	cout << "Start states : ";
	for(auto it = start_states.cbegin(); it != start_states.cend(); it++){
		cout << *it << ", ";
	}
	cout << endl;

		cout << "Final states : ";
	for(auto it = final_states.cbegin(); it != final_states.cend(); it++){
		cout << *it << ", ";
	}
	cout << endl;


	//...puis on les ajoute au tableau d'état courant en fusionnant leurs transitions...
	CState * states_to_add = new CState [STATES_MAX], state_to_add, current_state;
	CTransition * transitions = new CTransition[nb_alpha], transition, * transitions_tmp = new CTransition[TRANSITIONS_MAX];

	int id_state = 1, id_transition = 0, flag_start = 1, flag_final = 0;

	//Etat de départ (combiné de tous les états initiaux)
	stringstream ss;
	copy(start_states.begin(), start_states.end(), ostream_iterator<int>(ss, ""));
	string str_id_begin_state = ss.str();
	int id_begin_state = stoi(str_id_begin_state);
	cout << "ID de l'état de départ : " << id_begin_state << endl;

	//On prépare les transitions de l'état de départ
	vector<string> ids_to_state(nb_alpha, "");
	
	for(int i=0; i < start_states.size(); i++){

		current_state = states[start_states[i]];

		if(current_state.get_id_final_state())
			flag_final = 1;


		transitions_tmp = current_state.get_transitions();

		for(int j=0; j < current_state.get_transitions_number(); j++){

			for(int l=0; l < nb_alpha; l++){
				if(alphabet[l] == transitions_tmp[j].get_tag())
					ids_to_state[l] += to_string(transitions_tmp[j].get_id_to_state());
			}
		}
	}

	for(int i=0; i < nb_alpha; i++){
		transition = CTransition(alphabet[i], stoi(ids_to_state[i]));
		transitions[i] = transition;
	}

	state_to_add = CState(id_begin_state, flag_start, flag_final);
	state_to_add.set_transitions_number(nb_alpha);
	state_to_add.set_transitions(transitions);

	states_to_add[0] = state_to_add;
	
	//PUIS. On récupère chaque ID d'états conjoints pour obtenir sa dérivation
	//on rassemble les transitions de même étiquette et on crée les nouvelles transitions pour CHAQUE lettre
	//de l'alphabet (l'automate final est donc déterministe complet).
	//JUSQU'A CE QUE LA QUEUE SOIT VIDE (PLUS D'ETATS RESTANTS)
	/*
	
	//On récupère le prochain ID généré
	for(int i=0; i < nb_alpha; i++)
		queue.push_back(state_to_add.get_transitions()[i].get_id_to_state());
	
	//On effectue le traitement sous forme de dérivation. jusqu'à ce que la queue soit vide.
	while(!queue.empty()){

		flag_start = flag_final = 0;

		//On traite la queue pour créer l'état actuel
		for(int i=0; i < queue.size(); i++){

			current_state = states[queue[i]];
			cout << current_state.get_transitions_number() << endl;

			transitions = new CTransition [nb_alpha];

			for(int j=0; j < nb_alpha; j++){
				transitions[id_transition] = CTransition(alphabet[j], -1);
			}

			id_transition = 0;
			for(int j=0; j < current_state.get_transitions_number(); j++){

				if(current_state.get_id_start_state() == 1)
					flag_start = 1;
				if(current_state.get_id_final_state() == 1)
					flag_final = 1;

				transitions[id_transition] = current_state.get_transitions()[j];

				id_transition += 1;
			}
		}

		//..création de l'état courant
		state_to_add = CState(id_state, flag_start, flag_final);
		state_to_add.set_transitions_number(id_transition);
		state_to_add.set_transitions(transitions);
		states_to_add[id_state] = state_to_add;

		//Préparation de la nouvelle file contenant les prochains états
		queue.clear();
		//Attribution de la file suivante
		//...

		id_state += 1;
	}
	
	//Attribution des états finaux
	//...
	*/

	//Attribution des états à l'automate
	output.set_number_state(id_state);
	output.set_states(states_to_add);


	//================= DEBUG
	#ifdef DEBUG
	cout << endl << "Nb d'états de l'automate : " << output.get_number_state() << endl;
	cout << "Alphabet : ";
	for (auto it = output.get_alphabet().cbegin(); it != output.get_alphabet().cend(); it++)
		cout << *it << ", ";
	cout << endl << endl;

	cout << "Etats de l'automate: " << endl << endl;

	CState * test = output.get_states(), test2;

	CTransition * test3, test4;

	for(int i=0; i < output.get_number_state(); i++){
		test2 = test[i];
		cout << "-----------------------------" <<endl;
		cout << "ID Etat : " << test2.get_id_state() << endl;
		cout << "Etat départ : " << test2.get_id_start_state() << endl;
		cout << "Etat final : " << test2.get_id_final_state() << endl;
		cout << "Nombre de transitions : " << test2.get_transitions_number() << endl << endl;

		test3 = test2.get_transitions();
		for(int j=0; j < test2.get_transitions_number(); j++){
			cout << "Transition " << j << endl;
			cout << "Etiquette : " << test3[j].get_tag() << endl;
			cout << "Vers -> " << test3[j].get_id_to_state() << endl << endl;
		}
	}
	cout << "-----------------------------" << endl <<endl;
	#endif
	//===================================================================


	return output;
}