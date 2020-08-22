/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:07:27 by dbirtel           #+#    #+#             */
/*   Updated: 2017/05/19 00:37:48 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

float		dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}