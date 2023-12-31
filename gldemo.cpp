// Array Visualisation for CIS6007 WRIT1

//Header section where libraries and namespaces are included
#include <iostream>//to input and output data
#include <string>//to handle strings
#include <random>//to generate random numbers
#include "gl_stuff.h"//includes functionalities which help creating an OpenGL context
#include "Array2D.h"//has a class to deal with 2D arrays
#include <tbb/tbb.h>//library for parallel programming
#include <chrono>//for time-related operations
#include <thread>//for time-related operations

using namespace std;
using namespace tbb;

#pragma region Function Prototypes

void initPattern(Array2D<int>& array); // Initialise grid with "alive" & "dead" cells
void update(void); // Applying rules 

#pragma endregion



// Example 2Darray                             
Array2D<int>						myArray = Array2D<int>(30, 30);



// Starting point for our program...(The main function)
int main(int argc, char* argv[])
{
	// Initialise OpenGL window...
	gl_init(argc, argv, update, "CIS6007 WRIT1 - Game of Life Demo", true);

	// Initialise our Game of Life starting pattern...
	initPattern(myArray);

	// Start the main loop - this calls our update function (below) to update our game of life generations.
	// Note: We never return from glutMainLoop until we quit the application
	glutMainLoop();

    return 0;
}



//Function to Initialise grid with "alive" and "dead" cells
void initPattern(Array2D<int>& array) {

	//Initially, clearing the array by setting all cells to "dead")
	parallel_for( //loop through each element in the array
		0,
		array.w * array.h, // loop goes from 0 to the total number of elements in the array
		[&](int i) { //representing each element by index i
       //& means that passing the variable i by reference so it can be modified inside the loop

			//Below two lines calculate the x and y coordinates

			int x = i % array.w;//get the X cordinate from the remainder of 'index' divided by the width of array 
			int y = i / array.h;//get Y cordinate from 'index' divided by the height of array

			// It divides the loop iterations 
			// into multiple parts 
			// So, it can run simultaneously by multiple threads for better performance

			array(x, y) = 0; //sets the value of the current element in the array to 0
		}
	);


	// Setup some specific cells to be "1" (alive) - this is the initial state
	// NOTE: *** REPLACE THIS WITH YOUR OWN CODE TO SETUP THE LIVE CELL PATTERNS

	//Pattern 1 - (dead)
	myArray(2, 5) = 1;
	myArray(2, 6) = 1;
	myArray(2, 7) = 1;
	myArray(2, 8) = 1;
	myArray(2, 9) = 1;

	myArray(3, 4) = 1;
	myArray(3, 10) = 1;

	myArray(6, 3) = 1;
	myArray(6, 11) = 1;

	myArray(7, 2) = 1;
	myArray(8, 2) = 1;
	myArray(9, 2) = 1;
	myArray(10, 2) = 1;
	myArray(11, 2) = 1;

	myArray(8, 7) = 1;
	myArray(9, 6) = 1;
	myArray(9, 7) = 1;
	myArray(9, 8) = 1;
	myArray(10, 7) = 1;

	myArray(7, 12) = 1;
	myArray(8, 12) = 1;
	myArray(9, 12) = 1;
	myArray(10, 12) = 1;
	myArray(11, 12) = 1;

	myArray(12, 3) = 1;
	myArray(12, 11) = 1;

	myArray(15, 4) = 1;
	myArray(15, 10) = 1;

	myArray(16, 5) = 1;
	myArray(16, 6) = 1;
	myArray(16, 7) = 1;
	myArray(16, 8) = 1;
	myArray(16, 9) = 1;


	//Pattern 2 - Breadcrumb Grenade (dead)
	/*myArray(4, 7) = 1;
	myArray(4, 8) = 1;
	myArray(5, 8) = 1;
	myArray(5, 6) = 1;
	myArray(6, 6) = 1;
	myArray(6, 7) = 1;

	myArray(4, 12) = 1;
	myArray(4, 13) = 1;
	myArray(5, 12) = 1;
	myArray(5, 14) = 1;
	myArray(6, 13) = 1;
	myArray(6, 14) = 1;

	myArray(7, 9) = 1;
	myArray(7, 10) = 1;
	myArray(8, 9) = 1;
	myArray(8, 10) = 1;

	myArray(9, 6) = 1;
	myArray(9, 7) = 1;
	myArray(10, 6) = 1;
	myArray(10, 8) = 1;
	myArray(11, 7) = 1;
	myArray(11, 8) = 1;

	myArray(9, 13) = 1;
	myArray(9, 14) = 1;
	myArray(10, 14) = 1;
	myArray(10, 12) = 1;
	myArray(11, 12) = 1;
	myArray(11, 13) = 1;*/

	
	//Pattern 3 - Pulsar Pattern (repeat)
	/*myArray(5, 3) = 1;
	myArray(6, 3) = 1;
	myArray(7, 3) = 1;
	myArray(11, 3) = 1;
	myArray(12, 3) = 1;
	myArray(13, 3) = 1;

	myArray(3, 5) = 1;
	myArray(8, 5) = 1;
	myArray(10, 5) = 1;
	myArray(15, 5) = 1;

	myArray(3, 6) = 1;
	myArray(8, 6) = 1;
	myArray(10, 6) = 1;
	myArray(15, 6) = 1;

	myArray(3, 7) = 1;
	myArray(8, 7) = 1;
	myArray(10, 7) = 1;
	myArray(15, 7) = 1;

	myArray(5, 8) = 1;
	myArray(6, 8) = 1;
	myArray(7, 8) = 1;
	myArray(11, 8) = 1;
	myArray(12, 8) = 1;
	myArray(13, 8) = 1;

	myArray(5, 10) = 1;
	myArray(6, 10) = 1;
	myArray(7, 10) = 1;
	myArray(11, 10) = 1;
	myArray(12, 10) = 1;
	myArray(13, 10) = 1;

	myArray(3, 11) = 1;
	myArray(8, 11) = 1;
	myArray(10, 11) = 1;
	myArray(15, 11) = 1;

	myArray(3, 12) = 1;
	myArray(8, 12) = 1;
	myArray(10, 12) = 1;
	myArray(15, 12) = 1;

	myArray(3, 13) = 1;
	myArray(8, 13) = 1;
	myArray(10, 13) = 1;
	myArray(15, 13) = 1;

	myArray(5, 15) = 1;
	myArray(6, 15) = 1;
	myArray(7, 15) = 1;
	myArray(11, 15) = 1;
	myArray(12, 15) = 1;
	myArray(13, 15) = 1;*/


	//Pattern 4 - (repeat)
	/*myArray(9,5) = 1;
	myArray(9,6) = 1;
	myArray(9,7) = 1;
	myArray(9,8) = 1;
	myArray(9,9) = 1;
	myArray(9,10) = 1;
	myArray(9,11) = 1;
	myArray(9,12) = 1;
	myArray(9,13) = 1;
	myArray(9,14) = 1;
	myArray(9,15) = 1;
	myArray(9,16) = 1;
	myArray(9,17) = 1;
	myArray(9,18) = 1;
	myArray(9,19) = 1;
	myArray(9,20) = 1;*/
}


