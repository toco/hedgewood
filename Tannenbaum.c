
typedef struc {
	int x,y;
} p;

#include <stdio.h>

#include <stdlib.h>

#define N 40 

int main(void) {
	int j;
	
	p r[3]= {{N,N},{2*N,0},{0,0}};
	p p= {0,0};
	
	int i=N*N*N;
	
	char *a; 
	
	a=calloc((N+1)*(N+1),sizeof(char));
	
	do {
		int q=rand()%3;
		*(a+(N-p.y+1)*(N-p.y+1)-(2*(N-p.y)-p.x+p.y)-1)='*';
		p.x=(p.x+r[q].x)/2;
		p.y=(p.y+r[q].y)/2;
	}while(i--);
	
	for(j=0; j<=N; j++) {
		int k=(N-j)-1;
		while(k-->-1)putchar(' ');
		
		for(k=0; k<=2*j;k++){
			putchar(*(a+k+(j+1)*(j+1))?*(a+k+(j+1)*(j+1)):' ');
		}
		putchar ('\n');
	}
	free(a);
	return 0;
}
