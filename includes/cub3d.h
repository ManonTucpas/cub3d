/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:34:05 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 10:01:47 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"

# define DIST 0.02
# define PI  3.141559
# define MAXTEXTURES 7
# define CHARVALID "*01234NSWE"
# define SPRITE "234"
# define TILE 27
# define SCALE 5

typedef struct	s_sprite
{
	double			x;
	double			y;
	int				texture;
	int				starty;
	int				startx;
	int				endy;
	int				endx;
	int				h;
	int				w;
	int				type;
	int				screenx;
	double			newy;
	double			dist;
	double			size;
}				t_sprite;

typedef struct	s_texture
{
	void			*img;
	char			*addr;
	int				h;
	int				w;
}				t_texture;

typedef struct	s_ray
{
	int				i;
	double			perpwalldist;
	double			camerax;
	double			dirx;
	double			diry;
	int				mapx;
	int				mapy;
	double			sidedisty;
	double			sidedistx;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				line_height;
	int				drawstart;
	int				drawend;
	int				texdir;
	int				tex_nb;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}				t_ray;

typedef struct	s_player
{
	float			x_pos;
	float			y_pos;
	char			dir;
	int				turn_dir;
	int				walk_dir;
	int				leftstep;
	int				rightstep;
	float			speed;
	double			r_speed;
	double			x_dir;
	double			y_dir;
	double			plan_x;
	double			plan_y;
	double			r_angle;
}				t_player;

typedef struct	s_mlx
{
	void	*ptr;
}				t_mlx;

typedef struct	s_img
{
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_lenght;
	int				endian;
	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color0;
}				t_img;

typedef struct	s_config
{
	int				r1;
	int				r2;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*s;
	char			*ss;
	char			*sss;
	int				f_red;
	int				f_green;
	int				f_blue;
	unsigned int	f_color;
	int				c_red;
	int				c_green;
	int				c_blue;
	unsigned int	c_color;
	int				param_ok;
	int				error;
	int				save_image;
	char			**map;
	int				height;
	int				width;
	int				nb_spr;
	double			*buff;
	int				in_config;
	char			*line;
	t_sprite		*spr;
	t_mlx			mlx;
	t_img			img;
	t_player		p;
	t_ray			r;
	t_texture		t[MAXTEXTURES];
}				t_conf;
/*
** no -> 0
** so -> 1
** we -> 2
** ea -> 3
** s  -> 4
*/
/*
** UTILS
*/
void			ft_putstr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				get_next_line(int fd, char **line);
int				args_nb(char **str);
void			get_res_max(t_conf *conf);
/*
** FREE && CLEAR
*/
void			ft_free_all(t_conf *conf);
void			free_tab(char **tab);
char			*reass_join(char *s1, char *s2, char *(*f)
				(const char *, const char *));
/*
** PARSER
*/
void			parse_map(t_conf *conf, int fd);
void			get_resolution(t_conf *conf, char *line);
void			get_path(t_conf *conf, char *line);
void			get_floor(t_conf *conf, char *str);
void			get_ceiling(t_conf *conf, char *line);
void			get_config_rgb(t_conf *conf, char *str);
void			get_config_path(t_conf *conf, char *str);
void			ft_check_ar(t_conf *conf, unsigned int i, unsigned int j);
int				is_first_line(char *str);
int				is_valid_char(char c);
void			ft_get_tab(t_conf *conf, char *mapline);
void			ft_check_inside(t_conf *conf);
/*
** INITIALIZE
*/
void			ini_conf(t_conf *conf);
void			ini_player(t_player *p);
void			ini_ray(t_ray *r);
void			initiallization_sprite(t_conf *conf);
void			ini_buff(t_conf *conf);
/*
** ERROR
*/
void			ft_error(t_conf *conf, char *str, char **tab);
/*
** TOOLS
*/
void			clean_image(t_conf *conf);
int				ft_close(t_conf *conf);
void			my_pixel_put(t_conf *conf, int x, int y, int color);
int				color_no_valid(int color);
void			save_bmp(t_conf *conf);
/*
** RAYCASTING
*/
void			launch_game(t_conf *conf);
void			create_image(t_conf *conf);
void			key_actions(t_conf *conf);
void			movement(t_conf *conf);
int				raycast(t_conf *conf);
/*
** TEXTURES
*/
void			draw_background(t_conf *conf);
void			wall_height(t_conf *conf);
void			get_text_id(t_conf *conf);
void			get_text_coord(t_conf *conf);
void			draw_texture(t_conf *conf);
void			draw_column(t_conf *conf);
/*
** SPRITES
*/
void			count_sprite(t_conf *conf);
void			get_sprites(t_conf *conf);
void			malloc_t_sprite(t_conf *conf);
void			draw_sprites(t_conf *conf);
void			sort_sprites(t_conf *conf);
/*
** BONUS
*/
void			play_sound(char c);
void			get_text_bonus(t_conf *conf);
void			print_map(t_conf *conf);

#endif
