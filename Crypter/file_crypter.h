/*
 * FileCrypter.h
 *
 *  Created on: Apr 23, 2019
 *      Author: fenris
 */

#ifndef FILECRYPTER_H_
#define FILECRYPTER_H_

#include<fstream>

#include <QThread>
#include <QThreadPool>

#include "common.h"

using std::ofstream;
using std::ifstream;

class FileCrypter : public QRunnable {
private:
    const QString inFile;
    const QString outFile;
    const QString password;

    bool doesFileExists (const char* name);
    int xorOperation();

public:
    FileCrypter(const QString& inFile, const QString& outFile, const QString& password): inFile(inFile), outFile(outFile), password(password) {}

    void processFile();
    void run();
};

#endif /* FILECRYPTER_H_ */
