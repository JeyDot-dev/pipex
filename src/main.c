/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/20 01:23:51 by jsousa-a         ###   ########.fr       */
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
int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	infile;
	int	i;
	pid_t	child;
	char	**cleanedArgs;
	char	*cmdPath;
	char	**pathList;
	char	buff[100];

	int	status = 0;
	infile = open(av[1], O_RDONLY);
	i = 2;
	if (ac < 5)
		error_exit("Not enough arguments");
	if (access(av[1], R_OK))
		error_exit("Infile doesn't exist or no read-access.");
	pathList = get_path_list(envp);
//	fd = open(av[ac - 1], O_WRONLY);
	while (i < ac - 1)
	{
		pipe(fd);
		child = fork();
		if (child == 0)
		{
								ft_printf("in child : %i\n", getpid());
			close(fd[0]);
			cleanedArgs = clean_args(av[i], av[1]);
			cmdPath = get_path(pathList, cleanedArgs[0]);
								ft_printf("in child\n");
			ft_printf("cmdPath = %s\n", cmdPath);
			dup2(infile, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			execve(cmdPath, cleanedArgs, envp);
			free(cmdPath);
			exit(status);
		}
		close(fd[1]);
		waitpid(child, &status, 0);
		dup2(fd[0], infile);
		close(fd[0]);
		i++;
	}
	read(infile, buff, 100);
		ft_printf("buffer = %s\n", buff);
	free_strtab(pathList);
	if (WIFSIGNALED(status))
		ft_printf("exited properly\n");
	return (0);
}
