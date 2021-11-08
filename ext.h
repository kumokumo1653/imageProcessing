/*  extend file name               */
/*                                 */
/*  kakuchousi bunri               */
/*                                 */
/*  must include <string.h> in master program */

int filenamesearch(argv,name,ext)
char *argv;
char *name;
char *ext;
{
	char	*ptr;
	int	i;

	*ext='\0';
	i=-1;
	strcpy(name,argv);
	if( (ptr=(char *)strchr(name,'.'))!=NULL){
		*ptr='\0';
		strcpy(ext,ptr+1);
		i=0;
	}

	return(i);
}

