# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int picoshell(char** cmds[])
{
	int pip[2];
	pid_t pid;
	int pip_in;
	int i;

	pip_in = 0;
	i = 0;
	while(cmds[i])
	{
		if(cmds[i + 1] != NULL)
		{
			if ( pipe(pip) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}

		pid = fork();
		if (pid == -1) //erreur
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0) //enfant
		{
			//redirige in
			if(pip_in != 0)
			{
				dup2(pip_in , 0);
				close(pip_in);
			}

			//redirige out
			if(cmds[i+1] != NULL)
			{
				close(pip[0]);
				dup2(pip[1], 1);
				close(pip[1]);
			}

			execvp(cmds[i][0], cmds[i]);
			perror("execvp");
			exit(1);
		}
		// pere
		if(pip_in != 0)
			close(pip_in);
		if(cmds[i+1] != 0)
		{
			close(pip[1]);
			pip_in = pip[0];
		}
		i++;
	}

	while (wait(NULL) > 0)
	{
	}
	return(0);
}
