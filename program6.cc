/*
 * Abhishek Chakladar(axc161930)
 * axc161930@utdallas.edu
 * CS 3377.501
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include "program6.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{

  //CDK matrix objects necessary
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;

  //objects for reading the binary headers and the records
  BinaryFileRecord *record = new BinaryFileRecord();
  BinaryFileHeader *header = new BinaryFileHeader();
  
  //read from the binary file
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char *) header, sizeof(BinaryFileHeader));
  
  char buff[1024];
  
  //define the row and column titles for the matrix
  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "C4", "C5"};
  
  //set the dimensions
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  
  //Make sure putty terminal is large enough
  window = initscr();
  cdkscreen = initCDKScreen(window);

  //Start CDK Colors
  initCDKColor();
  
  //Create the matrix.  Need to manually cast (const char**) to (char **)
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  //check if the matrix built succesfully
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //Display the Matrix
  drawCDKMatrix(myMatrix, true);

  //put the headers in the top row
  //for each one steps are:
  /*
  * 1. store the string info inside the buff array
  * 2. put it in the correct matrix position
  * 3. draw it in
  */
  sprintf(buff, "Magic: 0x%X", header -> magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buff);
  drawCDKMatrix(myMatrix, true);
  
  sprintf(buff, "Version: %u", header -> versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buff);
  drawCDKMatrix(myMatrix, true);
  
  sprintf(buff, "NumRecords: %lu", header -> numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buff);
  drawCDKMatrix(myMatrix, true);
  
  //get the number of records
  unsigned long long records = header -> numRecords;
  
  //do a for loop for all the record entries and add them to the matrix
  //did from i=2 to i < records + 2, because we start at row 2, and add arbitrary number of records
  for (int i = 2; i < int(records) + 2; i++){
	//get the records from the record object
	binInfile.read((char *) record, sizeof(BinaryFileRecord));
	char buff2[1024];
	
	//put it into buffer, then put string length in
	sprintf(buff2, "strlen: %u", record -> strLength);
	setCDKMatrixCell(myMatrix, i, 1, buff2);
	drawCDKMatrix(myMatrix, true);    /* required  */
	
	//don't sprintf, because we're using the same point
	setCDKMatrixCell(myMatrix, i, 2, record -> stringBuffer);
	drawCDKMatrix(myMatrix, true);    /* required  */
  }

  //press a key to continue
  unsigned char x;
  cin >> x;

  //Cleanup screen
  endCDK();
}
