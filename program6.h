/*
Abhishek Chakladar(axc161930)
axc161930@utdallas.edu
CS 3377.501
*/

#ifndef PROGRAM6_H
#define PROGRAM6_H

#include <stdint.h>

//holds the header informations
class BinaryFileHeader{

 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;

};

//record string lengths can only be 25 characters long
const int maxRecordStringLength = 25;

//hold the record information
class BinaryFileRecord{

 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};
#endif
