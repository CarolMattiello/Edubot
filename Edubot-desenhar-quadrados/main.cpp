/*
 * EDUBOT HELLO WORLD EXAMPLE
 * @Author: Maik Basso <maik@maikbasso.com.br>
*/

#include <iostream>
#include "libs/EdubotLib.hpp"

using namespace std;

int main(){
	
	double x = 0.5;
	double y = 0.5;
	int rounds = 3;
	
	EdubotLib *edubot = new EdubotLib();
	
	if (edubot->connect())
	{
		cout << "Conexao bem sucedida" << endl;
		
		edubot->sleepMilliseconds(100);

		//desenha o numero de quadrados do loop definido na variavel
		//desenha se couber no limite da sala
		while (rounds > 0 && x < 2 && y < 2){
			
			//anda ate limite x positivo
			while (edubot->isConnected() && edubot->getX() < x)
			{	
				edubot->move(0.2);
				edubot->sleepMilliseconds(100);
				edubot->getX();
			}
			edubot->rotate(+90);
			edubot->sleepMilliseconds(1200);
			edubot->neutral();
	
			//anda ate limite y negativo
			while (edubot->isConnected() && -(edubot->getY()) < y)
			{	
				edubot->move(0.2);
				edubot->sleepMilliseconds(100);
				edubot->getY();
			}
			edubot->rotate(+90);
			edubot->sleepMilliseconds(1200);
			edubot->neutral();
	
			//anda ate limite x zerar
			while (edubot->isConnected() && edubot->getX() > 0)
			{	
				edubot->move(0.2);
				edubot->sleepMilliseconds(100);
				edubot->getX();
			}
			edubot->rotate(+90);
			edubot->sleepMilliseconds(1200);
			edubot->neutral();
	
			//anda ate limite y zerar
			while (edubot->isConnected() && -(edubot->getY()) > 0)
			{	
				edubot->move(0.2);
				edubot->sleepMilliseconds(100);
				edubot->getY();
			}
			edubot->rotate(+90);
			edubot->sleepMilliseconds(1200);
			edubot->neutral();
	
			//dobra x e y para a proxima rodada
			x = x*2;
			y = y*2;
			rounds--;
		}

		edubot->stop();
	} 
	
	else
	{
		cout << "Conexao falhou" << endl; 	
	
	}

	return 0;
}

