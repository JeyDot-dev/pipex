/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:34:27 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/13 14:36:33 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	**get_path_list(char **env)
{
	int		i;
	char	**path_list;

	i = 0;
	path_list = NULL;
	while (env[i] && strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		error_exit("PATH not found.");
	else
		path_list = ft_split(&env[i][5], ':');
	return (path_list);
}

char	*get_path(char **path_list, char *cmd)
{
	int		i;
	int		cmd_len;
	char	*path;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (path_list[i])
	{
		path = ft_calloc(ft_strlen(path_list[i]) + cmd_len + 1, sizeof(*path));
		ft_strlcat(path, path_list[i], ft_strlen(path_list[i]) + 1);
		ft_strlcat(path, "/", ft_strlen(path) + 2);
		ft_strlcat(path, cmd, ft_strlen(path) + cmd_len + 1);
		if (!access(path, X_OK))
			break ;
		free(path);
		i++;
	}
	if (!access(path, X_OK))
		return (path);
	else
		error_exit("CMD access impossible");
	return (NULL);
}
