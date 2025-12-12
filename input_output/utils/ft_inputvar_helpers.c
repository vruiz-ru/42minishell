/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:00:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:13:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

void	ft_trimmer(char **line, char *name, int raw_val_len)
{
	char	*res;
	size_t	cut_len;

	cut_len = ft_strlen(name) + 1 + raw_val_len;
	if ((*line)[cut_len])
		res = ft_strdup(*line + cut_len);
	else
		res = ft_strdup("");
	if (!res)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	free(*line);
	*line = res;
}

int	ft_add_var(t_process *proc, char *n, char *v)
{
	char	*var;
	int		idx;

	var = ft_strjoin(n, "=");
	if (!var)
		return (free(n), 0);
	var = ft_strjoin_free(var, v);
	if (!var)
		return (free(n), 0);
	idx = ft_mapitem_index(proc->envs->static_env, var);
	if (idx >= 0)
	{
		if (!ft_mapitem_replace(&proc->envs->static_env, var, idx))
			return (free(var), free(n), 0);
	}
	else if (!ft_mapitem_add(&proc->envs->static_env, var))
		return (free(var), free(n), 0);
	return (free(var), free(n), 1);
}

int	ft_get_raw_value_len(char *line)
{
	int		i;
	bool	dq;
	bool	sq;

	i = 0;
	dq = false;
	sq = false;
	while (line[i])
	{
		if (line[i] == ' ' && !dq && !sq)
			break ;
		else if (line[i] == '"' && !sq)
			dq = !dq;
		else if (line[i] == '\'' && !dq)
			sq = !sq;
		i++;
	}
	return (i);
}

int	ft_process_assignment(t_process *p, char **line, char *name, char *val)
{
	int	raw_len;

	raw_len = ft_get_raw_value_len(ft_strchr(*line, '=') + 1);
	if (ft_strchr(val, '$'))
	{
		p->is_variable = true;
		if (!ft_tokenize_line(p, val))
			return (free(name), free(val), 0);
		ft_trimmer(line, name, raw_len);
		val = ft_construct(p->tokens, val);
		ft_lstclear(&p->tokens, free);
		p->tokens = NULL;
		p->is_variable = false;
	}
	else
		ft_trimmer(line, name, raw_len);
	return (ft_add_var(p, name, val));
}
