/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/19 16:59:11 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
char	**cleaned_args(char *str, char *file)
{
	char	**new_av;
	int		i;
	int		ii;
	int		x;

	new_av = malloc(sizeof(*new_av) * (ac));
	return (new_av);
}
int	main(int ac, char **av, char **envp)
{
	int	fd;
//	int	ct;
	pid_t	child;
	pid_t	check_pid;
	char	**str;
	char	**pathList;

	int	status = 0;
					int	j = 0;
/*					while (envp[j])
					{
						ft_printf("%s\n", envp[j]);
						j++;
					}
					*/
	if (ac < 4)
		error_exit("Not enough arguments");
	if (access(av[1], R_OK))
		error_exit("Infile doesn't exist or no read-access.");
	pathList = get_path_list(envp);
	child = 0;
	fd = open("test2", O_WRONLY);
	str = cleaned_args(ac, av);
//	ft_printf("%s\n", PATH);
//	ct = read(fd, str, 60);
	child = fork();
//	ft_printf("PID = %i\n", getpid());
//			ft_printf("Child = %i\n", child);
	if (child == 0)
	{
//		dup2(fd, STDOUT_FILENO);
//		ft_printf("Me child lul\n");
//		ft_printf("STR[1] = %s\n, envp[0] = %s\n", str[1], envp[0]);
					ft_printf("Before Execve\n");
		execve(cmd_check("/usr/bin/", str[0]), str, envp);
		ft_printf("Before child exit\n");
		exit(status);
		ft_printf("After child exit\n");
	}
	else
	{
		ft_printf("Me parent lol\n");
		check_pid = waitpid(child, &status, 0);
	}
	if (child == check_pid)
	{
		close(fd);
	if (WIFSIGNALED(status))
		ft_printf("exited properly\n");
	}
	ft_printf("CHILD PID = %i\n", child);
	ft_printf("Whut\n");
//	ft_printf("print env : %s\n", envp[1]);

	return (0);
}
