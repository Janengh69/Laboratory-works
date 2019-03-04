/*!
 * file: Test_Translate.cpp
 * Ctarnslate class defiition 
 * written: 19/02/2019
 * last modified: 21/02/2019
 * created: Dorosh Karuna KV-72
 */
#include "CTranslate.h"

//empty constructor
CTranslate::CTranslate()
{
	this->eng = "";
	this->ita = "";
}
CTranslate::~CTranslate()
{
}
bool CTranslate::operator<(const CTranslate & word) {
	return this->eng.compare(word.eng);
}

CTranslate::CTranslate(const CTranslate &ob) {
	*this = ob;
}

CTranslate & CTranslate::operator=(const CTranslate &ob) {
	this->eng = ob.eng;
	this->ita = ob.ita;
	return *this;
}
//Порівнює англійські слова в лексикографічному порядку
void CTranslate::SetEng(std::string _eng) {
	this->eng = _eng;
}
void CTranslate::SetIta(std::string _ita) {
	this->ita = _ita;
}
void CTranslate::MakePair(std::string en, std::string ita) {
	CTranslate new_word;
	new_word.eng = en;
	new_word.ita = ita;
	*this = new_word;

}
//Затягає анг.і італ.слова в відпов.поля
void CTranslate::Print()const {
	if (this != nullptr) {
		std::cout  << "   eng: "<< this->eng << "\n    ital: " << this->ita << std::endl;
	}
	else {
		std::cout << "Word wasn't found" << std::endl;
	}
}
std::string CTranslate::GetEng()const {
	return this->eng;
}
std::string CTranslate::GetIta()const {
	return this->ita;
}
//Повертають покажчик на eng / ita відповідно.

void ListAll(const std::vector<CTranslate> &vect) {
	if(!vect.empty())
		for (auto i : vect)
			i.Print();

}
//Вивести на консоль уміст контейнера
void DelByEng(std::vector <CTranslate> & vect, const std::string en) {
	std::vector<CTranslate>::iterator it = (&vect)->begin();
 	while(it != (&vect)->end()) {
		if ((*it).GetEng() == en) 
			it = vect.erase(it);
		else 	
			++it;
	}
}
//Вилучити з контейнера всі елементи, у яких поле eng рівно en.

void DelByIta(std::vector <CTranslate> &vect, const std::string ita) {
	std::vector<CTranslate>::iterator it = (&vect)->begin();
	while (it != (&vect)->end()) {
		if ((*it).GetIta() == ita)
			it = vect.erase(it);
		else
			++it;
	}
}
//Вилучити з контейнера всі елементи, у яких поле ita рівно it.
 bool EngCmp(const CTranslate &first,const CTranslate &sec) { return (first.GetEng() < sec.GetEng());}
void SortByEng(std::vector <CTranslate> &vect) {
	
	sort(vect.begin(), vect.end(), EngCmp);
}
//Відсортувати елементи контейнера в лексикографічному порядку англійських слів.
bool ItCmp(const CTranslate &first, const CTranslate &sec) { return (first.GetIta() < sec.GetIta());}

void SortByIta(std::vector <CTranslate> &vect) {
	sort(vect.begin(), vect.end(), ItCmp);
}
//Відсортувати елементи контейнера в лексикографічному порядку італійських слів.

void TranslateEng(const std::vector <CTranslate> &vect, std::string en) {
	for (auto i : vect) {
		if (i.GetEng() == en)
			std::cout << "\n\t\t\t" << i.GetIta();
	}
}
//Вивести на консоль усі итальянскиe еквіваленти en.

void TranslateIta(const std::vector<CTranslate> &vect, std::string ita) {
	for (auto i : vect) {
		if (i.GetIta() == ita)
			std::cout << "\n\t\t\t" << i.GetEng() << std::endl;
	}
}
//Вивести на консоль усі англійські еквіваленти ita.
bool CTranslate::LoadFromCSV(char* filename, std::vector<CTranslate> &base) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Can't open the file!" << std::endl;
		return false;
	}
	std::string eng;
	std::string ital;
	std::string text;
	while (getline(file, text)) {
		CTranslate word;
		std::stringstream ss(text);
		getline(ss, eng, ';');
		word.SetEng(eng);
		getline(ss, ital, ';');
		word.SetIta(ital);
		base.push_back(word);
	}
	return true;
}
