/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:49:42 by fschuber          #+#    #+#             */
/*   Updated: 2015/06/07 20:53:57 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "setenv") || !ft_strcmp(str, "unsetenv"))
		return (1);
	if (!ft_strcmp(str, "printenv"))
		return (1);
	return (0);
}

int			cancel_color(void)
{
	ft_putstr("\x1b[0m");
	return (0);
}

void		handle_process(char **cmd, char ***envpptr, char **entries)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid >= 0)
		if (pid > 0)
		{
			wait(&status);
			if (status == 1024)
				builtins(cmd, envpptr);
		}
		else
			execute(entries, cmd, *envpptr);
	else
		exit(1);
}

void		color_me(int ac, char **av)
{
	char	*str;

	if (ac == 1)
		return ;
	str = av[1];
	if (!ft_strcmp("blue", str))
		ft_putstr("\x1b[34m");
	else if (!ft_strcmp("red", str))
		ft_putstr("\x1b[31m");
	else if (!ft_strcmp("yellow", str))
		ft_putstr("\x1b[33m");
	else if (!ft_strcmp("green", str))
		ft_putstr("\x1b[32m");
	else if (ft_strcmp("black", str))
	{
		ft_putstr("Sorry, the color ");
		ft_putstr(str);
		ft_putstr(" is not available\n");
	}
}
