/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:47:03 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/19 21:06:44 by jsousa-a         ###   ########.fr       */
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
void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
