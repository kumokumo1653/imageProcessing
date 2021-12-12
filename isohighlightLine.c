#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;
    int range;


    if(argc < 4){
	puts("usage: isohighlightLine [Input filename] [Output filename] [range]");
	exit(-1);
    }
    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");
    range = atoi(argv[3]);
    
    if(fin == NULL ){
        printf("Can't open file %s\n",argv[1]);
        exit(-1);
    }
    if(fout == NULL)puts("out");
    while((c = getc(fin)) != EOF){    /* input image data */
        if(range <= 1){
            putc(c, fout);
        }else{
            putc((int)(k * (c % range) / (range - 1)), fout);            /* output the result */
        }
    }

    fclose(fin);
    fclose(fout);
}


