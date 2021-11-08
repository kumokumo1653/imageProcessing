#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;
    int histogram[256];
    int i;
    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");

    for(i = 0; i < 256; i++){
        histogram[i] = 0;
    }
    if(argc < 3){
	puts("usage: inverse [Input filename] [Output filename]");
	exit(-1);
    }
    
    if(fin == NULL ){
	printf("Can't open file %s\n",argv[1]);
	exit(-1);
    }
   
    while((c = getc(fin)) != EOF){    /* input image data */
        fprintf(fout, "%d,", c);
    }

    fclose(fin);
    fclose(fout);
}


