#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;
    int threshold;

    if(argc < 4){
	puts("usage: binarize [Input filename] [Output filename] [threshold]");
	exit(-1);
    }
    
    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");
    threshold = atoi(argv[3]);

    
    if(fin == NULL ){
	printf("Can't open file %s\n",argv[1]);
	exit(-1);
    }
   
    while((c = getc(fin)) != EOF){    /* input image data */

	    putc((c > threshold ? k : 0),fout);            /* output the result */
    }

    fclose(fin);
    fclose(fout);
}


