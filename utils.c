/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:19:13 by fschuber          #+#    #+#             */
/*   Updated: 2015/06/07 20:36:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			get_env_size(char ***envpptr)
{
	int		i;

	i = 0;
	while ((*envpptr)[i])
		i++;
	return (i);
}

void		unset_env(char ***envpptr, char *var)
{
	char	**newenv;
	int		i;
	int		j;
	char	**split;

	i = -1;
	j = 0;
	if (!var)
	{
		ft_putstr("unsetenv: Too few arguments.\n");
		return ;
	}
	if (!get_env(var, *envpptr))
		return ;
	newenv = malloc(sizeof(char*) * (get_env_size(envpptr) + 1));
	while ((*envpptr)[++i])
	{
		split = ft_strsplit((*envpptr)[i], '=');
		if (ft_strcmp(split[0], var))
			newenv[j++] = ft_strdup((*envpptr)[i]);
		free(split);
		split = NULL;
	}
	newenv[j] = NULL;
	*envpptr = newenv;
}

char		*get_env(char *var, char **envp)
{
	int		i;
	char	**envvar;
	char	**split;

	if (var)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			split = ft_strsplit(envp[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				return (split[1]);
			}
			free(split);
			split = NULL;
			i++;
		}
	}
	return (NULL);
}

void		show_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		ft_putstr("\n");
		i++;
	}
}

void		set_env(char ***envpptr, char *var, char *value)
{
	int		i;
	char	**newenv;
	char	**split;

	i = -1;
	if (get_env(var, *envpptr))
		while ((*envpptr)[++i])
		{
			split = ft_strsplit((*envpptr)[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				(*envpptr)[i] = ft_strjoin(ft_strjoin(var, "="), value);
				return ;
			}
		}
	else
	{
		newenv = malloc ((get_env_size(envpptr) + 2) * sizeof(char *));
		while ((*envpptr)[++i])
			newenv[i] = ft_strdup((*envpptr)[i]);
		newenv[i] = ft_strjoin(ft_strjoin(var, "="), value);
		newenv[i + 1] = NULL;
		*envpptr = newenv;
	}
}
