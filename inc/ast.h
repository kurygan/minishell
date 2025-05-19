/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:43:42 by mkettab           #+#    #+#             */
/*   Updated: 2025/05/18 17:56:46 by mkettab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum {
	TOKEN_ARGS,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT
}	token_type;

#endif