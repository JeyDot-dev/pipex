/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:34:27 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/01 04:22:54 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_list(char **env)
{
	int		i;
	char	**pathList;
	
	i = 0;
	while (env[i] && strncmp(env[i], "PATH=", 5))
	{
		i++;
	}
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
	while (pathList[i])
	{
		path = ft_calloc(ft_strlen(pathList[i]) + cmdLen + 1, sizeof(*path));
		ft_strlcat(path, pathList[i], ft_strlen(pathList[i]) + 1);
		ft_strlcat(path, "/", ft_strlen(path) + 2);
		ft_strlcat(path, cmd, ft_strlen(path) + cmdLen + 1);
		if (!access(path, X_OK))
			break ;
		free(path);
		i++;
	}
	if (!access(path, X_OK))
	{
		return (path);
	}
	else
		error_exit("get_path : CMD access impossible");
	return (NULL);
}
