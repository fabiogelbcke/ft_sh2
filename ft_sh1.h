/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:18:52 by fschuber          #+#    #+#             */
/*   Updated: 2015/06/07 20:55:31 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# define BUFF_SIZE 1024
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/Includes/libft.h"
# include <stdio.h>
# include <sys/types.h>

void	env(void);
char	*get_env(char *var, char **envp);
void	cd(char *path, char **envp);
void	show_env(char **envp);
void	set_env(char ***envpptr, char *var, char *value);
void	unset_env(char ***envpptr, char *var);
void	handle_process(char **cmd, char ***envpptr, char **entries);
void	color_me(int ac, char **av);
void	builtins(char **cmd, char ***envpptr);
void	execute(char **entries, char **cmd, char **envp);
int		is_builtin(char *str);
int		cancel_color(void);

#endif