// Main update function - apply Game of Life rules here
// Note: This is called by FreeGLUT's main event loop - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!




//Defining the neighborsComputing function outside 
//can re used for many interations 
//becomes a utility of the Update 

int neighborsComputing(Array2D<int>& array, int x, int y) {
	int count = 0; //initializes "count" variable to 0, that keeps track of the number of neighboring cells

	for (int i = -1; i <= 1; i++) {
	//Loops through 'i' (represents x-coordinate of the neighboring cell)
		for (int j = -1; j <= 1; j++) {
		//Loops through 'j' (represents the y-coordinate of the neighboring cell)
			
			//checks if the current cell being examined is the same as the original cell
			if (i == 0 && j == 0) { continue; }//Continue to next iteration

			int nx = x + i;//calculate the x coordinates of the neighboring cell
			int ny = y + j;//calculate the y coordinates of the neighboring cell
			
			//checks neighboring cell is alive 
										 //checks the neighboring cell is within the the array boundaries
			if (nx >= 0 && ny >= 0 && nx < array.w && ny < array.h) {
				//if so, count variable increments
				count += array(nx, ny);
			}
		}
	}
	//return count of alive neighboring cells 
	return count;
}



//Function to update the simulation by computing the next generation of cells based on the current generation
void update(void) {

	//
	// *** SEQUENTIAL VERSION OF THE CODE TO UPDATE GAME OF LIFE ***
	//


	Array2D<int> nextGenArray(myArray.w, myArray.h);
	//Creating a new array with the same size in the current array to hold the next generation of cells

	//obtaining the system time before the task starts
	auto startTime = chrono::high_resolution_clock::now();

	//Below Loops will loop through each cell in the current array to build the rules
	for (int x = 0; x < myArray.w; x++) {
		for (int y = 0; y < myArray.h; y++) {

			                //counting the number of live neighbours for the current cell
			int neighbors = neighborsComputing(myArray, x, y);

			//RULES
			//current cell = alive and has 2 or 3 live neighbors;
			if (myArray(x, y) == 1 && (neighbors == 2 || neighbors == 3)) {
				nextGenArray(x, y) = 1;//that cell stays alive in the next generation
			}
			//current cell = alive and has 3 live neighbors,
			else if (myArray(x, y) == 0 && neighbors == 3) {
				nextGenArray(x, y) = 1;//that cell stays alive in the next generation 
			}
			//Otherwise, that cell will be a dead in next generation
			else {
				nextGenArray(x, y) = 0;
			}
		}
	}


	//
	// *** PARALLEL VERSION OF THE CODE TO UPDATE GAME OF LIFE ***
	//
	
	//Parallelize the initPattern function & Modify it to use the parallel_for loop from the TBB library
	//Use: Ability to execute the loop iterations parallely
	
	                              //'x' = current index
	parallel_for(0, myArray.w, [&](int x) {
							   //Passing the Lambda function for each iteration of the loop, 
	//to handle a different range of indices and set the value of each element 
	//in the x column of myArray = 0
		for (int y = 0; y < myArray.h; y++) {

			int neighbors = neighborsComputing(myArray, x, y);

			if (myArray(x, y) == 1 && (neighbors == 2 || neighbors == 3)) {
				nextGenArray(x, y) = 1;
			}
			else if (myArray(x, y) == 0 && neighbors == 3) {
				nextGenArray(x, y) = 1;
			}
			else {
				nextGenArray(x, y) = 0;
			}
		}
		});



	//obtaining the system time after the task ended
	auto endTime = chrono::high_resolution_clock::now();
	//display the time taken for the execution in seconds
	chrono::duration<double> duration = endTime - startTime;
	cout << "Time Taken For Execution: " << duration.count() << " Seconds" << endl;

	

	//The current array is updated to be the new generation
	//Use: Ensures that the state of each cell is updated
    myArray = nextGenArray;


	//Suspends the execution for 1200 milliseconds before the next update
	this_thread::sleep_for(chrono::milliseconds(1200));

	// Redraw the screen to show the new generation
	renderLatestGeneration(myArray);

}