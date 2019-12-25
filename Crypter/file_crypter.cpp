/*
 * FileCrypter.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: fenris
 */
#include "file_crypter.h"

void FileCrypter::processFile(const char* inFile, const char* outFile, const QString& password) {
    xorOperation(inFile, outFile, password);
}

int FileCrypter::xorOperation(const char* inFile, const char* outFile, const QString& password) {
	if (doesFileExists(outFile)) {
        qDebug() << "File already exists. Skipping";
		return 1;
	}
	ofstream output(outFile, ofstream::binary);
	ifstream input(inFile, ifstream::binary);

    QString::size_type password_size = static_cast<QString::size_type>(password.size());

	input.seekg(0, input.end);
    QString::size_type size = static_cast<QString::size_type>(input.tellg());
	input.seekg(0);

	char* buffer = new char[size];
	input.read(buffer, size);

	char* xor_string = new char[size];
    for (QString::size_type i = 0; i < size; i++) {
        xor_string[i] = (buffer[i]) ^ (password.at(i % password_size).toLatin1());
	}

	output.write(xor_string, size);

	delete[] buffer;
	delete[] xor_string;
	output.close();
	input.close();
	return 0;
}


bool FileCrypter::doesFileExists (const char* name) {
    if (FILE *file = fopen(name, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}
