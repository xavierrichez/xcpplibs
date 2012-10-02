/**********************************************************************************
 * Bases.h : standard declarations.
 *//*******************************************************************************
 * Copyright (C) 2005 by Xavier Richez
 * xavier[.]richez[@]laposte.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 **********************************************************************************/
#ifndef _Bases_H
#define _Bases_H

#include <iostream>
#include <cstdlib>
#include <string>

#define square(x) ((x)*(x))
#define sqroot(x) (sqrtl(x))
#define ABS(x) ((x)<0)?(-(x)):(x)
#define Epsilon 0.0000000001
#define null NULL
typedef long double real;
typedef real reel;

/// macro randomize().
/// random generator initialization.
#define rdminit() srand(time(NULL))
/// macro random(i).
/// returns an integer between 0 and i-1.
#define rdm(i) (rand()%i)

#endif
