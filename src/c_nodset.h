/*$Id: c_nodset.h,v 20.10 2001/10/05 01:35:36 al Exp $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@ieee.org>
 *
 * This file is part of "GnuCap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *------------------------------------------------------------------
 * structures to keep track of nodesets and ICs
 */
#ifndef NODESET_H
#define NODESET_H
/*--------------------------------------------------------------------------*/
class CS;
/*--------------------------------------------------------------------------*/
class NODESET {
private:
  std::map<int, double> _m;
public:
  void	command(CS&);
  void	add_list(CS&);
  void	rm_all();
  void	list_all()const;
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif