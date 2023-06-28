/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/06/27 12:51:46 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
char	*cmd_check(char *path, char *cmd)
{
	char	*result;
	int		size;

	size = ft_strlen(path) + ft_strlen(cmd);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (result);
	ft_strlcat(result, path, ft_strlen(path) + 1);
	ft_strlcat(result, cmd, size + 1);
					ft_printf("path = %s, cmd = %s\nresult == %s\n", path, cmd, result);
	return (result);
}
char	**cleaned_args(int ac, char **av)
{
	char	**new_av;
	int		i;
	int		ii;
	int		x;

	x = 0;
	i = 0;
	ii = 1;
//	if (ac <= 3)
//		return (NULL);
	new_av = malloc(sizeof(*new_av) * (ac));
	while (ii < ac)
	{
		if (ii == 1 || ii == ac - 1)
			//file shenanigans, continue;
		new_av[i] = ft_strdup(av[ii]);
		i++;
		ii++;
	}
	new_av[i] = NULL;
//	ft_printf("AC = %i, i = %i \n", ac, i);
	while (new_av[x])
	{
//		ft_printf("new_av %i = %s\n", x, new_av[x]);
		x++;
	}
	return (new_av);
}
int	main(int ac, char **av, char **envp)
{
	int	fd;
//	int	ct;

	int	status = 0;
	pid_t	child;
	pid_t	check_pid;
	child = 0;
	char	**str;
//	char	*strtest = "Un test wow";
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
		execve(cmd_check("/usr/bin/", str[0]), str, envp);
//				printf("T33333ST \n");
		exit(status);
	}
	ft_printf("Wait...\n");
	check_pid = wait(&status);
	if (child == check_pid)
	{
		close(fd);
		ft_printf("Me parent lol\n");
	if (WIFSIGNALED(status))
		ft_printf("exited properly\n");
	}
	ft_printf("Whut\n");
//	ft_printf("print env : %s\n", envp[1]);

	return (0);
}
