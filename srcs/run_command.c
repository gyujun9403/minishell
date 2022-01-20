/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:49:23 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 16:23:00 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	only_one_command(t_var *var)
{
	run_func(var, var->ast, 1);
	free_ast_in_var(var);
}

void	run_func(t_var *var, t_ast *ptr, int flag)
{
	char	**cmds;
	int		stat_loc;

	if (!ptr->text || !ptr->text[0])
		return ;
	cmds = ptr->text;
	if (!ft_strncmp(cmds[0], "cd", 2))
		return (b_cd(var, cmds));
	if (!ft_strncmp(cmds[0], "pwd", 3))
		return (b_pwd());
	if (!ft_strncmp(cmds[0], "env", 3))
		return (b_env(var->our_env));
	if (!ft_strncmp(cmds[0], "echo", 4))
		return (b_echo(cmds));
	if (!ft_strncmp(cmds[0], "export", 6))
		return (b_export(var, cmds));
	if (!ft_strncmp(cmds[0], "unset", 5))
		return (b_unset(var, cmds));
	if (!ft_strncmp(cmds[0], "exit", 4))
		b_exit(var, 0);
	else if (flag == 1)
		b_exec_with_fork(var, cmds);
	else
		b_exec(var, cmds);
}