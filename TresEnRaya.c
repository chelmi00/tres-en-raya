/*
 * Juego del tres en raya
 * Juegas con cruces y empiezaas
 * Los círculos juegan relativamente inteligente:
 * Intentan ganar, luego no perder y luego el centro
 *
 * @author: chelmi
 * @date inicial: 03/09/2021
 * @date final: 05/09/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void loop (char c[3][3]);
void Intro_Primera (char c[3][3]);
void Intro_Yo (char c[3][3]);
void Intro_IA (char c[3][3]);
int IA (char c[3][3], char n);
void tablero (char c[3][3]);
int ganador (char c[3][3]);
int analisis (char c[3][3], char n);

int main() {

	char c [3][3];

	loop (c);

	system ("pause");
	return 0;
}

void loop (char c[3][3]) {

	int i = 0, j;

	Intro_Primera (c);

	do {
		system ("cls");
		tablero (c);
		if (i % 2 == 0)
			Intro_Yo (c);
		else
			Intro_IA (c);
		j = ganador (c);
		i++;
	} while (i < 9 && j == 2);

	system ("cls");
	tablero (c);

	if (j == 0)
		printf ("Enhorabuena, has ganado\n\n");
	else if (j == 1)
		printf ("Oh no, has perdido\n\n");
	else
		printf ("Has empatado\n\n");

	return;
}

void Intro_Primera (char c[3][3]) {

	char aux = '1';

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			c[i][j] = aux++;
}

void Intro_Yo (char c[3][3]) {

	int aux;
	int i, j, k;

	do {
		do {
			printf ("Coloca una ficha: ");
			fflush (stdin);
			scanf ("%i", &aux);
		} while (aux < 1 || aux > 9);

		aux --;
		i = aux / 3;
		j = aux % 3;
		k = 0;

		if (c[i][j] == 'X' || c[i][j] == 'O'){
			k = 1;
			printf ("Casilla ocupada, intenta otro numero\n\n");
		}

	} while (k == 1);

	c[i][j] = 'X';
}

void Intro_IA (char c[3][3]) {

	int i, j;

	// Aquí falla algo

	int a = IA (c, 'O');
	int b = IA (c, 'X');

	if (a != 0){
		a --;
		i = a / 3;
		j = a % 3;
	}
	else if (b != 0){
		b --;
		i = b / 3;
		j = b % 3;
	}
	else if (c[1][1] == '5'){
		i = 1;
		j = 1;
	}
	else {
		int k;
		srand (time(NULL));
		do {
			k = 0;

			i = rand() % 3;
			j = rand() % 3;
			if (c[i][j] == 'X' || c[i][j] == 'O')
				k = 1;

		} while (k == 1);
	}

	c[i][j] = 'O';

}

int IA (char c[3][3], char n) {
	int c1, c2, c3, f1, f2, f3, d1, d2, a;

	c1 = 0;
	c2 = 0;
	c3 = 0;
	f1 = 0;
	f2 = 0;
	f3 = 0;
	d1 = 0;
	d2 = 0;

	for (int i = 0; i < 3; i++){
		if (c[i][0] == n)
			c1 ++;
		if (c[i][1] == n)
			c2 ++;
		if (c[i][2] == n)
			c3 ++;
		if (c[0][i] == n)
			f1 ++;
		if (c[1][i] == n)
			f2 ++;
		if (c[2][i] == n)
			f3 ++;
		if (c[i][i] == n)
			d1 ++;
		if (c[i][2 - i] == n)
			d2 ++;
	}

	a = 0;

	for (int i = 0; i < 3; i++){
		if (c1 == 2 && c[i][0] != 'X' && c[i][0] != 'O')
			a = 3 * i + 1;
		if (c2 == 2 && c[i][1] != 'X' && c[i][1] != 'O')
			a = 3 * i + 2;
		if (c3 == 2 && c[i][2] != 'X' && c[i][2] != 'O')
			a = 3 * i + 3;

		if (f1 == 2 && c[0][i] != 'X' && c[0][i] != 'O')
			a = i + 1;
		if (f2 == 2 && c[1][i] != 'X' && c[1][i] != 'O')
			a = i + 4;
		if (f3 == 2 && c[2][i] != 'X' && c[2][i] != 'O')
			a = i + 7;

		if (d1 == 2 && c[i][i] != 'X' && c[i][i] != 'O')
			a = 4 * i + 1;
		if (d2 == 2 && c[i][2 - i] != 'X' && c[i][2 - i] != 'O')
			a = 2 * i + 3;
	}
	return a;
}

void tablero (char c[3][3]) {

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (j < 2)
				printf (" %c |", c[i][j]);
			else
				printf (" %c ", c[i][j]);
		}
		if (i < 2)
			printf ("\n---+---+---\n");
	}
	printf ("\n\n");
}

int ganador (char c[3][3]) {

	int a = analisis (c,'X');
	int b = analisis (c, 'O');

	if (a == 1)
		return 0;
	if (b == 1)
		return 1;
	return 2;
}

int analisis (char c[3][3], char n) {
	int c1, c2, c3, fi, d1, d2;

	c1 = 0;
	c2 = 0;
	c3 = 0;
	d1 = 0;
	d2 = 0;

	for (int i = 0; i < 3; i++){
		fi = 0;
		if (c[i][0] == n)
			c1 ++;
		if (c[i][1] == n)
			c2 ++;
		if (c[i][2] == n)
			c3 ++;
		for (int j = 0; j < 3; j++){
			if (c[i][j] == n)
				fi ++;
			if (i == j && c[i][j] == n)
				d1 ++;
			if (i + j == 2 && c[i][j] == n)
				d2 ++;

			if (c1 == 3 || c2 == 3 || c3 == 3 || fi == 3 || d1 == 3 || d2 == 3)
				return 1;
		}
	}

	return 0;
}
