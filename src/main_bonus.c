/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/13 14:39:36 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	open_file(char *file_name, unsigned char mode)
{
	int	fd;

	if (mode == 'i')
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0 || access(file_name, R_OK))
			perror_exit("open file_in");
	}
	else
	{
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd < 0 || access(file_name, W_OK))
			error_exit("open/create outfile");
	}
	return (fd);
}

void	exec_child(t_pipex pipex, char *cmd)
{
	close(pipex.pipe[0]);
	pipex.args = ft_split(cmd, ' ');
	pipex.path = get_path(pipex.path_list, pipex.args[0]);
	if (dup2(pipex.pipe[1], STDOUT_FILENO) == -1)
		error_exit("dup2() in exec_child");
	if (execve(pipex.path, pipex.args, pipex.envp))
		error_exit("execve in exec_child");
}

void	process_cmds(t_pipex pipex, int ac, char **av)
{
	int		i;
	int		status;
	pid_t	child;

	i = 2;
	while (i < ac - 2)
	{
		if (pipe(pipex.pipe))
			perror_exit("pipe in process_cmds");
		child = fork();
		if (child == -1)
			perror_exit("fork() in process_cmds");
		if (child == 0)
			exec_child(pipex, av[i]);
		else
		{
			close(pipex.pipe[1]);
			if (dup2(pipex.pipe[0], STDIN_FILENO) == -1)
				error_exit("dup2 in process_cmds");
			waitpid(child, &status, 0);
			if (WIFEXITED(status) == 1)
				exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		error_exit("Wrong number of arguments");
	pipex.envp = envp;
	pipex.fdin = open_file(av[1], 'i');
	pipex.outfile = open_file(av[ac - 1], 'o');
	if (dup2(pipex.fdin, STDIN_FILENO) == -1)
		error_exit("dup2() in main()");
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		error_exit("dup2() in main()");
	if (ac < 5)
		error_exit("Not enough arguments");
	pipex.path_list = get_path_list(envp);
	process_cmds(pipex, ac, av);
	pipex.args = ft_split(av[ac - 2], ' ');
	pipex.path = get_path(pipex.path_list, pipex.args[0]);
	free_strtab(pipex.path_list);
	if (execve(pipex.path, pipex.args, pipex.envp))
		error_exit("last execve in main");
	return (1);
}
