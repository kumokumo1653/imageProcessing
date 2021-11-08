/*                                                             */
/*      Inverse (nodo-hanten) program                          */
/*                                                             */
/*      usage : inverse [Input filename] [Output filename]     */
/*                                                             */
/*      December 22  2007                                      */
/*                                                             */

#include<stdio.h>

main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;

    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");

    if(argc < 3){
	puts("usage: inverse [Input filename] [Output filename]");
	exit(-1);
    }
    
    if(fin == NULL ){
	printf("Can't open file %s\n",argv[1]);
	exit(-1);
    }
   
    while((c = getc(fin)) != EOF){    /* input image data */

	    putc(k-c,fout);            /* output the result */
    }

    fclose(fin);
    fclose(fout);
}


