/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:32:19 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 22:48:46 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <libxml/tree.h>
# include <libxml/parser.h>
# include <png.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <pthread.h>
# include <float.h>
# include "libft.h"
# include "libmath.h"

# define WIDTH		800.0
# define HEIGHT		600.0

# define INTER_MAX	42000
# define THREAD		4
# define IND		0.5 / HEIGHT
# define Y_WOW		HEIGHT / 2.0 * IND
# define X_WOW		WIDTH / 2.0 * IND

# define DIFFUSE	0.4

# define PAS		4
# define MILLENIUM	25
# define ROT		M_PI / 25

# define PLANE		0
# define SPHERE		1
# define CYLINDER	2
# define CONE		3

# define SEPIA		1
# define ICE		2

# define MB_RAY		7
# define MB_TIME	0.5
# define JOUR		6

# define COSMOS		"./img_png/cosmos.png"
# define TERRE		"./img_png/terre.png"
# define LUNE		"./img_png/lune.png"
# define MERCURE	"./img_png/mercure.png"
# define VENUS		"./img_png/venus.png"
# define MARS		"./img_png/mars.png"
# define JUPITER	"./img_png/jupiter.png"

# define EXIT		65307  // esc 
# define EXPOSE		65293  // enter/return
# define ZERO		108    // L : moving cam on/off
# define UN		119    // W : rot ↓  
# define DEUX		115    // S : rot ↑
# define TROIS		97     // A : rot ←
# define QUATRE		100    // D : rot → 
# define CINQ		113    // Q : barrel ←
# define SIX		101    // E : barrel → 
# define SEPT		65361  // ← : left
# define HUIT		65363  // → : right
# define NEUF		65364  // ↓ : back
# define DIX		65362  // ↑ : forward
# define ONZE		65363  // 0 : down
# define DOUZE		32     // space : up
# define FAUCON		65505  // shift : speed
# define ANTIA		61     // +_midkeybord
# define CARTOON	99     // C
# define CARTOON_P	65451  // +_numpad
# define CARTOON_M	65453  // -_numpad
# define MOTION_B 	109    // M

typedef struct		s_base
{
	t_vect			vx;
	t_vect			vy;
	t_vect			vz;
}					t_base;

typedef struct		s_vp
{
	t_vect			dir;
	t_vect			up;
	t_vect			right;
}					t_vp;

typedef struct		s_val
{
	float			param[3];
	float			r[3];
	float			det;
}					t_val;

typedef struct		s_cam
{
	t_vect			ori;
	t_vp			b;
}					t_cam;

typedef struct		s_lim
{
	t_vect			x;
	t_vect			y;
	t_vect			z;
}					t_lim;

typedef struct		s_png
{
	png_structp		png;
	png_infop		info;
	int				width;
	int				height;
	unsigned char	color_type;
	unsigned char	bit_depth;
	unsigned char	**row_pointers;
}					t_png;

typedef struct		s_tex
{
	char			is_tex_obj;
	int				width;
	int				height;
	int				*addr;
	t_vect			ori;
	float			dim;
	float			rep_x;
	float			rep_y;
}					t_tex;

typedef struct		s_motion_b
{
	int				is_m_b_obj;
	t_vect			a;
	t_vect			b;
	t_vect			saved;
}					t_motion_b;

