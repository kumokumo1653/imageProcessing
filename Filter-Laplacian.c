#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main(int argc,char *argv[])
{
    FILE *fin,*fout;
    int c,k=255;
    int i,j;
    int x,y;
    int** src;
    int ** dst;
    int mask[3][3] = {  {1, 1, 1},
                        {1, -8, 1},
                        {1, 1, 1}}; 
    int offset[3] = {-1, 0, 1};

    if(argc < 4){
	puts("usage: laplacian [Input filename] [Output filename] [size]");
	exit(-1);
    }
    fin = fopen(argv[1],"rb");
    fout = fopen(argv[2],"wb");
    int size = atoi(argv[3]);

    //mat malloc
    src = malloc(sizeof(int*) * size);
    dst = malloc(sizeof(int*) * size);
    for(i = 0;i < size;i++){
        src[i] = malloc(sizeof(int) * size);
        dst[i] = malloc(sizeof(int) * size);
    }
    
    if(fin == NULL ){
	printf("Can't open file %s\n",argv[1]);
	exit(-1);
    }
   
    i = 0;
    j = 0;
    while((c = getc(fin)) != EOF){    /* input image data */
        src[j][i] = c;
        j++;
        if(j == size){
            i++;
            j = 0;
        }
    }

    for(i = 0; i < size;i++){
        for(j = 0; j < size; j++){
            int sum = 0;
            for(x = 0; x < 3; x++){
                for(y = 0; y < 3; y++){
                    if(i + offset[x] >= 0 && i + offset[x] < size && j + offset[y] >= 0 && j + offset[y] < size){
                        sum += mask[y][x] * src[j + offset[y]][i + offset[x]];
                    }
                }
            }
            dst[i][j] = sum;
            putc(sum < 0 ? 0 : sum > k ? 255 : sum, fout);
        }
    }


    fclose(fin);
    fclose(fout);
}


