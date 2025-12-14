/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:23:06 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:53:57 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

static int	add_split_array(t_list **tokens, char **split_tokens)
{
	int		i;
	char	*token_copy;

	i = 0;
	while (split_tokens[i])
	{
		token_copy = ft_strdup(split_tokens[i]);
		if (!token_copy)
		{
			perror("malloc");
			return (0);
		}
		ft_safeadd_tokens(tokens, &token_copy);
		i++;
	}
	return (1);
}

int	ft_add_split_tokens(t_list **tokens, char *value)
{
	char	**split_tokens;
	char	*token_copy;

	if (!value)
		return (1);
	if (ft_strchr(value, ' '))
	{
		split_tokens = ft_split(value, ' ');
		if (!split_tokens)
			return (0);
		if (!add_split_array(tokens, split_tokens))
		{
			ft_free_array(split_tokens);
			return (0);
		}
		ft_free_array(split_tokens);
	}
	else
	{
		token_copy = ft_strdup(value);
		if (!token_copy)
			return (0);
		ft_safeadd_tokens(tokens, &token_copy);
	}
	return (1);
}

int	ft_contains_variable(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i] == '=')
		return (1);
	return (0);
}

int	ft_return_value(t_process *process, char *line)
{
	char	**p_env;
	char	**s_env;
	char	*value;
	int		length;

	value = NULL;
	length = ft_strlen(line);
	p_env = process->envs->parent_env;
	s_env = process->envs->static_env;
	if (length == 1 && ft_specialvars(process, &value, *line))
	{
		ft_safeadd_tokens(&process->tokens, &value);
		return (1);
	}
	value = ft_getvar(p_env, line);
	if (value == NULL)
		value = ft_getvar(s_env, line);
	if (value == NULL)
		return (0);
	if (!ft_add_split_tokens(&process->tokens, value))
		return (0);
	free(value);
	return (1);
}
