/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 09:59:16 by hekang            #+#    #+#             */
/*   Updated: 2021/02/18 19:35:34 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
int vec_sub_each(t_vec *a, t_vec *b)
{
    if ((a->x - b->x) < 0)
        return (FALSE);
    if ((a->y - b->y) < 0)
        return (FALSE);
    if ((a->y - b->y) < 0)
        return (FALSE);
    return (TRUE);
}

int             vec_each_len(t_vec *a, double l)
{
    if (fabs(a->x) > l)
        return (FALSE);
    if (fabs(a->y) > l)
        return (FALSE);
    if (fabs(a->z) > l)
        return (FALSE);
    return (TRUE);
}


int             square_hit(void *obj, t_ray *r, t_hit_record *rec)
{
    double      denominator; //분모
    t_square    *sq;
    t_vec       *oc;
    double      t;

    sq = ((t_square *)obj);

    // sq->p1 = vec_add(sq->origin, vec_create(sq->size / 2, sq->size / 2, sq->size / 2));
    // sq->p2 = vec_sub(sq->origin, vec_create(sq->size / 2, sq->size / 2, sq->size / 2));


    denominator = vec_dot(sq->normal, r->dir);
    if (fabs(denominator) < 0.000001)
        return (FALSE);
    oc = vec_sub(sq->origin, r->orig);
    t = vec_dot(oc, sq->normal) / denominator;
    if (t < rec->t_min || t > rec->t_max)
        return (FALSE);
    rec->p = ray_at(r, t);
    // rec->p = vec_add(rec->p, vec_mul_const(r->orig, 0.000001));


    //  (p - p0) . n = 0
    // //  vec_len(p - p0) < L / 2
    // if ((vec_dot(vec_sub(rec->p, sq->origin), sq->normal) == 0 
    //     || vec_dot(vec_sub(sq->origin, rec->p), sq->normal) == 0 )
    //     && (vec_len(vec_sub(rec->p, sq->origin)) < sq->size * pow(2, 0.5) / 2)
    //     && vec_each_len(vec_sub(rec->p, sq->origin), sq->size / 2))

    if (vec_dot(vec_sub(rec->p, sq->origin), sq->normal) == 0 
        // && (vec_len(vec_sub(rec->p, sq->origin)) < sq->size * pow(2, 0.5) / 2)
        && vec_each_len(vec_sub(rec->p, sq->origin), sq->size / 2))
    {
        rec->t = t;
        rec->normal = vec_unit(sq->normal);
        rec->color = sq->color;
        return (TRUE);
    }
    return (FALSE);

}