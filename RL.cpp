#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include <algorithm>  
using namespace std;

const int MISSILE = 0;
const int FIREBALL = 1;
const int DAGGER = 2;
const int STAFF = 3;
const int GLOBE = 4;
const int STONESKIN = 5;
const int STRENGTH = 6;
const int HEAL = 7;

// number of rounds for game
int rounds = 0;
//false until a round is over 
bool  eRound = false;


int aiHealth;
int oldHealth;
int opHealth;


//12 numbers from enviorment 
int opAction;	// the action that opponent has taken this turn (0-7).
int damageD;	// damage I have dealt to my opponent this turn.
int damageT;	// damage I have taken this turn (a negative number meaning the amount I healed).
int opHalf;		// Whether the opponent's current health is below 50 now: 1-yes, 0-no.
int opTen;		// Whether the opponent's current health is below 10 now: 1-yes, 0-no.
int gInv;		// Whether I have a Globe of Invulnerability active now: 1-yes, 0-no.
int stoneS;		// Whether I have a Stoneskin effect active now: 1-yes, 0-no.
int strength;	// Whether I have a Strength effect active now: 1-yes, 0-no.
int opGInv;		// Whether the opponent has a Globe of Invulnerability active now: 1-yes, 0-no.
int opStoneS;	// Whether the opponent has a Stoneskin effect active now: 1-yes, 0-no.
int opStrength; // Whether the opponent has a Strength effect active now: 1-yes, 0-no.
int endRound;   // the end-round signal: 0-round not finished, 1-I have won, 2-The opponent has won, 3-Both are dead





// Display info
void printInfo(vector<vector<float>> &weights, vector<bool> &state);

// Q-Learning or SARSA steps with function approximation
int selectAction(vector<vector<float>> weights, vector<bool> &state, float epsilon);
void performSelectedAction(int action, vector<bool> &state_p);
float obtainReward();
void updateWeights(vector<vector<float>> &weights, int action, int reward, vector<bool> state, vector<bool> state_p, float alpha, float gamma);
void updateState(vector<bool> &state, vector<bool> state_p);
void updateAction();   // SARSA only


const int numActions = 8;
const int numFeatures = 7;
int roundCount = 0;
int action = 0;
bool potionUsed;
bool aiHalf;
float reward = 0;

int damageCounter;
int damageDoneCounter;

int gturnCount;
int DCount;

int sturnCount;

int previousAction;
int MatkCount;
int PatkCount;

float val1 = 0;;
float Qsa;
int main()
{
	srand(time(NULL));

	


	float alpha = 0.1f;
	float gamma = 0.1f;
	float epsilon = 0.1f;

	// the weights table used for function approximation
	vector<vector<float>> weights(numActions, vector<float>(numFeatures + 1, 0.0));

	vector<bool> state(numFeatures, false);    // the current state represented as vector of binary features
	vector<bool> state_p(numFeatures, false);  // the next state State Prime


	// Set up Reinforcement Learning here
	
	cin >> rounds;

	while (roundCount < rounds) {
		   
		
		aiHealth = 100;
		opHealth = 100;
		
		sturnCount = 0;
		gturnCount = 0;
		state[0] = 0;
		state[1] = 0;
		state[2] = 0;
		state[3] = 0;
		state[4] = 0;
		state[5] = 0;
		eRound = false;
		while (eRound == false) {

			
			//choose an action and output to enviorment 
			previousAction = action;
			action = selectAction(weights,state, epsilon);
			
			performSelectedAction(action,state_p);
			
			reward = obtainReward();
			updateWeights(weights, action,reward ,state,state_p,alpha,gamma);
			printInfo(weights, state);
			updateState(state, state_p);
			if (endRound != 0) {
				eRound = true;
				roundCount++;
			}

			
			
		}
	}












	printInfo(weights, state);
	cerr << endl;
	cout.flush();
	system("pause");
	return 0;

}


// prints the weights and the features in the current state
void printInfo(vector<vector<float>> &weights, vector<bool> &state)
{
	int numActions = weights.size();
	int numColumns = weights[0].size();

	cerr << endl << "Weights: " << endl;
	for (int i = 0; i < numActions; i++) {
		cerr << "Action" << i << " ";
		for (int j = 0; j < numColumns; j++) {
			cerr << setw(8) << left;
			cerr << setprecision(3) << weights[i][j];
		}
		cerr << endl;
	}

	cerr << "The current state: " << endl;
	cerr << "      Always1   ";
	for (unsigned int i = 0; i < state.size(); i++) {
		cerr << setw(8) << left;
		cerr << state[i];   
	}
	cerr << endl;
	cerr << "reward= " << reward << endl;
	cerr << "Qsa= " << Qsa << endl;
	cerr << "Val1= " << val1 << endl;
}

