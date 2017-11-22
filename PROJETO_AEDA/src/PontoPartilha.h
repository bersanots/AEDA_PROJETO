#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utente.h"

class PontoPartilha {
	Localizacao local;			/**< Localizacao do ponto de partilha */
	unsigned int capacidade;	/**< Capacidade do ponto de partilha */
	vector <vector<Bicicleta *> > bicicletas;	/**< Bicicletas existentes no ponto de partilha */
	string nome;				/**< Nome do ponto de partilha */
	static int UbikeNextID;		/**< Numero de identificacao da proxima bicicleta do tipo Urbana */
	static int USbikeNextID;	/**< Numero de identificacao da proxima bicicleta do tipo Urbana Simples */
	static int CbikeNextID;		/**< Numero de identificacao da proxima bicicleta do tipo Corrida */
	static int IbikeNextID;		/**< Numero de identificacao da proxima bicicleta do tipo Infantil */
public:
	PontoPartilha();	/**< Necess�rio para o overload do operador de extra��o na classe utente*/
	PontoPartilha(Localizacao spot,unsigned int storage,string name);

	void limpaVectorBike();
	friend ostream & operator <<(ostream & o, const PontoPartilha & p);
	friend istream & operator >>(istream & i, PontoPartilha & p);
	void removeBike(Bicicleta *bike);
	void adicionaBike(Bicicleta* bike);

	//Metodos Get
	static int getBikeNextId(string bike);
	Localizacao getLocal() const;
	string getNome() const;
	int getCapacidade() const;
	vector<int> getNumberOfBikes() const; // n�mero de bicicletas de cada tipo
	vector <string> getBikeTypes();
	vector <vector<Bicicleta *> > getBikes() const;

	//M�todos Set
	void setNome(string name);
	static void setBikeNextId(string bike,const int value);
	static void setBikeNextIdForward(string bike);
	static void setBikeNextIdBackward(string bike);
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo PontoPartilha nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const PontoPartilha & p)
{
	o << p.nome << '/' << p.local << '/' << p.capacidade << '[' << p.bicicletas.at(0).size() << ','
			<< p.bicicletas.at(1).size() << ',' << p.bicicletas.at(2).size() << ',' << p.bicicletas.at(3).size() << ']';
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo PontoPartilha,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, PontoPartilha & p)
{
	char b1, b2, b3, b4, b5, b6;
	unsigned int u,uc,c,inf; //4 tipos de bicicletas
	vector<Bicicleta *> v1,v2,v3,v4;
	vector <vector<Bicicleta *> > bikes{v1,v2,v3,v4};

	Bicicleta * b; //apontador gen�rico apenas para reservar espa�o no vetor

	getline(i,p.nome,'/');
	i >> p.local >> b1 >> p.capacidade >> b2 >> u >> b3 >> uc >> b4 >> c >> b5 >> inf >> b6;

	for (unsigned int k=0 ; k<u ; k++){
		bikes.at(0).push_back(b);
	}
	for (unsigned int k=0 ; k<uc ; k++){
		bikes.at(1).push_back(b);
	}
	for (unsigned int k=0 ; k<c ; k++){
		bikes.at(2).push_back(b);
	}
	for (unsigned int k=0 ; k<inf ; k++){
		bikes.at(3).push_back(b);
	}

	p.bicicletas=bikes;
	return i;
}
