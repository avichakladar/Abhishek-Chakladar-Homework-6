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
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  BinaryFileRecord *record = new BinaryFileRecord();
  BinaryFileHeader *header = new BinaryFileHeader();
  
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char *) header, sizeof(BinaryFileHeader));
  
  char buff[1024];
  
  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.
  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  sprintf(buff, "Magic: 0x%X", header -> magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buff);
  drawCDKMatrix(myMatrix, true);    /* required  */
  
  sprintf(buff, "Version: %u", header -> versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buff);
  drawCDKMatrix(myMatrix, true);    /* required  */
  
  sprintf(buff, "NumRecords: %lu", header -> numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buff);
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
