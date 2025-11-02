/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:02 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:54:42 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	remove_var(char ***env, char *var_name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var_name, len) && (*env)[i][len] == '=')
		{
			if (ft_mapitem_del(env, i))
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_process **process)
{
	t_list	*ptr;
	char	*var_name;
	

	if (!process || !(*process)->envs->parent_env)
		return (0);
	ptr = (*process)->tokens->next;
	while (ptr)
	{
		var_name = (char *)ptr->content;
		remove_var(&(*process)->envs->parent_env, var_name);
		ptr = ptr->next;
	}
	return (1);
}
