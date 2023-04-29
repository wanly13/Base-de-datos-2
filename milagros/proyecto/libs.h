//
// Created by milagros on 4/28/23.
//

#ifndef RECORDLECTURE_LIBS_H
#define RECORDLECTURE_LIBS_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <cctype>
#include <iterator>
using namespace std;

#define KEY_SIZE 40
#define ORIGIN_SIZE 10

class Pos{
public:
    long pos;
    char file;

    Pos(){}

    Pos(long pos, char file){
        this->pos = pos;
        this->file = file;
    }
};

class file_not_found : public exception {
public:
    file_not_found(const char* message) : m_message(message){}
    virtual const char* what() const throw(){
        return m_message.c_str();
    }
private:
    string m_message;
};

class key_not_found : public exception {
public:
    key_not_found(const char* message) : m_message(message){}
    virtual const char* what() const throw(){
        return m_message.c_str();
    }
private:
    string m_message;
};

class ayudame_Dios : public exception {
public:
    ayudame_Dios(const char* message) : m_message(message){}
    virtual const char* what() const throw(){
        return m_message.c_str();
    }
private:
    string m_message;
};

void create_file_if_doesnt_exist(string filename){
    ofstream file("files/" + filename, ios::out | ios::app);
    if(!file.is_open())
        throw file_not_found("\nCould not open file - Class Constructor");
    file.close();
}



#endif //RECORDLECTURE_LIBS_H

