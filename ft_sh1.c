/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:44:12 by fschuber          #+#    #+#             */
/*   Updated: 2015/06/07 20:51:28 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char				**get_entry(void)
{
	int			n;
	char		*str;
	int			size;
	char		**entries;

	n = 1;
	str = malloc(sizeof(char) * BUFF_SIZE);
	n = read(0, str, BUFF_SIZE);
	str[ft_strlen(str) - 1] = '\0';
	entries = ft_strsplit(str, ';');
	if (entries[0] == NULL)
	{
		entries = malloc(sizeof(char*) * 2);
		entries[0] = malloc(sizeof(char) * 2);
		entries[0] = NULL;
		entries[1] = NULL;
	}
	return (entries);
}

void				execute(char **entries, char **cmd, char **envp)
{
	char			**paths;
	int				i;
	int				j;

	if (is_builtin(cmd[0]))
		exit(4);
	if (*entries && ft_strlen(*entries) > 0)
	{
		i = 0;
		j = 0;
		paths = ft_strsplit(get_env("PATH", envp), ':');
		while (paths[i])
			j = execve(ft_strjoin(ft_strjoin(paths[i++], "/"), cmd[0])
					, cmd, NULL);
		if (j == -1)
		{
			ft_putstr(cmd[0]);
			ft_putstr(": command not found\n");
		}
	}
	exit(2);
}

void				custom_envp_color(int ac, char **av,
									char *env_one, char ***envpptr)
{
	char			*str;

	if (env_one == NULL)
	{
		str = malloc(sizeof(char) * 1024);
		set_env(envpptr, "PWD", getcwd(str, 1024));
		set_env(envpptr, "_", ft_strjoin(str, "/ft_minishell1"));
		set_env(envpptr, "PATH", "usr/local/bin/:usr/bin:/bin:/sbin");
		set_env(envpptr, "HOME", "/");
	}
	color_me(ac, av);
}

void				builtins(char **cmd, char ***envpptr)
{
	char			*str;

	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], *envpptr);
	else if (!ft_strcmp(cmd[0], "env"))
		show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "setenv"))
		if (cmd[2] && cmd[3])
			ft_putstr("setenv: Too many arguments.\n");
		else if (!cmd[1])
			show_env(*envpptr);
		else if (!cmd[2])
			set_env(envpptr, cmd[1], "");
		else
			set_env(envpptr, cmd[1], cmd[2]);
	else if (!ft_strcmp(cmd[0], "printenv"))
		if (cmd[1] != NULL && cmd[2] != NULL)
			ft_putstr("printenv: Too many arguments.\n");
		else if (cmd[1] && get_env(cmd[1], *envpptr))
			ft_putstr(ft_strjoin(get_env(cmd[1], *envpptr), "\n"));
		else
			show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unset_env(envpptr, cmd[1]);
}

int					main(int ac, char **av, char **envp)
{
	pid_t			pid;
	int				status;
	char			**cmd;
	char			**entries;

	custom_envp_color(ac, av, envp[0], &envp);
	while (1)
	{
		if (!entries || (!*(entries)))
			ft_putstr("$> ");
		entries = get_entry();
		while (*entries)
		{
			cmd = ft_strsplit(*entries, ' ');
			if (!ft_strcmp(cmd[0], "exit"))
				return (cancel_color());
			handle_process(cmd, &envp, entries);
			entries++;
		}
	}
	return (0);
}
