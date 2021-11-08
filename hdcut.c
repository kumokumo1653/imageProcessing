/*  hdcut070.c  

             .BMP Head Cutter     ver0.70

                   Multi platform version.

            1995.8.18-1995.12.13

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
int	argc;
char	*argv[];
{
	FILE	*fin,*fout;
	char	*bf;

	uint	n;
	double	a;

	DWORD	datatop,xsize,ysize,scan,yy;

	char	fname1[20],ext1[4];
	char	fname2[20];


	bf=(char *)malloc(4096);

	printf("\n*** BMP Head Cutter ver 0.70 by Tell me. ***\n\n");

	if(argc==1)
		error(" Use : hdcut [file name]");

	filenamesearch(argv[1],fname1,ext1);

	strcpy(fname2,fname1);
	strcat(fname1,".bmp");
	strcat(fname2,".inc");

	printf("Input  file : %s\n",fname1);
	printf("Output file : %s\n\n",fname2);

	if( (fin = fopen(fname1,"rb"))==NULL)
		error("Input file not found.");

	if( (fout= fopen(fname2,"wb"))==NULL)
		error("Output file can't open.");


	if( (a=optionsearch(argc,argv,"/r="))==-999 || a==-998)   a=9;

	n=1<<(uint)a;

	printf("Output size : 2^%f = %d\n\n",a,n);

/* ###### Header cut ###### */

	fread(bf,BMPHEADERsize,1,fin);

	if( bf[bfType]!='B' || bf[bfType+1]!='M' )
		error("Not BMP file !");

	if( chartodata(&bf[biBitCount],2)!=8 )
		error("Pixel size not '8' !");

	if( chartodata(&bf[biCompression],4)!=BI_RGB)
		error("Data is compressed !");

	xsize = chartodata(&bf[biWidth],4);
	ysize = chartodata(&bf[biHeight],4);

printf("bmp header checked.\n");

	datatop = chartodata(&bf[bfOffBits],4) - BMPHEADERsize;

	if( datatop != 0){
		fread(bf,(uint)datatop,1,fin);
		printf("Palette read Ok!\n");
	}

	printf("\n");

	printf("Width    : %ld\n",xsize);
	printf("Height   : %ld\n",ysize);

	if(xsize<n || ysize<n)
		error("Target data is small !");

	scan = (xsize + 3) & 0xfffc;

	fseek(fin,-scan,2);

	for(yy=n;yy;yy--){
		fread(bf,(uint)scan,1,fin);
		fwrite(bf,n,1,fout);

		fseek(fin,-scan*2,1);
	}

	fclose(fin);
	fclose(fout);
 

	printf("\n Header cuting completed.\n\n");

	exit(0);
}
		
