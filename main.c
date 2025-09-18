# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int picoshell(char** cmds[]);

int print_cmds(char** cmds[])
{
	int i;
	int j;

	i = 0;
	while(cmds[i])
	{
		j = 0;
		while(cmds[i][j])
		{
			printf("cmds[%d][%d] = %s\n", i, j , cmds[i][j]);
			j++;
		}
		i++;
	}
	return(0);
}

int main(int argc, char **argv)
{
	int cmds_size = 1;

	for (int i = 1; i < argc; i++)
	{
		if( !strcmp(argv[i], "|"))
			cmds_size++;
	}
	char ***cmds = calloc(cmds_size + 1, sizeof(char**));
	if (!cmds)
		return(-1);

	cmds[0] = argv + 1;
	int cmds_i = 1;

	for (int i = 1; i < argc ; i++)
	{
		if(!strcmp(argv[i], "|"))
		{
			argv[i] = NULL;
			cmds[cmds_i] = argv + i + 1;
			cmds_i++;
		}
	}
	print_cmds(cmds);
	int ret = picoshell(cmds);
	if(ret)
		perror("picoshell");
	free(cmds);
	return(ret);
}
