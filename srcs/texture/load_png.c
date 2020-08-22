/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:50:48 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:50:49 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static FILE	*init_reading(t_png *p, char *filename)
{
	FILE *fp;

	if (!(fp = fopen(filename, "rb")))
		ft_error("probleme dans l'ouverture d'un .png -> ", filename);
	p->png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!(p->png))
		exit(0);
	p->info = png_create_info_struct(p->png);
	if (!(p->info))
		exit(0);
	if (setjmp(png_jmpbuf(p->png)))
		abort();
	png_init_io(p->png, fp);
	png_read_info(p->png, p->info);
	p->width = png_get_image_width(p->png, p->info);
	p->height = png_get_image_height(p->png, p->info);
	p->color_type = png_get_color_type(p->png, p->info);
	p->bit_depth = png_get_bit_depth(p->png, p->info);
	return (fp);
}

static void	reading_option(t_png *p)
{
	if (p->bit_depth == 16)
		png_set_strip_16(p->png);
	if (p->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(p->png);
	if (p->color_type == PNG_COLOR_TYPE_GRAY && p->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(p->png);
	if (png_get_valid(p->png, p->info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(p->png);
	if (p->color_type == PNG_COLOR_TYPE_RGB ||
			p->color_type == PNG_COLOR_TYPE_GRAY ||
			p->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(p->png, 0xFF, PNG_FILLER_AFTER);
	if (p->color_type == PNG_COLOR_TYPE_GRAY ||
			p->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(p->png);
	png_read_update_info(p->png, p->info);
}

static void	read_png_file(t_png *p, char *filename)
{
	FILE	*fp;
	int		i;

	fp = init_reading(p, filename);
	reading_option(p);
	p->row_pointers =
		(unsigned char **)malloc(sizeof(unsigned char *) * p->height);
	i = -1;
	while (++i < p->height)
		p->row_pointers[i] =
			(unsigned char *)malloc(png_get_rowbytes(p->png, p->info));
	png_read_image(p->png, p->row_pointers);
	png_destroy_read_struct(&(p->png), &(p->info), NULL);
	fclose(fp);
}

static void	init_tex(t_tex *t, t_env *e)
{
	t_base	b;
	t_vect	v[2];

	t->is_tex_obj = 1;
	t->ori = e->o->ori;
	t->dim = 1;
	t->rep_x = (e->o->type != CONE) ? -1 : 1;
	t->rep_y = -1;
	b.vy = vec_norm(e->o->axe);
	v[0] = (t_vect){1, 0, 0};
	v[1] = (t_vect){0, 0, 1};
	b.vx = vec_len(cross(b.vy, v[0])) ?
		v[0] : v[1];
	vect_prod(&b.vz, b.vx, b.vy);
	vect_prod(&b.vx, b.vy, b.vz);
	e->o->tr_mat = b;
}

t_tex		load_png(char *path, t_env *e, int i)
{
	t_png	p;
	t_tex	t;
	int		j;

	read_png_file(&p, path);
	t.height = p.height;
	t.width = p.width;
	t.addr = (int *)malloc(sizeof(int) * t.height * t.width);
	while (++i < t.height)
	{
		j = -1;
		while (++j < t.width)
			*(t.addr + i * t.width + j) =
				p.row_pointers[i][j * 4] * pow(256, 2)
				+ p.row_pointers[i][j * 4 + 1] * pow(256, 1)
				+ p.row_pointers[i][j * 4 + 2];
	}
	i = -1;
	while (++i < p.height)
		free(p.row_pointers[i]);
	free(p.row_pointers);
	xmlFree(path);
	init_tex(&t, e);
	return (t);
}
