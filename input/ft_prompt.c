/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:02:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:49:16 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_prompt(t_process *process)
{
	char	*current_path;
	char	*home_path;
	char	*buffer;
	char	*prompt;
	size_t	size_current;
	size_t  size_home;
	
	current_path = process->prompt->current_wd;
	home_path = process->prompt->home_path;
	size_current = ft_strlen(current_path);
	size_home = ft_strlen(home_path);
	if (!ft_strncmp(current_path, home_path, size_current))
	{
		prompt = ft_strjoin(">/~", PROMPT_ARROW);
		if (!prompt)
			return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		return (prompt); 
	}
	buffer = ft_strnstr(current_path, home_path, size_current) + size_home;
	prompt = ft_strjoin(">/~", buffer);
	buffer = ft_strjoin(prompt, PROMPT_ARROW);
	if (!prompt || !buffer)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (free(prompt), buffer);
}
