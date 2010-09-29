/* $Id: d_mos_base.h,v 20.7 2001/09/29 05:31:06 al Exp $ -*- C++ -*-
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
 * MOS model - base for levels 1,2,3,6
 */ 
/* This file is automatically generated. DO NOT EDIT */
#ifndef D_MOS_BASE_H_INCLUDED
#define D_MOS_BASE_H_INCLUDED

#include "d_mos.h"
  enum polarity_t {pP = -1, pN = 1};
/*--------------------------------------------------------------------------*/
class SDP_MOS_BASE
  :public SDP_DIODE{
public:
  explicit SDP_MOS_BASE(const COMMON_COMPONENT*);
public:
  double l_eff;	// -23-c- actual (electrical) channel length
  double w_eff;	// --3-c- actual (electrical) channel width
  double ad;	// ----c- drain area, actual
  double as;	// ----c- source area, actual
  double cgate;	// -----b gate to channel capacitance
  double idsat;	// -----b drain junction saturation current
  double issat;	// -----b source junction saturation current
  double rd;	// -----b ohmic drain resistance
  double rs;	// -----b ohmic source resistance
  double phi;	// surface potential at strong inversion
};
/*--------------------------------------------------------------------------*/
class TDP_MOS_BASE{
public:
  explicit TDP_MOS_BASE(const DEV_MOS*);
public:
};
/*--------------------------------------------------------------------------*/
class MODEL_MOS_BASE
  :public MODEL_DIODE{
public:
  // using generated copy constructor, should be unreachable
  explicit MODEL_MOS_BASE();
  ~MODEL_MOS_BASE() {--_count;}
public: // override virtual
  bool      parse_front(CS&);
  void      parse_params(CS&);
  void      parse_finish();
  SDP_CARD* new_sdp(const COMMON_COMPONENT* c)const;
  void      print_front(OMSTREAM&)const;
  void      print_params(OMSTREAM&)const;
  void      print_calculated(OMSTREAM&)const;
  void      tr_eval(COMPONENT*)const;
public: // not virtual
  static int count() {return _count;}
private: // strictly internal
  static int _count;
public: // input parameters
  int level;	// dummy
  double is;	// bulk jct sat current
  double js;	// bulk jct sat current per sq meter
  double rsh;	// D & S diffusion sheet resistance
  double rd;	// drain ohmic resistance
  double rs;	// source ohmic resistance
  double cbd;	// 0-bias BD jct capacitance
  double cbs;	// 0-bias BS jct capacitance
  double cgso;	// GS overlap capacitance
  double cgdo;	// GD overlap capacitance
  double cgbo;	// GB overlap capacitance
  int cmodel;	// which capacitor model to use (2 or 3)
public: // calculated parameters
  polarity_t polarity;	// 
  double egap;	// energy gap at tnom
  bool needs_isub;	// 
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif