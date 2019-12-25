/*
 * FileCrypter.h
 *
 *  Created on: Apr 23, 2019
 *      Author: fenris
 */

#ifndef FILECRYPTER_H_
#define FILECRYPTER_H_

#include<fstream>

#include "common.h"

using std::ofstream;
using std::ifstream;

class FileCrypter {
    int xorOperation(const char* inFile, const char* outFile, const QString& password);
	bool doesFileExists (const char* name);
public:
    void processFile(const char* inFile, const char* outFile, const QString& password);
};

#endif /* FILECRYPTER_H_ */
