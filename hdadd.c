/*

             .BMP Head Additioner    ver0.70

                   Multi platform version.

            1995.8.18-1995.12.13
            2020.6.4 revised

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp012.h"
#include "option.h"
#include "ext.h"

/* ################ */
/*   error -> end   */
/* ################ */
void error(s)
char *s;
{
        puts("\n\n");
        puts(s);
        puts("\n\n");
        exit(1);
}


main(argc,argv)
int     argc;
char    *argv[];
{
        FILE    *fin,*fout;
        char    *bf;

        uint    n,i,bmpflag;
        double  a;

        DWORD   datatop,xsize,ysize,scan,yy;

        char    fname1[20];
        char    fname2[20],ext2[4];

	bf=(char *)malloc(4096);

        printf("\n*** BMP Head Additioner ver 0.70 by Tell me. ***\n\n");

        if(argc==1)
                error(" Use : hdadd [file name]");

        strcpy(fname1,argv[1]);

	filenamesearch(argv[1],fname2,ext2);

        strcat(fname2,".bmp");

        printf("Input  file : %s\n",fname1);
        printf("Output file : %s\n\n",fname2);

        if( (fin = fopen(fname1,"rb"))==NULL)
                error("Input file not found.");

        if( (fout= fopen(fname2,"wb"))==NULL)
                error("Output file can't open.");


        if( (a=optionsearch(argc,argv,"/r="))==-999)   a=9;
        n=1<<(uint)a;
        printf("Input size : 2^%f = %d\n\n",a,n);


/* ###### Header addition ###### */

	bf[bfType]='B';
	bf[bfType+1]='M';
	datatochar(&bf[bfSize],4,n*n+BMPHEADERsize+256*4);
	datatochar(&bf[bfReserved1],2,0);
	datatochar(&bf[bfReserved2],2,0);
	datatochar(&bf[bfOffBits],4,BMPHEADERsize+256*4);

	datatochar(&bf[biSize],4,BMPHEADERsize-14);
	datatochar(&bf[biWidth],4,n);
	datatochar(&bf[biHeight],4,n);
	datatochar(&bf[biPlanes],2,1);
	datatochar(&bf[biBitCount],2,8);
	datatochar(&bf[biCompression],4,BI_RGB);
	datatochar(&bf[biSizeImage],4,n*n);
	datatochar(&bf[biXPelsPerMeter],4,0);
	datatochar(&bf[biYPelsPerMeter],4,0);
	datatochar(&bf[biClrUsed],4,256);
	datatochar(&bf[biClrImportant],4,0);

	fwrite(bf,BMPHEADERsize,1,fout);

        for(i=0;i<=255;++i){
                bf[0]=i;
                bf[1]=i;
                bf[2]=i;
                bf[3]=0;
                fwrite(bf,4,1,fout);
        }



	fseek(fin,-n,2);

        for(yy=1;yy<=n;yy++){
            fseek(fin,n*(n-yy),0);
            fread(bf,n,1,fin);
            fwrite(bf,n,1,fout);
        }

        fclose(fin);
        fclose(fout);
 

        printf("\n Header addition completed.\n\n");

        exit(0);
}
