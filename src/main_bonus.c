/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/23 14:17:45 by jsousa-a         ###   ########.fr       */
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
			perror(file_name);
	}
	else
	{
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd < 0 || access(file_name, W_OK))
			perror(file_name);
	}
	return (fd);
}

void	exec_child(t_pipex pipex, char *cmd, int flag, int offset)
{
	close(pipex.pipe[0]);
	if (offset > 0)
		exit (1);
	pipex.args = ft_split(cmd, ' ');
	pipex.path = get_path(pipex.path_list, pipex.args[0]);
	if (flag == 0)
	{
		if (dup2(pipex.pipe[1], STDOUT_FILENO) == -1)
			perror_exit("dup2() in exec_child");
	}
	else
	{
		if (pipex.outfile < 0)
			exit(1);
		if (dup2(pipex.pipe[1], pipex.outfile) == -1)
			perror_exit("dup2 in exec_child");
	}
	if (execve(pipex.path, pipex.args, pipex.envp))
		perror_exit("execve in exec_child");
}

int	process_cmds(t_pipex pipex, int ac, char **av, int offset)
{
	int		i;
	pid_t	child;

	i = 2;
	while (i < ac - 1)
	{
		if (pipe(pipex.pipe))
			perror_exit("pipe in process_cmds");
		child = fork();
		if (child == -1)
			perror_exit("fork() in process_cmds");
		if (child == 0 && i == ac - 2)
			exec_child(pipex, av[i], 1, offset);
		else if (child == 0)
			exec_child(pipex, av[i], 0, offset);
		close(pipex.pipe[1]);
		if (dup2(pipex.pipe[0], STDIN_FILENO) == -1)
			error_exit("dup2 in process_cmds");
		i++;
		offset = 0;
	}
	waitpid(child, &i, 0);
	return (WEXITSTATUS(i));
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		file_in_flag;

	file_in_flag = 0;
	if (ac < 5)
		error_exit("Wrong number of arguments");
	pipex.envp = envp;
	pipex.fdin = open_file(av[1], 'i');
	pipex.outfile = open_file(av[ac - 1], 'o');
	if (pipex.fdin < 0)
		file_in_flag = 1;
	else if (dup2(pipex.fdin, STDIN_FILENO) == -1)
		error_exit("dup2() file in()");
	if (pipex.outfile >= 0 && dup2(pipex.outfile, STDOUT_FILENO) == -1)
		error_exit("dup2() file out()");
	pipex.path_list = get_path_list(envp);
	file_in_flag = process_cmds(pipex, ac, av, file_in_flag);
	free_strtab(pipex.path_list);
	return (file_in_flag);
}
