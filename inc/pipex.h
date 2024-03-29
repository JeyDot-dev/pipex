/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:37:27 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/21 15:21:43 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*path;
	char	**path_list;
	char	**args;
	char	**envp;
	int		fdin;
	int		outfile;
	int		pipe[2];
	int		input;
}				t_pipex;

void	perror_exit(char *str);
void	error_exit(char *str);
void	error_cmd_not_found(char *str);
char	**get_path_list(char **env);
char	*get_path(char **pathList, char *cmd);
void	free_strtab(char **strTab);
#endif
