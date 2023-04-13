/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:35:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/04/13 17:13:16 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
char	**cleaned_args(int ac, char **av)
{
	char	**new_av;
	int		i;
	int		ii;

	i = 0;
	ii = 1;
//	if (ac <= 3)
//		return (NULL);
	new_av = malloc(sizeof(*new_av) * (ac));
	while (i < ac)
	{
		if (ii == 1 || ii == ac - 1)
			//file shenanigans, continue;
		new_av[i] = ft_strdup(av[ii]);
		i++;
		ii++;
		ft_printf("boucle\n");
	}
	new_av[i] = NULL;
	return (new_av);
}
int	main(int ac, char **av, char **envp)
{
	int	fd;
//	int	ct;

	int	status = 0;
	pid_t	child;
	char	**str;
//	char	*strtest = "Un test wow";
	fd = open("test2", O_WRONLY);
	str = cleaned_args(ac, av);
//	ft_printf("%s\n", PATH);
//	ct = read(fd, str, 60);
	child = fork();
	ft_printf("PID = %i\n", getpid());
	if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		ft_printf("Me child lul\n");
		ft_printf("exec : %i\n", execve("/usr/bin/wc", str, envp));
		exit(status);
	}
	else
	{
		close(fd);
		ft_printf("Me parent lol\n");
	wait(&status);
	if (WIFEXITED(status))
		ft_printf("exited properly\n");
	}
	ft_printf("Whut\n");
//	ft_printf("print env : %s\n", envp[1]);

	return (0);
}
