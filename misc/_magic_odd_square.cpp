#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef long long i64;

i64 n;
int cuadrado[101][101];

void CuadradoMagico(i64 x)
{
    int numero = 1;
    int fila = 0;
    int columna = x / 2;
    bool caso;
    while (numero <= x*x)
    {
        cuadrado[fila][columna] = numero;
        caso = false;
        if (fila==0 && columna!=x-1 && !caso)
        {
            fila = x - 1;
            columna++;
            caso=true;
        }
        if (fila==0 && columna==x-1 && !caso)
        {
            fila++;
            caso = true;
        }
        if (fila!=0 && columna==x-1 && !caso)
        {
            fila--;
            columna = 0;
            caso = true;
        }
        if (!caso && cuadrado[fila - 1][columna + 1] !=0)
        {
            fila++;
            caso = true;
        }
        if (!caso && cuadrado[fila - 1][columna + 1] == 0)
        {
            fila--;
            columna++;
            caso = true;
        }
        numero++;
    }
}


int main()
{
	scanf("%lld",&n);
	CuadradoMagico(n);
	for(int i = 0;i<n;i++ )
	{
		for(int j = 0 ;j< n;j++)
		{
			if(j == 0)printf("%d",cuadrado[i][j]);
			else printf(" %d",cuadrado[i][j]);
		}
		printf("\n");
	}

}

