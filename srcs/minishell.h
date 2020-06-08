/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:33:35 by pramella          #+#    #+#             */
/*   Updated: 2020/06/08 18:53:46 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/srcs/libft.h"
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>

# define BUFFER_TRM 	3
# define REDIRECT		3
# define PIPE			4

# define CLR_GREEN   	"\x1b[32m"
# define CLR_CYAN    	"\x1b[36m"
# define CLR_RESET   	"\x1b[0m"

# define INIT 1
# define PULL 2

/*
** STRUCTS
*/

typedef struct		s_cmd
{
	t_list			*token;
	t_list			*file_in;
	t_list			*file_out;
	int				std_in;
	int				std_out;
	int				fd_copy_in;
	int				fd_copy_out;
	int				p_in[2];
	int				p_out[2];
	int				append;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				set;
	struct s_env	*next;
}					t_env;

typedef struct		s_dlst
{
	void			*data;
	struct s_dlst	*prev;
	struct s_dlst	*next;
}					t_dlst;

typedef struct		s_trmkey
{
	char			*on;
	char			*up;
	char			*right;
	char			*del;
	char			*delk;
	char			*left;
	char			*clear;
	char			*mov_csr;
	char			*save;
	char			*reset;
}					t_trmkey;

typedef struct		s_cnt
{
	unsigned int	s;
	char			*save;
}					t_cnt;

typedef struct		s_normcpy
{
	int				i;
	int				w;
	int				a;
}					t_normcpy;

typedef struct		s_all
{
	t_cmd			*cmd;
	t_env			*env;
	t_dlst			*hst;
	char			*hst_path;
	t_dlst			*act_hst;
	t_trmkey		*term_key;
	t_cnt			*spc;
	struct termios	old_term;
	struct termios	new_term;
	int				last_exit;
	char			*line;
	t_list_fd		*s_head;
	int				hst_on;
}					t_all;

/*
** PARSING
*/

t_cmd				*parsing(char *line, t_env *env, int *last_exit);
t_env				*parse_env(char **ev);
size_t				get_non_escaped(char *line, size_t start, char *sep);
size_t				get_non_escaped2(char *line, size_t start, char *sep);

void				parse_dollar(t_cmd *cmd, t_env *env, int last_exit);
void				parse_pipe(t_cmd *cmd, t_list *token, int ret);
void				parse_redirect(t_cmd *cmd, t_list *token, int ret);

int					valid_syntax(char *line);
void				rm_parsed_redirects(t_cmd *cmd);
void				rm_quotes(t_cmd *cmd);
size_t				find_char(char *s, char c);
int					is_first_char(char *str, char *set);
int					is_last_char(char *str, char *set);

/*
** BUILTINS
*/

int					is_builtin(char *name);
int					builtin_cd(t_env *env, t_list *tkn);
int					builtin_echo(t_list *tkn);
int					builtin_env(t_env *env);
void				builtin_exit(t_all *gbl, t_list *tkn);
int					builtin_export(t_env *env, t_list *tkn);
int					builtin_pwd(void);
int					builtin_unset(t_env **env, t_list *tkn);

/*
** EXECUTION
*/

void				execution(t_all *gbl, t_cmd *cmd);
void				handle_execve(t_all *gbl, t_cmd *cmd, char *path);
void				set_redirect_fd(t_cmd *cmd, int std_fd);
void				set_builtin_pipe(t_cmd *cmd);
void				set_cmd_pipe(t_cmd *cmd);
void				set_read_write_pipe(t_cmd *cmd);
char				*locate_executable(t_env *env, char *name);

/*
** HISTORY
*/

t_dlst				*check_history(t_all *gbl);
t_dlst				*ft_newdlst(void *ctn);
t_dlst				*ft_dlstadd_back(t_dlst **hst, void *ctn);
void				ft_dlstiter(t_dlst *hst);
void				ft_dlstiter_up(t_dlst *hst);
int					ft_dlst_save(char *filename, t_dlst *hst);
void				ft_dlstclear(t_dlst **fst);

/*
**	TERMINAL
*/

/*
**	SET_TERMINAL.C
*/
t_trmkey			*init_termcap(void);

/*
**	SET_TERMINAL2.C
*/
void				init_terminal(t_all *gbl);
t_cnt				*init_cnt(void);
int					is_only_whitespace(char *line);

/*
**	TERMINAL_UTILS.C
*/
char				*check_move(char *buf, t_all *gbl, char **line);
char				*dup_key(char *buf);
void				move_cursor_left(unsigned int *s, char *left);

/*
**	TERMINAL_UTILS2.C
*/
char				*dup_key(char *buf);
void				move_cursor_left(unsigned int *s, char *left);
void				check_home(t_all *gbl, char *buf);
void				check_end(t_all *gbl, char *buf, char **line);
char				*empty_new_line(char **line, char *buf);

/*
**	TERMINAL_GNL.C
*/
int					trm_get_next_line(int fd, char **line, t_all *gbl);
char				*trm_substr(char const *s, unsigned int start, size_t len);

/*
**	TERMINAL_GNL_UTILS.C
*/
size_t				trm_strlen_gnl(const char *s);
char				*trm_strjoin_gnl(char const *s1, char const *s2);
char				*trm_cleanbuf_gnl(char *str);
void				trm_lstclear_gnl(int fd, t_list_fd **head);

/*
**	EDIT_LINE.C
*/
void				add_letter(char **line, char c, size_t h);
char				*add_print(char *buf, t_all *gbl,
					char **line, int *padding_letter);

/*
**	COPY_PASTE.C
*/
int					check_copy(t_all *gbl, char *buf, char **line);
void				add_word(char **line, char *str, int h);

/*
**	COPY_PASTE2.C
*/
void				check_paste(t_all *gbl, char *buf, char **line);

/*
**	BACKSPACE.C
*/
char				*trm_backspace(t_all *gbl, char **line, char *buf);

/*
**	KEY_RIGHT.C
*/
void				display_right(int i, char **line);
void				check_key_right(t_all *gbl, char *buf, char **line);

/*
**	KEY_LEFT.C
*/
void				check_key_left(t_all *gbl, char *buf);

/*
**	KEY_UP.C
*/
void				check_key_up(t_all *gbl, char *buf, char **line);

/*
**	KEY_DOWN.C
*/
void				check_key_down(t_all *gbl, char *buf, char **line);
int					check_file_history(void);

/*
** UTILS
*/
void				display_prompt(t_env *env);
void				parse_var_declaration(t_cmd *cmd, t_list **tk, t_env *env);
int					is_var_declaration(char *str);

/*
**	SIGNAL.C
*/
void				sig_main(int sig);
void				sig_child(int sig);
void				sig_quit(int sig);

/*
**	MINISHELL.C
*/
t_all				*cp_gbl(int flg);

void				free_all(t_all *gbl);
void				free_cmd(t_cmd *cmd);
void				free_env(t_env *env);

t_cmd				*cmd_new(void);
t_cmd				*cmd_last(t_cmd **begin);
void				cmd_add_back(t_cmd **begin, char *id);
void				tkn_add_back(t_cmd **begin, char *id);
t_env				*get_env(t_env *env, char *key);
t_env				*env_new(char *key, char *value, int set);
int					env_size(t_env *env);
void				env_add_back(t_env **begin, t_env *new);
void				set_env_value(t_env *env, char *str);

#endif
