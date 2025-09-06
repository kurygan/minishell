/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by emetel            #+#    #+#             */
/*   Updated: 2025/09/06 15:22:08 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*init_cd_pwd_vars(t_sys *sys)
{
	t_env_var	*head;
	char		cwd[4096];

	head = create_env_var("PWD", getcwd(cwd, sizeof(cwd)), sys);
	if (!head)
		return (NULL);
	head->exported = true;
	add_cd_pwd_var(&head, "OLDPWD", NULL, sys);
	return (head);
}
