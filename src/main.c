/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/31 15:29:00 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
char	**clean_args(char *str, char *file)
{
	char	**new_av;
 	(void) file;
	new_av = ft_split(str, ' ');
	return (new_av);
}
void	exec_last(t_pipex pipex, char *cmd)
{
	ft_printf("pid = %i\n", getpid());
			char	buff[100];
			ft_printf("read %i\n", read(pipex.fdin, buff, 50));
		ft_printf("buff = %s\n", buff);
		pipex.args = ft_split(cmd, ' ');
		pipex.path = get_path(pipex.pathList, pipex.args[0]);
		dup2(pipex.fdin, STDIN_FILENO);
		close(pipex.fdin);
		execve(pipex.path, pipex.args, pipex.envp);
		exit(1);

}
void	exec_child(t_pipex pipex, char *cmd)
{
	close(pipex.pipe[0]);
	pipex.args = ft_split(cmd, ' ');
	pipex.path = get_path(pipex.pathList, pipex.args[0]);
	dup2(pipex.pipe[1], STDOUT_FILENO);
	fprintf(stderr, "Pipex.path = %s\nPipex.args[0 - 2] = %s %s %s\n", pipex.path, pipex.args[0],
	pipex.args[1], pipex.args[2]);
	execve(pipex.path, pipex.args, pipex.envp);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int	i;
	pid_t	child;
	pipex.envp = envp;

	pipex.fdin = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	dup2(pipex.fdin, STDIN_FILENO);
	dup2(pipex.outfile, STDOUT_FILENO);
	i = 2;
	if (ac < 5)
		error_exit("Not enough arguments");
	if (access(av[1], R_OK))
		error_exit("Infile doesn't exist or no read-access.");
	pipex.pathList = get_path_list(envp);
	while (i < ac - 2)
	{
		pipe(pipex.pipe);
		child = fork();
		if (child == 0)
			exec_child(pipex, av[i]);
		else
		{
			close(pipex.pipe[1]);
			dup2(pipex.pipe[0], STDIN_FILENO);
			waitpid(child, NULL, 0);
		}
		i++;
	}
	pipex.args = ft_split(av[i], ' ');
	pipex.path = get_path(pipex.pathList, pipex.args[0]);
	execve(pipex.path, pipex.args, pipex.envp);
	free_strtab(pipex.pathList);
	return (0);
}
