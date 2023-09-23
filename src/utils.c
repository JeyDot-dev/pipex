/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:47:03 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/23 12:33:06 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	free_strtab(char **strTab)
{
	int	i;

	i = 0;
	while (strTab[i])
		free(strTab[i++]);
	free(strTab);
}

void	error_cmd_not_found(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putchar_fd('\n', 2);
	exit(127);
}

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(1);
}
