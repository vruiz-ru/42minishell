/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:30:32 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getvar(char **envp, char *var_name)
{
	char	**split;
	char	*value;
	int		i;

	i = 0;
	split = NULL;
	value = NULL;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!ft_strncmp(split[0], var_name, ft_strlen(var_name)))
		{
            if (split[1])
			    value = ft_strdup(split[1]);
			else
                break ;
            ft_mapfree(split);
			return (value);
		}
		ft_mapfree(split);
		split = NULL;
		i++;
	}
	return (NULL);
}
