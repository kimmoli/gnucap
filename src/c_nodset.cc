/*$Id: c_nodset.cc,v 20.10 2001/10/05 01:35:36 al Exp $ -*- C++ -*-
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
 * nodeset and ic commands
 */
#include "io_.h"
#include "ap.h"
#include "c_comand.h"
#include "c_nodset.h"
/*--------------------------------------------------------------------------*/
//	void	CMD::ic(CS&);
//	void	CMD::nodeset(CS&);
//	void	NODESET::command(CS&,NODESET*);
//	void	NODESET::add_list(CS&);
//	void	NODESET::add1(int,double);
//	void	NODESET::rm_all()
//	void	NODESET::rm1(int);
//	void	NODESET::list_all()const
//	void	NODESET::list1()const
/*--------------------------------------------------------------------------*/
static NODESET iclist;
static NODESET nslist;
/*--------------------------------------------------------------------------*/
void CMD::ic(CS& cmd)
{
  iclist.command(cmd);
}
/*--------------------------------------------------------------------------*/
void CMD::nodeset(CS& cmd)
{
  nslist.command(cmd);
}
/*--------------------------------------------------------------------------*/
void NODESET::command(CS& cmd)
{
  if (cmd.end()) {
    list_all();
  }else if (cmd.pmatch("CLEAR")) {
    rm_all();
  }else{
    add_list(cmd);
  }
}
/*--------------------------------------------------------------------------*/
/* add_list: add a bunch of nodes
 */
void NODESET::add_list(CS& cmd)
{
  while (cmd.pmatch("V")) {
    int paren = cmd.skiplparen();
    int node = cmd.ctoi();
    paren -= cmd.skiprparen();
    if (paren != 0) {
      untested();
      cmd.check(bWARNING, "need )");
    }
    cmd.skipequal();
    int mark = cmd.cursor();
    double voltage = cmd.ctof();
    if (mark == cmd.cursor()) {		/* no voltage value = unset */
      _m.erase(node);
    }else{
      _m[node] = voltage;
    }
  }
  cmd.check(bWARNING, "what's this?");
}
/*--------------------------------------------------------------------------*/
/* rm_all: unset all nodes
 * but leave top allocated
 */
void NODESET::rm_all()
{
  _m.erase(_m.begin(), _m.end());
}
/*--------------------------------------------------------------------------*/
/* list_all: list all nodes set
 */
void NODESET::list_all()const
{
  for (std::map<int, double>::const_iterator
	 i = _m.begin(); i != _m.end(); ++i) {
    IO::mstdout.setfloatwidth(7) << "  V(" << i->first << ")=" << i->second;
  }
  IO::mstdout << '\n';	
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/