typedef struct		s_obj
{
	t_qt			rot;
	t_vect			ori;
	t_vect			axe;
	t_vect			col;
	t_vect			col_inv;
	t_lim			lim;
	t_lim			l;
	float			rad;
	float			refl;
	float			trans;
	float			spec;
	int				id;
	int				type;
	int				damier;
	int				sinus;
	struct s_obj	*vide;
	struct s_obj	*inv;
	t_tex			tex;
	t_base			tr_mat;
	t_motion_b		m_b;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_ray
{
	t_vect			ori;
	t_vect			dir;
	t_vect			p[2];
	t_vect			normal_hit;
	t_obj			*o_inter;
	float			inter;
	t_vect			col;
	int				norm_mult;
	int				refl;
	int				refr;
	int				c_l;
	t_vect			c_trans;
	int				bool;
}					t_ray;

typedef struct		s_light
{
	t_vect			ori;
	int				t;
	struct s_light	*next;
}					t_light;

typedef struct		s_env
{
	void			*ptr;
	void			*win;
	void			*img;
	int				*addr;
	float			amb;
	char			*filter;
	int				filter_id;
	t_cam			*c;
	t_obj			*o;
	t_light			*l;
	char			*ambi;
	char			*c_dir;
	char			*c_ori;
	char			move[14];
	char			solar_sys;
	t_obj			*astre[6];
	t_vect			trigo;
	char			effet;
	int				nb_sphere;
	int				nb_plane;
	int				nb_cone;
	int				nb_cyl;
	int				nb_cube;
	int				nb_light;
}					t_env;

typedef struct		s_data_th
{
	int				id;
	t_env			*e;
	t_obj			*o;
	t_light			*l;
	t_ray			r;
}					t_data_th;

/*
** Parsing
*/
void				ft_error(char *str, char *file_name);
t_vect				*load_vect(t_vect *v, char *s);
void				cam_init(t_env *e, xmlNodePtr noeud);
t_obj				*new_obj(t_env *e);
void				plan_set(t_env *e, xmlNodePtr noeud);
void				sphere_set(t_env *e, xmlNodePtr noeud);
void				parse(t_env *e, char *path);
void				lim_set(t_obj *o, xmlNodePtr noeud);
void				motion_blur_set(t_env *e, xmlNodePtr noeud);

/*
** Textures
*/
t_tex				load_png(char *path, t_env *e, int i);
void				sphere_tex_set(t_env *e, xmlNodePtr noeud);
void				plan_tex_set(t_env *e, xmlNodePtr noeud);
void				cyl_tex_set(t_env *e, xmlNodePtr noeud);
void				cone_tex_set(t_env *e, xmlNodePtr noeud);
int					tex(t_ray r);
int					plan_tex(t_ray r);
int					sphere_tex(t_ray r);
int					cone_tex(t_ray r);
int					cyl_tex(t_ray r);

/*
** MLX Stuff
*/
t_env				*env_init(char *path);
int					expose(t_env *e);
int					key_press(int keycode, t_env *e);
int					key_release(int keycode, t_env *e);
int					loop_hook(t_env *e);
void				loop(t_env *e);

/*
** Intersections
*/
t_vect				select_inter_func(t_data_th *th);
void				find_inter(t_ray *r, t_obj *o);
t_vect				find_color(t_ray *r, t_obj *o, t_light *light, float amb);
t_vect				inter(t_data_th *th);
void				plan_inter(t_ray *r, t_obj *o);
void				sphere_inter(t_ray *r, t_obj *o);
t_vect				antia_inter(t_data_th *th, int i, int bord);
t_vect				motion_b_inter(t_data_th *th);

/*
** Pixel
*/
void				rt(t_env *e);
t_vect				refl_trans(t_data_th *th);
int					rgb_to_hexa(t_vect col);
t_vect				hexa_to_rgb(int	col);
t_vect				mix_color(t_vect *col, int n);
t_vect				cartoon(t_vect *col, t_ray *r, int	*bord);

/*
** Realtime lol
*/
void				cam_set(t_env *e);
char				is_in_motion(t_env *e);
void				ft_solar_sys(t_env *e);

/*
** Vect And Mat
*/
void				vect_init(t_vect *v);
void				base_init(t_base *b);
t_vect				*mat_prod(t_vect *dst, t_base b, t_vect src);
t_vect				*rot(t_vect *dst, float value, t_vect n);
t_base				*transpose(t_base *mat);
t_base				*inverse(t_base *mat);
t_vect				*vect_sum(t_vect *dst, t_vect u, t_vect v);
t_vect				*vect_sub(t_vect *sub, t_vect u, t_vect v);
t_vect				*vect_multi(t_vect *dst, float k, t_vect u);
t_vect				*vect_prod(t_vect *dst, t_vect u, t_vect v);
float				dot_prod(t_vect u, t_vect v);
t_vect				*vect_set(t_vect *dst, float a, float b, float c);
t_vect				*vect_copy(t_vect *dst, t_vect src);
float				ft_dist(t_vect a, t_vect b);
t_vect				*ft_norme(t_vect *v);

/*
** Ocean & Damine
*/
void				realim_set(t_obj *o, xmlNodePtr noeud);
int					rlim(t_vect ori, t_vect dir, float dist, t_lim l);
t_vect				col_inv(t_vect color);
t_qt				compute_rot_qt(t_vect dir);
void				cone_set(t_env *e, xmlNodePtr noeud);
void				cyl_set(t_env *e, xmlNodePtr noeud);
t_ray				move_ray(t_ray ray, t_obj *obj);
void				cyl_inter(t_ray *ray, t_obj *o);
void				cone_inter(t_ray *ray, t_obj *o);
t_vect				diffuse(t_ray *r, t_vect light_dir, float dist, int type);
t_vect				get_normal(t_ray *r);
void				light_set(t_env *e, xmlNodePtr noeud);
t_vect				filter(int filter, t_data_th *th);
int					in_lim(t_vect p, t_obj *o);
t_vect				specular(t_ray *r, t_vect light_dir, float dist);
void				load_ray(t_ray *r, float dist, t_vect hit, t_obj *o);
void				load_ray_plus(t_ray *r, float dist, t_vect hit, t_obj *o);
int					hit_void(t_vect hit, t_obj *o);
void				fix_color(t_vect *color);
int					good_axis(t_vect n);
void				init_plane(t_obj *o);
void				load_plan(t_obj *o, xmlNodePtr noeud, t_env *e);
void				init_sphere(t_obj *o);
void				load_sphere(t_obj *o, xmlNodePtr noeud, t_env *e);
t_obj				*neg_obj(xmlNodePtr noeud);
int					void_sphere_inter(t_vect hit, t_obj *o);
int					void_cyl_inter(t_vect hit, t_obj *o);
int					void_cone_inter(t_vect hit, t_obj *o);
void				init_cyl(t_obj *o);
void				load_cyl(t_obj *o, xmlNodePtr noeud, t_env *e);
void				init_cone(t_obj *o);
void				load_cone(t_obj *o, xmlNodePtr noeud, t_env *e);
t_vect				damier_plane(t_obj *o, t_vect p);
t_vect				sinus_plane(t_ray *r);
void				cube_set(t_env *e, xmlNodePtr noeud);
t_vect				rfix_color(t_vect col);
void				light_process(t_ray *r, t_ray *saved, t_light *l,
					t_vect *color);
void				sommaire(t_env *e, char *scene);
void				cam_clear(t_env *e);
#endif
