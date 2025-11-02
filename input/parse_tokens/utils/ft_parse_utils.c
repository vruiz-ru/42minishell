/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:19:55 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 21:43:25 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

static void	assign_value(char **env, char **dest, char *var_name)
{
	char	*value;
	int		idx;
	int		size;
	
	idx = 0;
	while (env && env[idx])
	{
		size = -1;
		if (ft_strchr(env[idx], '='))
			size = ft_strchr(env[idx], '=') - env[idx];
		if (size >= 0 && !ft_strncmp(env[idx], var_name, size) && \
			env[idx][size] == '=')
		{
			value = ft_strdup(ft_strchr(env[idx], '=') + 1);
			*dest = ft_strjoin_free(*dest, value);
			if (!value || !*dest)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			break ;
		}
		idx++;
	}
}

int	already_exists(char **env, char *var_name)
{
	int	idx;
	int size;
	
	idx = 0;
	while (env && env[idx])
	{
        size = -1;
        if (ft_strchr(env[idx], '='))
		    size = ft_strchr(env[idx], '=') - env[idx];
		if (size >= 0 && !ft_strncmp(env[idx], var_name, size))
			return (1);
		idx++;
	}
	return (0);
}

char	*clean_line(char *content, char token)
{
	char    *seq;
	char	*new;
	int     i;

	i = 0;
	new = NULL;
	seq = "`\"\\";
	if (token == 'n')
		seq = " tn`\"'\\*?[]#&;|<>()~";    
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr(seq, content[i + 1]))
		{
			i++;
			new = ft_addchar(new, content[i]);
		}
		else
			new = ft_addchar(new, content[i]);
		i++;
	}
	return (free(content), new);
}

void    scan_char(t_process *process, char *content, char **var_name, int *idx)
{
	char    *stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	else if (content[*idx] == '$')
	{
		(*idx)++;
		if (special_variable(process, var_name, content[*idx]))
			return ;
		while (content[*idx] && !ft_strchr(stop, content[*idx]))
		{
			*var_name = ft_addchar(*var_name, content[*idx]);
			(*idx)++;
		}
	}
	return ;
}

void	insert_value(t_process *process, char **dest, char *var_name)
{
	char	**process_env;
	char	**static_env;

	process_env = process->envs->parent_env;
	static_env = process->envs->static_env;
	if (already_exists(static_env, var_name))
		assign_value(static_env, dest, var_name);
	else if (already_exists(process_env, var_name))
		assign_value(process_env, dest, var_name);
}
