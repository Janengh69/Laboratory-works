/*!
 * file: Translate.h
 * CTranslate class declaration
 * written: 19/02/2019
 * last modified: 21/02/2019
 * Copyright (c) 2011 by Yu.Zorin
 */
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm> 
#include <fstream>
#include <functional>
#include <sstream>
class CTranslate {
public:
	//default constructor
	CTranslate();

	//copy constructor
	CTranslate(const CTranslate &);
	//destructor
	~CTranslate();
	//overloaded assignment
	CTranslate & operator=(const CTranslate &);
	bool operator<(const CTranslate &);
	void SetEng(std::string _eng);
	void SetIta(std::string _ita);
	void MakePair(std::string, std::string);
	void Print()const;
	std::string GetEng()const;
	std::string GetIta()const;
	bool LoadFromCSV(char* filename, std::vector<CTranslate> &base);
	
private:
	std::string eng;//English word
	std::string ita;//Italian word
};

bool EngCmp(const CTranslate &, const CTranslate &);
bool ItCmp(const CTranslate &, const CTranslate &);
void ListAll(const std::vector<CTranslate> &);
void DelByEng(std::vector <CTranslate> &, std::string en);
void DelByIta(std::vector <CTranslate> &, std::string it);
void SortByEng(std::vector <CTranslate> &);
void SortByIta(std::vector <CTranslate> &);
void TranslateEng(const std::vector <CTranslate> &, std::string en);
void TranslateIta(const std::vector<CTranslate> &, std::string ita);
