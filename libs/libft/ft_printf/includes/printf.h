/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:50:55 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/16 09:58:15 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define ABS(Value) (Value<0) ? Value * -1 : Value
# include "../src/libft/libft.h"
# include <stdarg.h>

typedef	struct		s_flags
{
	int			sign;
	long		width;
	long		length;
	int			la;
	int			plus;
	int			hash;
	int			zero;
	int			space;
	long		precision;
	int			hflag;
	int			lflag;
}					t_flags;

typedef struct		s_double
{
	long		mantis:52;
	long		expo:11;
	long		signe:1;
}					t_double;

typedef union		u_64bit
{
	double		d;
	t_double	dfloat;
}					t_64bit;

typedef struct		s_ldouble
{
	long		mantis:63;
	long		int_part:1;
	long		expo:15;
	long		signe:1;
}					t_ldouble;

typedef union		u_80bit
{
	long double		ld;
	t_ldouble		ldouble;
}					t_80bit;

typedef enum		e_cnv
{
	O_s,
	O_d,
	O_i,
	O_u,
	O_o,
	O_x,
	O_X,
	O_b,
	O_c,
	O_p,
	O_f,
	O_t,
	O_k,
	O_n,
	O_END
}					t_cnv;

typedef struct		s_func
{
	char	cnv_type;
	t_cnv	cnv;
	void	(*f)(va_list arg, int *cursor, t_flags flags);
}					t_func;

typedef union		u_typeunisgned
{
	unsigned long int	u;
	unsigned int		d;
	unsigned char		c;
	unsigned short		s;
}					t_typeunisgned;

typedef union		u_type
{
	long long int	lli;
	long int		li;
	int				i;
	short int		si;
	signed char		sc;
}					t_type;

t_func				call_func(int i);
int					ft_printf(const char *string, ...);
int					print_cnv(const char *string, va_list arg,
					int *cursor, t_flags flags);
char				detect_cnv_exist(const char *string);
int					ft_numbersize(unsigned long long number);
long unsigned int	ft_assigntypeunsigned(va_list arg, t_flags flags);
long long int		ft_assigntype(va_list arg, t_flags flags);
void				ft_printnumberbin(va_list arg, int *cursor, t_flags flags);
void				ft_printnumber(va_list arg, int *cursor, t_flags flags);
void				ft_printnumberu(va_list arg, int *cursor, t_flags flags);
void				ft_printnumberhexmin(va_list arg, int *cursor,
					t_flags flags);
void				ft_printnumberhexmaj(va_list arg, int *cursor,
					t_flags flags);
void				ft_print_nonprintable(va_list arg, int *cursor,
					t_flags flags);
void				ft_printnumberoct(va_list arg, int *cursor, t_flags flags);
void				ft_printcolor(va_list arg, int *cursor, t_flags flags);
void				ft_printtime(va_list arg, int *cursor, t_flags flags);
void				ft_printadresse(va_list arg, int *cursor, t_flags flags);
void				ft_printstring(va_list arg, int *cursor, t_flags flags);
void				ft_printchar(va_list arg, int *cursor, t_flags flags);
void				ft_printpercent(int *cursor, t_flags flags);
void				ft_putunbr(unsigned long long nbr);
void				ft_printsign(long long number, t_flags flags);
void				ft_hashprint(int **cursor, unsigned char type,
					t_flags flags);
void				ft_initflags(t_flags *flags);
void				ft_printfloat(va_list arg, int *cursor, t_flags flags);
void				ft_printldouble(va_list arg, int *cursor, t_flags flags);
void				ft_getvaluesu(t_flags *flags, int *precision, int **cursor,
					long unsigned int d);
void				ft_getvaluesd(t_flags *flags, int *precision, int **cursor,
					long long d);
int					ft_getvaluex(t_flags *fl, int **cursor, int size,
					long unsigned int d);
int					ft_getvalueo(t_flags *fl, int **cursor, int size,
					long unsigned int d);
int					ft_getvaluead(t_flags *fl, int **cursor, int size);
int					ft_assignflag(t_flags *flags, char **string);
int					ft_assignflag2(va_list arg, t_flags *flags, char **string);
char				*detect_flg(char *string, va_list arg, int *cursor,
					t_flags *flags);
long				reverse_bits(long b, int bit_len);
void				puideux(int mem, long mantis, char **n, char **count);
void				ft_foisdix(char **str, int *len);
void				puicinq(int i, long mantis, char **n, char **count);
void				ft_printsignfloat(long sign, t_flags *flags, int **cursor);
void				ft_print_nan_inf(t_64bit d, t_flags *flags, char **f);
void				ft_dprint_nan_inf(t_80bit d, t_flags *flags, char **f);
int					ft_infini(t_64bit d, char **f, t_flags *flags,
					int **cursor);
int					ft_dinfini(t_80bit d, char **f, t_flags *flags,
					int **cursor);
int					int_expo(long expo);
int					int_dexpo(long expo);
char				*int_mantis(t_64bit d);
char				*int_dmantis(t_80bit d);
char				*float_mantis(t_64bit d);
char				*ldouble_mantis(t_80bit d);
void				ft_adjust_width(t_64bit d, t_flags *flags, int **cursor,
					int i);
void				ft_dadjust_width(t_80bit d, t_flags *flags, int **cursor,
					int i);
#endif
