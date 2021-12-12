#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;
    int min,max;


    if(argc < 5){
	puts("usage: brightnessControl [Input filename] [Output filename] [min] [max]");
	exit(-1);
    }
    
    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");
    min = atoi(argv[3]);
    max = atoi(argv[4]);
    
    if(fin == NULL ){
	printf("Can't open file %s\n",argv[1]);
	exit(-1);
    }
   
    while((c = getc(fin)) != EOF){    /* input image data */
	    putc(c < min ? 0 : c > max ? k : (int)((k * c - k * min) / (max - min)), fout);            /* output the result */
    }

    fclose(fin);
    fclose(fout);
}


