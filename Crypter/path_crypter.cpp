/*
 * StringCrypter.cpp
 *
 *  Created on: May 4, 2019
 *      Author: fenris
 */

#include "path_crypter.h"

Fullpath PathCrypter::GetEncodedPath(Fullpath &path, const QString &password){
    Fullpath encodedPath;
    encodedPath.elements.push_back(path.elements[0]);
    encodedPath.isDir = path.isDir;

    for (std::vector<QString>::size_type i=1;i<path.elements.size();i++) {
        QString path_var = path.elements[i];

        if( cache.find(path_var) != cache.end()) {
            encodedPath.elements.push_back(cache[path_var]);
            continue;
        }

        QString encoded_str =  EncodeString(path_var, password).append(SUFFIX_ENC);
        encodedPath.elements.push_back(encoded_str);
        cache[path_var]=encoded_str;
    }

    return encodedPath;
}

Fullpath PathCrypter::GetDecodedPath(Fullpath &path, const QString &password){
    Fullpath decodedPath;
    decodedPath.elements.push_back(path.elements[0]);
    decodedPath.isDir = path.isDir;

    for (std::vector<QString>::size_type i=1;i<path.elements.size();i++) {
        QString path_var = path.elements[i];

        if( cache.find(path_var) != cache.end()) {
            decodedPath.elements.push_back(cache[path_var]);
            continue;
        }

        //It is expected to be always present
        QString::size_type loc = path_var.indexOf(SUFFIX_ENC, 0 );
        QString path_ele_wo_suffix = path_var.left(loc);
        QString decoded_str =  DecodeString(path_ele_wo_suffix, password);
        decodedPath.elements.push_back(decoded_str);
        cache[path_var]=decoded_str;
    }

    return decodedPath;
}



/*
 * prelist_value is the value at the prelist_index. l is the input character. p is the password character.
 * [number][prelist_value]
 * [(l+p)/62][prelist((l+p)%62)]
 */
QString PathCrypter::EncodeString(const QString &input,const QString &password) {
    QString::size_type password_size = password.size();
    QString::size_type size = input.size();

    QString enc_string("");
    for (QString::size_type i = 0; i < size; i++) {
        if (isalnum(input.at(i).toLatin1())) {
            int number = (input.at(i).toLatin1() + password.at(i % password_size).toLatin1())
                    / ALNUM_CHAR_LIST_SIZE;
            int prelist_index = (input.at(i).toLatin1() + password.at(i % password_size).toLatin1())
                    % ALNUM_CHAR_LIST_SIZE;
            char prelist_value = GetPrelistValue(prelist_index);
            enc_string = enc_string +  QString::number(number) + prelist_value;
        } else {
            enc_string += input[i];
        }
    }
    return enc_string;
}

/*
 * (62*number + indexof(prelist_value))-p
 *
 * pass_ind is needed coz every two encoded char there is one password char needed. One counter cannot do this.
 */
QString PathCrypter::DecodeString(const QString &input, const QString &password) {
    QString::size_type password_size = password.size();
    QString::size_type size = input.size();

    QString dec_string("");
    for (QString::size_type i = 0, pass_ind = 0; i < size; i++, pass_ind++) {
        if (isdigit(input.at(i).toLatin1())) {
            int number = input.at(i).toLatin1() - '0';
            char dec_char = static_cast<char>(ALNUM_CHAR_LIST_SIZE * number + GetPrelistIndex(input.at(++i).toLatin1())
                    - password.at(pass_ind % password_size).toLatin1());
            dec_string += dec_char;
        } else {
            dec_string += input[i];
        }
    }
    return dec_string;
}

/*
 * Gets the value of the list [0-9][A-Z][a-z] at the given index
 */
char PathCrypter::GetPrelistValue(int prelist_index) {
    return alnum_str[prelist_index];
}

/*
 * Gets the index of the list [0-9][A-Z][a-z] for the passed value
 */
int PathCrypter::GetPrelistIndex(char prelist_value) {
    if ('0' <= prelist_value && prelist_value <= '9') {
        return static_cast<int>(prelist_value - '0');
    } else if ('A' <= prelist_value && prelist_value <= 'Z') {
        return static_cast<int>(prelist_value - 'A' + NUM_CHAR_LIST_SIZE);
    } else { //if ('a' <= prelist_value && prelist_value <= 'z')
        return static_cast<int>(prelist_value - 'a' + CAP_ALNUM_CHAR_LIST_SIZE);
    }
}
