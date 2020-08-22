/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 19:32:16 by dbirtel           #+#    #+#             */
/*   Updated: 2017/04/10 09:41:54 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include <math.h>

typedef struct	s_vect
{
	float		x;
	float		y;
	float		z;
}				t_vect;

typedef struct	s_qt
{
	float		a;
	t_vect		v;
}				t_qt;

float			vec_len(t_vect v);
float			dot(t_vect a, t_vect b);
float			magnitude_qt(t_qt q);
t_qt			norm_qt(t_qt q);
t_qt			inv_qt(t_qt q);
t_qt			rot_qt(t_qt v, t_qt r);
t_qt			mult_qt(t_qt a, t_qt b);
t_vect			add_coord(t_vect a, t_vect b);
t_vect			sub_coord(t_vect a, t_vect b);
t_vect			mult_coord(t_vect a, float d);
t_vect			translate(t_vect o, t_vect v, float d);
t_vect			vec_norm(t_vect v);
t_vect			cross(t_vect a, t_vect b);

#endif
