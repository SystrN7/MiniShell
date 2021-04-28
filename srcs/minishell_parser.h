/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/28 11:19:38 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"

# define EMPTY_QUOTE 126

typedef struct s_parse_pos
{
	int	i;
	int	index;
}				t_parse_pos;

typedef struct s_parser_ints
{
	int	j;
	int	sep_found;
}				t_parser_ints;

typedef struct s_parse_backslash
{
	int	ret;
	int	backslash;
}				t_parse_backslash;

typedef struct s_parse_mask_str
{
	char	*str;
	char	*mask;
}				t_parse_mask_str;

typedef struct s_parsing_struct
{
	t_node_binary	*root;
	t_node_binary	*node;
	t_shell_command	*str_root;
	t_shell_command	*str_struct;
}					t_parse_struct;

int					ft_no_quote(char *line, int j, t_shell_command *str_struct);
int					ft_is_separator(char *line, int j);
int					ft_separator(char *line, t_node_binary **root, int j,
						t_shell_command **str_root);
int					ft_double_quote(char *line, int j,
						t_shell_command *str_struct, int no_end_quotes);
int					ft_single_quote(char *line, int j,
						t_shell_command *str_struct);
t_shell_command		*ft_new_str_struct(void);
char				*ft_strjoin_free(char *s1, char *s2);
int					ft_cat(char *dest, char *s, int j);

void				ft_treat_var(t_shell_context *context,
						t_shell_command *command);

void				ft_catch_redirection_before(t_shell_command *cmd);
void				ft_catch_redirection(t_shell_context *context,
						t_shell_command *cmd);
int					ft_redirection_right(t_shell_command *cmd, int i);
int					ft_redirection_left(t_shell_command *cmd, int i);
char				*ft_set_var_value(char *varname, t_shell_context *context);
int					ft_strjoin_custom_argv(t_shell_command *cmd,
						t_parse_mask_str *new,
						int len[2], int index);
int					ft_strjoin_custom_file(t_redirection_list *buff,
						t_parse_mask_str *new,
						int var_value_len, int varname_len);
t_parse_mask_str	*ft_setup_mask_str(int len);
void				ft_lstadd_back_redirection(t_redirection_list **alst,
						t_redirection_list *new);
t_node_binary		*ft_treat_line(char *line);
int					ft_split_mask(t_shell_command *cmd, char c);
void				ft_is_empty_argv(t_parse_mask_str *new, int k, int j);
int					ft_is_return_code(char *varname);
t_parse_struct		*ft_setup_parse_struct(t_parse_struct	*ret);
int					ft_cat(char *dest, char *s, int j);
int					ft_root_val_null(t_node_binary **root,
						t_shell_command **str_root, char *line, int j);
int					ft_first_command(char *line, int j, t_node_binary **root);
int					ft_cpy_before_dollard_file(t_redirection_list *buff,
						t_parse_mask_str *new, int j);
int					ft_cpy_before_dollard_argv(t_shell_command *cmd,
						t_parse_mask_str *new, int j, int index);
void				ft_treat_var(t_shell_context *context,
						t_shell_command *cmd);
int					ft_replace_var_argv(t_shell_context *context,
						t_shell_command *cmd, t_parse_pos s);
void				ft_replace_filenames(t_shell_context *context,
						t_shell_command *cmd);
int					ft_strjoin_custom_argv(t_shell_command *cmd,
						t_parse_mask_str *new, int len[2], int index);
void				ft_assign_new_strings_argv(t_shell_command *cmd,
						t_parse_mask_str *final,
						t_parse_mask_str *new, int index);
void				ft_add_nonprintable_ch(char *line,
						int ret, int len, int no_end_quotes);
void				ft_fix_argv(t_shell_command *cmd);

#endif
