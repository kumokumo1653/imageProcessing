/*---------------------------*/
/*                           */
/*   Option value -> value   */
/*                           */
/* 1995.10.25-12.13          */
/*                           */
/*---------------------------*/

/*--------------------*/
/*   Search Option    */
/*--------------------*/
double optionsearch(argc,argv,keyword)
	int argc;
	char *argv[];
	char *keyword;
{
	double	aa;
	int	i,flag;
	char	*endp;

	aa=0;
	flag=0;
	for(i=1;i<argc;++i){
		if(strcmp2(argv[i],keyword)==0){
			flag=1;
			break;
		}
	}
	aa=-999;
	if(flag==1){
		aa=strtod(argv[i]+strlen(keyword),&endp);
		if (endp==NULL)
			aa=-998;
	}
	return(aa);
}

/*----------------------------*/
/*   Strings Cmpare Model 2   */
/*----------------------------*/

int strcmp2(a,b)
	char *a;
	char *b;
{
	int	i,flag=0;

	for(i=0;i<=strlen(a);++i){
		if(*b=='\0')
			break;

		if(*a!=*b){
			flag=1;
			break;
		}
		++a;
		++b;
	}

	return(flag);
}
