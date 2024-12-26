

#include <minishell.h>

void	free_mshell(t_mshell *mshell)
{
	free_ast(&mshell->ast);
	close_tmp();
	free(mshell->entry);
	mshell->ast = NULL;
}

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->entry = NULL;
	mshell->env = dup_env(env);
	mshell->token = NULL;
	mshell->ast = NULL;
	mshell->fd_tmp = -1;
	mshell->exit_code = 0;
	getcwd(mshell->path, PATH_MAX);
	mshell->hist_fd = open(".history_file", O_RDONLY, 0777);
	if (mshell->hist_fd > 0)
	{
		get_history(mshell->hist_fd);
		close(mshell->hist_fd);
	}
	setup_signals(mshell);
}

bool	repl(t_mshell *mshell)
{
	int	state;

	while (true)
	{
		set(0);
		mshell->entry = readline("mshell> ");
		if (!mshell->entry)
			return (false);
		state = start_mshell(mshell);
		if (state == 1)
		{
			mshell->exit_code = 130;
			continue ;
		}
		else if (state == 2)
			continue ;
		free_mshell(mshell);
	}
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_mshell	mshell;

	(void)ac;
	(void)av;
	init_mshell(&mshell, env);
	if (!repl(&mshell))
	{
		write(1, "exit\n", 5);
		free_mshell(&mshell);
		free_arr(mshell.env);
	}
	return (0);
}
