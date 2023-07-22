/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/22 10:11:29 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
char	**clean_args(char *str, char *file)
{
	char	**new_av;
//	char	*tmp;
//	char	*tmp2;
	
//	tmp = ft_strjoin(str, " ");
//	tmp2 = ft_strjoin(tmp, file);
//						ft_printf("File = %s\ntmp = %s\ntmp2 = %s\n", file, tmp, tmp2);
	(void) file;
	new_av = ft_split(str, ' ');
//	new_av = ft_split(tmp2, ' ');
//	free(tmp);
//	free(tmp2);
	return (new_av);
}
void	exec_child(t_pipex pipex, char *cmd)
{
	close(pipex.pipe[0]);
	pipex.args = ft_split(cmd, ' ');
	pipex.path = get_path(pipex.pathList, pipex.args[0]);
//	ft_printf("cmdPath = %s\n", pipex.path);
	dup2(pipex.infile, STDIN_FILENO);
	dup2(pipex.pipe[1], STDOUT_FILENO);
	execve(pipex.path, pipex.args, pipex.envp);
}
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int	i;
	pid_t	child;
	char	buff[1];

	int	status = 0;
	pipex.infile = open(av[1], O_RDONLY);
	i = 2;
	if (ac < 5)
		error_exit("Not enough arguments");
	if (access(av[1], R_OK))
		error_exit("Infile doesn't exist or no read-access.");
	pipex.pathList = get_path_list(envp);
	while (i < ac - 1)
	{
		pipe(pipex.pipe);
		child = fork();
		if (child == 0)
			exec_child(pipex, av[i]);
		close(pipex.pipe[1]);
		waitpid(child, &status, 0);
		dup2(pipex.pipe[0], pipex.infile);
		close(pipex.pipe[0]);
		i++;
	}
	pipex.outfile = open(av[i], O_WRONLY);
	while (read(pipex.infile, buff, 1) == 1)
		write(pipex.outfile, buff, 1);
	free_strtab(pipex.pathList);
	if (WIFSIGNALED(status))
		ft_printf("exited properly\n");
	return (0);
}
