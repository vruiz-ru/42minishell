/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:48:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_main *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->name)
		free(shell->name);
	if (shell)
		free(shell);
	shell = NULL;
}

void	free_builts(t_builts *ptr)
{
	if (!ptr)
		return ;
	if (ptr->tokens)
		ft_lstclear(&ptr->tokens, free);
	ptr->tokens = NULL;
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_subprocess(t_subproc *ptr)
{
	if (ptr->local_env)
		ft_mapfree(ptr->local_env);
	if (ptr->builtins->tokens)
		ft_lstclear(&ptr->builtins->tokens, free);
	if (ptr->builtins)
		free_builts(ptr->builtins);
	if (ptr->line)
		free(ptr->line);
	if (ptr->prompt)
		free(ptr->prompt);
	if (ptr->ptr_main)
		free_main(ptr->ptr_main);
	if (ptr)
		free(ptr);
	ptr = NULL;
}