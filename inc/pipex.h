/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:37:27 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/07/22 09:54:15 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_pipex
{
	char	*path;
	char	**pathList;
	char	**args;
	char	**envp;
	int		infile;
	int		outfile;
	int		pipe[2];
	int		input;
}				t_pipex;

void	error_exit(char *str);
char	**get_path_list(char **env);
char	*get_path(char **pathList, char *cmd);
void	free_strtab(char **strTab);
#endif
