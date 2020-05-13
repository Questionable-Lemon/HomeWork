#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;//very rarely it will output a number that isnt a increment of the last number/so far only happens for the second and third ships
//Oliver Greer
//5/10/2020
//global variables
const int carrierArrSize = 4;
const int destroyerArrSize = 3;
const int cruiserArrSize = 2;
const int shipArrSize = 2;
//arrays to hold ship location data
int carrierCoord[carrierArrSize][shipArrSize];
int destroyerCoord[destroyerArrSize][shipArrSize];
int cruiserCoord[cruiserArrSize][shipArrSize];
//function prototypes
bool CheckIfHit(int coord1, int coord2);

int Randomize(int maximumRand);

void CheckCollision(int coord1, int coord2, string shipType);
void Increment(int & coord1, int & coord2, int h_v, int upDown, string shipType);
void PlaceShips(string shipType);

int main()
{
	//variables
	const int gameBoardSize = 6;
	string carrier = "carrier";
	string destroyer = "destroyer";
	string cruiser = "cruiser";
	char gameBoard[gameBoardSize][gameBoardSize];
	int turnNumber = 0;
	int coordInputOne, coordInputTwo;
	bool shipsNotSunk = true;
	bool isHit;
	//seed the random function
	int seed = time(NULL);
	srand(seed);
	//place each ship with functions
	PlaceShips(carrier);
	PlaceShips(destroyer);
	PlaceShips(cruiser);
	for(int i = 0; i < carrierArrSize; i++){
		for(int t = 0; t < shipArrSize; t++)
			cout << carrierCoord[i][t];
		cout << " ";
	}
	cout << endl;
	for(int i = 0; i < destroyerArrSize; i++){
		for(int t = 0; t < shipArrSize; t++)
			cout << destroyerCoord[i][t];
		cout << " ";
	}
	cout << endl;
	for(int i = 0; i < cruiserArrSize; i++){
		for(int t = 0; t < shipArrSize; t++)
			cout << cruiserCoord[i][t];
		cout << " ";
	}
	cout << endl;
	//fill the game board with empty characters
	for(int i = 0; i < gameBoardSize; i++){
		for(int t = 0; t < gameBoardSize; t++){
			gameBoard[i][t] = ' ';
		}
	}
	//main game loop
	while(shipsNotSunk){
		//grid cout
		cout << "Current Battle Status: \n";
		for(int i = 0; i < gameBoardSize; i++){
			cout << "+---+---+---+---+---+---+\n" << "| ";
			for(int t = 0; t < gameBoardSize; t++){
				cout << gameBoard[i][t] << " | ";
			}
			cout << endl;
		}
		cout << "+---+---+---+---+---+---+\n" << "Fire at: ";
		//input coordinates
		cin >> coordInputOne >> coordInputTwo;
		cin.ignore();
		//check for valid input
		if(coordInputOne >= 0 && coordInputOne <= 5 && coordInputTwo >= 0 && coordInputTwo <= 5){
			if(gameBoard[coordInputOne][coordInputTwo] == ' '){
				isHit = CheckIfHit(coordInputOne, coordInputTwo);
				//assign char values to the location shot at
				if(isHit){
					gameBoard[coordInputOne][coordInputTwo] = 'X';
					cout << "A hit! ";
				}
				else{
					gameBoard[coordInputOne][coordInputTwo] = 'O';
					cout << "A miss! ";
				}
			}
			else
				cout << "Already entered those coordinates.\n";
		}
		else
			cout << "Input out of bounds, try again.\n";


	}
	cin.get();
	return 0;
}
bool CheckIfHit(int coord1, int coord2)//check if the fired shot hits any one of the ships
{
	for(int i = 0; i < carrierArrSize; i++){
		if(carrierCoord[i][0] == coord1 && carrierCoord[i][1] == coord2)
			return true;
	}
	for(int i = 0; i < destroyerArrSize; i++){
		if(destroyerCoord[i][0] == coord1 && destroyerCoord[i][1] == coord2)
			return true;
	}
	for(int i = 0; i < cruiserArrSize; i++){
		if(cruiserCoord[i][0] == coord1 && cruiserCoord[i][1] == coord2)
			return true;
	}
	return false;
}
int Randomize(int maximumRand)//returns a random number between 0 and argument passed
{
	int randomNumber;
	randomNumber = rand() % (maximumRand + 1);
	return randomNumber;
}
void CheckCollision(int coord1, int coord2, string shipType)//checks collisions with other ships
{															//if there is a collsion replace the ship
	//check carrier collision
	if(shipType != "carrier"){
		for(int i = 0; i < carrierArrSize; i++){
			if(carrierCoord[i][0] == coord1 && carrierCoord[i][1] == coord2)
				PlaceShips(shipType);
		}
	}
	//check destroyer collision
	if(shipType != "destroyer"){
		for(int i = 0; i < destroyerArrSize; i++){
			if(destroyerCoord[i][0] == coord1 && destroyerCoord[i][1] == coord2)
				PlaceShips(shipType);
		}
	}
	//check cruiser collsion
	if(shipType != "cruiser"){
		for(int i = 0; i < cruiserArrSize; i++){
			if(cruiserCoord[i][0] == coord1 && cruiserCoord[i][1] == coord2)
				PlaceShips(shipType);
		}
	}
}
void Increment(int & coord1, int & coord2, int h_v, int upDown, string shipType)//increments coordinates
{
	//vertical
	if(h_v){
		//down
		if(upDown)
			coord1++;
		//up
		else
			coord1--;
	}
	//horizontal
	else{
		//right
		if(upDown)
			coord2++;
		//left
		else
			coord2--;
	}
}
void PlaceShips(string shipType)//places ships
{
	//pick starting coordinates
	int startCoordinateOne = Randomize(5);
	int startCoordinateTwo = Randomize(5);
	//pick between horizontal or vertical placement
	int horizontalOrVertical = Randomize(1);
	//pick which way to go after initial placement
	int upDownLeftRight = Randomize(1);
	//place ships
	if(shipType == "carrier"){
		for(int i = 0; i < carrierArrSize; i++){
			carrierCoord[i][0] = startCoordinateOne;
			carrierCoord[i][1] = startCoordinateTwo;
			//check collision
			CheckCollision(startCoordinateOne, startCoordinateTwo, shipType);
			//increment coordinates
			Increment(startCoordinateOne, startCoordinateTwo, horizontalOrVertical, upDownLeftRight, shipType);
		}
	}
	if(shipType == "destroyer"){
		for(int i = 0; i < destroyerArrSize; i++){
			destroyerCoord[i][0] = startCoordinateOne;
			destroyerCoord[i][1] = startCoordinateTwo;
			CheckCollision(startCoordinateOne, startCoordinateTwo, shipType);
			Increment(startCoordinateOne, startCoordinateTwo, horizontalOrVertical, upDownLeftRight, shipType);
		}
	}
	if(shipType == "cruiser"){
		for(int i = 0; i < cruiserArrSize; i++){
			cruiserCoord[i][0] = startCoordinateOne;
			cruiserCoord[i][1] = startCoordinateTwo;
			CheckCollision(startCoordinateOne, startCoordinateTwo, shipType);
			Increment(startCoordinateOne, startCoordinateTwo, horizontalOrVertical, upDownLeftRight, shipType);
		}
	}
	//check if ship is out of bounds
	if(startCoordinateOne < 0 || startCoordinateOne > 5 || startCoordinateTwo < 0 || startCoordinateTwo > 5)
		PlaceShips(shipType);
}