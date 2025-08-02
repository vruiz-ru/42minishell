/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:02 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:42:07 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **remove_var(char **env, char *var_name)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], var_name, ft_strlen(var_name)))
		{
			env = ft_mapdel_item(env, i);
			break ;	
		}
		i++;
	}
	return (env);
}

int	ft_unset(t_subproc **process)
{
	t_list	*ptr;
	char	*var_name;
	

	if (!process || !(*process)->local_env)
		return (0);
	ptr = (*process)->builtins->tokens->next;
	while (ptr)
	{
		var_name = (char *)ptr->content;
		(*process)->local_env = remove_var((*process)->local_env, var_name);
		ptr = ptr->next;
	}
	return (1);
}
