/* 	
 *  	Trabalho Final EduBot - Introdução à Engenharia de Computação - ENG10031
 *  	Autores: Carolina Mattiello, Carolina Panizzi, Pedro H. F. Fleck,
 *  	Rafaela R. Favero e Thais Marcelle Dihl
*/

//main labirinto 1

using namespace std;

#include <iostream>
#include "libs/EdubotLib.hpp"


using namespace std;

#define DISTMIN 0.1
#define DISTMAX 1
#define DISTTESTE 0.5
#define VMAX 0.5
#define TROTACAO 2000
#define TESPERA 500

void andar_para_frente(EdubotLib *edubot, double sonarFrente);

void testa_bumper(EdubotLib *edubot);

void retroceder(EdubotLib *edubot);

void girar_direita(EdubotLib *edubot);

void girar_esquerda(EdubotLib *edubot);

//C:\Users\carol\Documents\Carol\ECP\2022-2\Intro a ECP\Edubot-1\ide\Maps


int main(){

	EdubotLib *edubot = new EdubotLib();

	double sonarEsquerda = 0, sonarFrente = 0, sonarDireita = 0;

	//Testa conexao do robo
	if(edubot->connect()){
		//conexao bem sucedida
		cout << "Conexao bem sucedida!" << endl;

		edubot->sleepMilliseconds(TESPERA);
		
		//enquanto ainda estiver no labirinto
		sonarEsquerda = edubot->getSonar(0);		
		sonarFrente = edubot->getSonar(3);		
		sonarDireita = edubot->getSonar(6);
		//confere se ainda está no labirinto		
		while ( (sonarFrente < DISTMAX) || (sonarDireita < DISTMAX) ){
			//testa se bumper nao estao ativados
			testa_bumper(edubot);
			//se a direita estiver livre
			while (sonarDireita > DISTTESTE){
				cout << "Direita livre" << endl;
				//testar se a frente esta livre
				while (sonarFrente > DISTTESTE){
					cout << "Direita e frente livre" << endl;
					//direita livre e frente livre
					andar_para_frente(edubot, sonarFrente);
					edubot->neutral();
					edubot->sleepMilliseconds(TESPERA);
					sonarFrente = edubot->getSonar(3);
					sonarDireita = edubot->getSonar(6);
					//testa bumper
					testa_bumper(edubot);
				}
				if (sonarDireita > DISTTESTE){
					//direita ainda livre e frente bloqueada
					cout << "Direita livre e frente bloqueada" << endl;
					girar_direita(edubot);
					edubot->sleepMilliseconds(TESPERA);
					sonarFrente = edubot->getSonar(3);
					sonarDireita = edubot->getSonar(6);
					testa_bumper(edubot);	
				}			
			}
			//direita bloqueada
			//testa se a frente esta bloqueada
			while(sonarFrente > DISTTESTE){
				cout << "Direita bloqueada e frente livre!" << endl;
				//frente livre
				andar_para_frente(edubot, sonarFrente);
				edubot->neutral();
				edubot->sleepMilliseconds(TESPERA);
				sonarFrente = edubot->getSonar(3);
				sonarDireita = edubot->getSonar(6);
				cout << sonarDireita << endl;
				//testa bumper
				testa_bumper(edubot);
			}
			if (sonarDireita < DISTTESTE){
				//confere se a direita ainda esta bloqueada
				cout << "Direita ainda bloqueada e frente bloqueada!" << endl;
				//direita bloqueada e frente bloqueada
				girar_esquerda(edubot);
				edubot->sleepMilliseconds(TESPERA);
				sonarFrente = edubot->getSonar(3);
				sonarDireita = edubot->getSonar(6);
				//testa bumper
				testa_bumper(edubot);
			}
			
		}//chave de enquanto estiver no labirinto
		
	}//chave do if connected
	
	else {
		cout << "Nao pode conectar no robo!" << endl;
	}//chave do else not connected

	return 0;

}//chave da main

void andar_para_frente(EdubotLib *edubot, double sonarFrente){
	sonarFrente = edubot->getSonar(3);
	while(sonarFrente > DISTMIN){
		edubot->move(VMAX*(sonarFrente/2));//maior a distancia, maior a velocidade
		edubot->sleepMilliseconds(TESPERA);
		sonarFrente = edubot->getSonar(3);
	}
}

void testa_bumper(EdubotLib *edubot){
	//bumper ativado retorna true
	if( (edubot->getBumper(0)) || (edubot->getBumper(1)) || (edubot->getBumper(2)) || (edubot->getBumper(3)) ){
		retroceder(edubot);		
	}
}

void retroceder(EdubotLib *edubot){
	edubot->neutral();
	edubot->move(-VMAX);
	edubot->sleepMilliseconds(TESPERA);
}

void girar_direita(EdubotLib *edubot){
	edubot->rotate(+90);
	edubot->sleepMilliseconds(TROTACAO);
	edubot->neutral();
}

void girar_esquerda(EdubotLib *edubot){
	edubot->rotate(-90);
	edubot->sleepMilliseconds(TROTACAO);
	edubot->neutral();
}
