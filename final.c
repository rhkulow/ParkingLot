/*
 Robert Kulow & Bryce Roy
 This program creates a car park by reading a file named "carpark.txt", then lets you view the
 car park, view the percentage of how filled it is, and reserve a parking spot.
*/
#include<stdio.h>
#include<stdlib.h>

void display(char carpark[]){

	//output
	printf("\n  ABCD EFGH\n");
	for(int i = 0; i < 10; i++){
		printf("%d ", i+1);
		for(int j = 0; j < 8; j++){
			printf("%c", carpark[(i*8) + j]);
			if (j == 3)
				printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}

void statistics(char carpark[]){
	/*
	 slot will keep track of how many slots of the car park are occupied
	*/
	//processing
	int slot = 0;
	for (int i = 0; i < 80; i++)
		if (carpark[i] == 'X')
			slot++;
	double occupany = (slot / 80.0) * 100;

	//output
	printf("\nCurrent occupancy is %.1f%%\n\n", occupany);
}

char assign_slot(char carpark[], int row, char column){
	//processing
	if ((row > -1 && row < 11) && (column > 64) && (column < 73) && carpark[(row * 8) + ((int)column - 65)] == 'O'){
		carpark[(row * 8) + ((int)column - 65)] = 'X';
		printf("Your selection %d%c is reserved!\n\n", row + 1, column);
		FILE *file = fopen("carpark2.txt", "w");
		int spot = 0;
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 4; j++){
				fprintf(file, "%c", carpark[spot]);
				spot++;
			}
			fprintf(file, " ");
			for(int j = 5; j < 9; j++){
				fprintf(file, "%c", carpark[spot]);
				spot++;
			}
			if (i % 2 == 1){
				fprintf(file, "\n\n");
			}
			else{
				fprintf(file, "\n");
			}
		}
		fclose(file);
	}
	else{
		printf("Error! Selection %d%c does not exist or is filled, please try again\n\n", row + 1, column);
	}
	return *carpark;
}

char reserve(char carpark[]){
	/*
	 row will store what row is being used from carpark
	 column will store what column is being used ftom the carpark
	 size will keep track of how big the search alforithm gets
	 input will see what the user inputs
	*/

	//processing
	int row = -1;
	char column = 'a';
	int size = 2;
	char input = 'a';
	while(row == -1 && size != 10){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(carpark[(i * 8) + j] == 'O'){
					column = j + 65;
					row = i;
					break;
				}
			if (row != -1)
				break;
			}
		}
		size++;
	}
	if(size != 9){

		//input
		printf("\nClosest available slot is %d%c, do you want to reserve it (y/n)? ", row + 1, column);
		scanf(" %c", &input);

		//processing
		if (input == 'y'){
			*carpark = assign_slot(carpark, row, column);
		}
		else if(input == 'n'){
			//input
			printf("Please enter your preferred empty slot: ");
			scanf("%d%c", &row, &column);
			*carpark = assign_slot(carpark, row - 1, column);
		}
		else{
			//output
			printf("Error! Please try again\n\n");
		}
	}
	else{
		//input
		printf("Please enter your preferred empty slot: ");
		scanf("%d%c", &row, &column);
		*carpark = assign_slot(carpark, row - 1, column);
	}
	return *carpark;
}

int main(){
	system("clear");
	/*
	 input will see what the user inputs
	 quit will keep track of when the program should quit
	 carpark is the dataset that will keep tack of the carpark's spots
	 file will containe the data from the file
	 line will be a buffer for each line of the text file
	 spot will keep track of what spot carpark is using
	*/

	//processing
	char input;
	int quit = 0;
	char carpark[80] = {};
	FILE *file = fopen("carpark.txt", "r");
	char line[1000];
	int spot = 0;
	while (fgets(line, 1000, file)){
		if ((line[0] == 'O') || (line[0] == 'X')){
			for (int i = 0; i < 4; i++){
				carpark[spot] = line[i];
				spot++;
			}
			for (int i = 5; i < 9; i++){
				carpark[spot] = line[i];
				spot++;
			}
		}
	}
	fclose(file);

	//input
	while(quit != 1){
		printf("Select your choice from the menu:\nD to display current status of the car park\nR to reserve an empty slot in the car park\nS to display %% occupany of the car park\nQ to quit\n: ");
		scanf(" %c", &input);
		switch(input){
			//output
			case('D'):{
				display(carpark);
				break;
			}
			//processing
			case('R'):{
				*carpark = reserve(carpark);
				break;
			}
			//ouput
			case('S'):{
				statistics(carpark);
				break;
			}
			case('Q'):{
				quit = 1;
				break;
			}
			default:{
				printf("Error! Please try again\n");
				break;
			}
		}
	}
	system("clear");
	return 0;
}
