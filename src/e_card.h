/*$Id: e_card.h,v 20.10 2001/10/05 01:35:36 al Exp $ -*- C++ -*-
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
 * base class for anything in a netlist or circuit file
 */
#ifndef E_CARD_H
#define E_CARD_H
#include "e_node.h"
#include "e_cardlist.h"
/*--------------------------------------------------------------------------*/
// this file
class CARD;
/*--------------------------------------------------------------------------*/
// external
class CS;
class COMMON_COMPONENT;
/*--------------------------------------------------------------------------*/
class CARD : public CKT_BASE {
private:
  int		_evaliter;	// model eval iteration number
  CARD_LIST	_subckt;
  CARD*		_owner;
public: //insert, s__init, s__map
  node_t*	_n;
private:
  double	_value;		// value, for simple parts
  int		_port_count;	// actual number of port nodes
  int		_inode_count;	// actual number of internal nodes
  bool		_constant;	// eval stays the same every iteration
  //--------------------------------------------------------------------
protected:   				// traversal functions
  CARD*	   find_in_scope(const std::string& name);
  //--------------------------------------------------------------------
public:					// virtuals. -- the important stuff
  virtual char	 id_letter()const	= 0;
  virtual CARD*	 clone()const		= 0;
  virtual void	 parse(CS&)		= 0;
  virtual void	 print(OMSTREAM&,int)const = 0;
  virtual void	 expand()		{}
  virtual void	 map_nodes()		{}
  virtual void	 precalc()		{}
  virtual void	 dc_begin()		{}
  virtual void	 tr_begin()		{}
  virtual void	 tr_restore()		{}
  virtual void	 dc_advance()		{}
  virtual void	 tr_advance()		{}
  virtual bool	 tr_needs_eval()	{untested(); return false;}
  virtual void	 tr_queue_eval()	{}
  virtual bool	 do_tr()		{return true;};
  virtual void	 tr_load()		{}
  virtual double tr_review()		{return NEVER;}
  virtual void	 tr_accept()		{}
  virtual void	 tr_unload()		{}
  virtual void	 ac_begin()		{}
  virtual void	 do_ac()		{}
  virtual void	 ac_load()		{}
  //--------------------------------------------------------------------
  // virtuals defined in base, not overridden here
  // shown here only to complete the list
  //virtual double tr_probe_num(CS&)const;
  //virtual XPROBE ac_probe_ext(CS&)const;
  //--------------------------------------------------------------------
protected:				// create and destroy.
  explicit CARD();
  explicit CARD(const CARD&);
public:
  virtual  ~CARD()			{}
  //--------------------------------------------------------------------
public:					// query functions.
  static double	probe(const CARD*,const std::string&);
  int		connects_to(int node)const;
  //--------------------------------------------------------------------
protected:				// query functions. deferred inline
  bool	evaluated();
  //--------------------------------------------------------------------
public:					// query functions. virtual constant
  virtual bool	is_1port()const		{return false;}
  virtual bool	is_2port()const		{return false;}
  virtual bool	is_source()const	{return false;}
  virtual bool	f_is_value()const	{return false;}
  virtual bool	is_device()const	{return false;}
  //--------------------------------------------------------------------
public:					// query functions.
  CARD_LIST&	     subckt()		{return _subckt;}
  const CARD_LIST&   subckt()const	{return _subckt;}
  double	     value()const	{return _value;}
  int		     port_count()const	{return _port_count;}
  int		     inode_count()const	{return _inode_count;}
  const std::string  long_label()const; /* virtual */
  CARD*		     owner()const	{return _owner;}
  int		     evaliter()const	{return STATUS::iter[iTOTAL];}
  bool		     constant()const	{return _constant;}
  //--------------------------------------------------------------------
protected:				// modifiers.
  virtual void	set_slave()		{untested(); subckt().set_slave();}
  virtual void  set_value(double v)	{_value = v;}
public:
  virtual void  set_value(double v, COMMON_COMPONENT*)
					{untested(); set_value(v);}
  double* set_value()		{return &_value;}
protected:
  void	  parse_label(CS&);
  void	  parse_Label(CS&);
public:
  void	  set_owner(CARD* o)	{assert(!_owner||_owner==o); _owner=o;}
  void	  set_constant(bool c)	{_constant = c;}
protected:
  void	  set_port_count(int c)  {_port_count = c;}
  void	  set_inode_count(int c) {_inode_count = c;}
  //--------------------------------------------------------------------
  // a very bad way to do parameter passing between the device and expression
public:
  static double initial_condition;
  //--------------------------------------------------------------------
  friend class CARD_LIST;
  friend CARD_LIST::fat_iterator findbranch(CS&,CARD_LIST::fat_iterator);
};
/*--------------------------------------------------------------------------*/
inline bool CARD::evaluated()
{
  if (_evaliter == STATUS::iter[iTOTAL]){
    return true;
  }else{
    _evaliter = STATUS::iter[iTOTAL];
    return false;
  }
}
/*--------------------------------------------------------------------------*/
inline CARD_LIST::fat_iterator findbranch(CS& cmd, CARD_LIST* cl){
  return findbranch(cmd, CARD_LIST::fat_iterator(cl));
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif