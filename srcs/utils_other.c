/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:52 by naykim            #+#    #+#             */
/*   Updated: 2022/01/24 17:40:35 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	*excep_malloc(int leng)
{
	void	*result;

	result = malloc(leng);
	if (result == NULL)
	{
		write(2, "fatal : malloc false.\n", 22);
		exit(1);
	}
	return (result);
}

void	*excep_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
	{
		write(2, "fatal : calloc false.\n", 22);
		exit(1);
	}
	return (result);
}

void	call_pwd(t_var *var)
{
	char	*str;
	char	*tmp_str;

	if (var->pwd_now)
		free(var->pwd_now);
	str = getcwd(0, 100);
	tmp_str = ft_strdup(ft_strrchr(str, '/'));
	free(str);
	str = ft_substr(tmp_str, 1, ft_strlen(tmp_str) - 1);
	free(tmp_str);
	tmp_str = ft_strjoin(str, "$ ");
	var->pwd_now = ft_strjoin("minishell-", tmp_str);
	free(str);
	str = 0;
	free(tmp_str);
	tmp_str = 0;
}

void	printf_err(char *str)
{
	write(2, str, ft_strlen(str));
}

int	input_home_in_cd(t_var *var, t_ast *ptr)
{
	char	*tmp;

	tmp = lookup_value("HOME", 4, var->our_env);
	if (!tmp)
	{
		printf_err("minishell: cd: HOME not set\n");
		free(tmp);
		g_exitcode = 1;
		return (1);
	}
	ptr->text = ft_addonestring(ptr->text, tmp);
	free(tmp);
	return (0);
}