//Select action 
int selectAction(vector<vector<float>> weights, vector<bool> &state, float epsilon) {
	
	float r[8];
	int action = 0;
	
	float Tepsilon =.4;

	if (roundCount < 5) {
		Tepsilon = 1;
	}
	
	else {
		Tepsilon = .3;  
	}
	
	
	int numberOfActions;
	

		numberOfActions = numActions;


	float temp = (float)rand() / (float)RAND_MAX;
	if (temp < Tepsilon) {
		action = rand() % numberOfActions;
		return action;
	}

	for (int i = 0; i < numberOfActions; i++) {
		
		float a = weights[i][0];

			if(state[0]==1){
				a += weights[i][1];
				}
			if (state[1] == 1) {
				a += weights[i][2];
			}
			if (state[2] == 1) {
				a +=  weights[i][3];
			}
			
			if (state[3] == 1) {
				a +=  weights[i][4];
			}
			if (state[4] == 1) {
				a += weights[i][5];
			}
			if (state[5] == 1) {
				a += weights[i][6];
			}
			if (state[6] == 1) {
				a += weights[i][7];
			}
		
			
			r[i] = a;
			//cout << r[i]<< endl;

	}
	
	
	Qsa = *max_element(r, r + 7);
	for (int b = 0; b < numberOfActions; b++) {

		
		if (Qsa == r[b]) {
			action = b;
			//cout << " action " << action << endl;
		}
		if (b == numberOfActions -1) {
			return action;
		}
			
		
	}
	
}

//Preform selected action
void performSelectedAction(int action, vector<bool> &state_p) {

	cout << action << endl;
	
	cin >> opAction >> damageD >> damageT >> opHalf >> opTen >> gInv >> stoneS >> strength >> opGInv >> opStoneS >> opStrength >> endRound;

	oldHealth = aiHealth;
	aiHealth -= damageT;
	opHealth -= damageD;


	state_p[0] = gInv;
	state_p[1] = stoneS;

	state_p[2] = opGInv;
	state_p[3] = opStoneS;
	state_p[4] = strength;
	state_p[5] = opStrength;
	state_p[6] = strength;
	

}
void updateState(vector<bool> &state, vector<bool> state_p) {
	
	state[0] = state_p[0];
	state[1] = state_p[1];
	state[2] = state_p[2];
	state[3] = state_p[3];
	state[4] = state_p[4];
	state[5] = state_p[5];
	state[6] = state_p[6];
	
}

//obtain reward
float obtainReward() {
	

	

	reward = 0;
	
	
	reward =  damageD - 1.3*damageT;
	
	
	
	
	
	 
	

	return reward;

}

void updateWeights(vector<vector<float>> &weights, int action, int reward, vector<bool> state, vector<bool> state_p, float alpha, float gamma) {
	float c[8];
	int naction = 0;
	float tGamma = .1;
	float tAlpha = 0.1;


	if (roundCount < 10) {
		tGamma = .5;
		tAlpha = 0.08;
	}

	else {
		tGamma = .15;
		tAlpha = .1;
	}


	for (int i = 0; i < numActions; i++) {
		
		float a = weights[i][0];
			
		if (state_p[0] == 1) {
			a += weights[i][1];
		}
		if (state_p[1] == 1) {
			a += weights[i][2];
		}
		if (state_p[2] == 1) {
			a += weights[i][3];
		}

		if (state_p[3] == 1) {
			a += weights[i][4];
		}
		if (state_p[4] == 1) {
			a += weights[i][5];
		}
		if (state_p[5] == 1) {
			a += weights[i][6];
		}
		if (state[6] == 1) {
			a += weights[i][7];
		}
	

		c[i] = a;
		
	}


	val1 = *max_element(c, c + 7);
	


	weights[action][0] = weights[action][0] + tAlpha * (reward + tGamma * val1 - Qsa );

	if (state[0]== 1) {
		weights[action][1] = weights[action][1] + tAlpha *(reward + tGamma * val1 - Qsa);
	}

	if (state[1] == 1) {
		weights[action][2] = weights[action][2] + tAlpha * (reward + tGamma * val1 - Qsa);
	}

	if (state[2] == 1) {
		weights[action][3] = weights[action][3] + tAlpha * (reward + tGamma * val1 - Qsa);
	}
		
	if (state[3]== 1) {
		weights[action][4] = weights[action][4] + tAlpha * (reward + tGamma * val1 - Qsa);
	}

	if (state[4] == 1) {
		weights[action][5] = weights[action][5] + tAlpha * (reward + tGamma * val1 - Qsa);
	}

	if (state[5] == 1) {
		weights[action][6] = weights[action][6] + tAlpha * (reward + tGamma * val1 - Qsa);
	}
	if (state[6] == 1) {
		weights[action][7] = weights[action][7] + tAlpha * (reward + tGamma * val1 - Qsa);
	}
	
	

}