/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:34:27 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/19 10:41:27 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_list(char **env)
{
	int		i;
	char	**pathList;
	
	i = 0;
	j = 0;
	while (env[i] && !strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		error_exit("get_path_list : Environment/PATH not found.");
	else
		pathList = ft_split(&env[i][5], ':');
	return (pathList);
}
char	*get_path(char **pathList, char *cmd)
{
	int		i;
	int		cmdLen;
	char	*path;

	i = 0;
	cmdLen = ft_strlen(cmd);
	while (path_list[i])
	{
		path = ft_strlcat(pathList[i], cmd, ft_strlen(pathList[i]) + cmdLen);
		if (!access(path, X_OK))
			break ;
		free(path);
		i++;
	}
	i = sizeof(pathList);
	while (--i >= 0)
		free(pathList[i]);
	free(pathList);
	if (!access(path, X_OK))
		return (path);
	else
		error_exit("get_path : CMD access impossible");
}
