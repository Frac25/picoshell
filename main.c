# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main(int argc, char **argv)
{
	int cmds_size = 1;

	for (int i = 1; i < argc; i++)
	{
		if( !strcmp(argv[i], "|"))
			cmds_size++;
	}
	char ***cmds = calloc(sizeof(char***), cmds_size + 1);
	if (!cmds)
	{
		free(cmds);
		return(-1);
	}
	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i = 1; i < argc ; i++)
	{
		if(!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	}
	int ret = picoshell(cmds);
	if(ret)
		perror("picoshell");
	free(cmds);
	return(ret);
}
