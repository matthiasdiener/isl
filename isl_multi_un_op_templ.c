/*
 * Copyright 2014      Ecole Normale Superieure
 *
 * Use of this software is governed by the MIT license
 *
 * Written by Sven Verdoolaege,
 * Ecole Normale Superieure, 45 rue d'Ulm, 75230 Paris, France
 */

#include <isl_multi_macro.h>

/* Data structure that specifies how isl_multi_*_un_op should
 * modify its input.
 *
 * "fn_el" is applied to each base expression.
 */
S(MULTI(BASE),un_op_control) {
	__isl_give EL *(*fn_el)(__isl_take EL *el);
};

/* Modify "multi" based on "control".
 */
static __isl_give MULTI(BASE) *FN(MULTI(BASE),un_op)(
	__isl_take MULTI(BASE) *multi, S(MULTI(BASE),un_op_control) *control)
{
	int i;
	isl_size n;

	n = FN(MULTI(BASE),size)(multi);
	if (n < 0)
		return FN(MULTI(BASE),free)(multi);

	for (i = 0; i < n; ++i) {
		EL *el;

		el = FN(MULTI(BASE),take_at)(multi, i);
		el = control->fn_el(el);
		multi = FN(MULTI(BASE),restore_at)(multi, i, el);
	}

	return multi;
}
