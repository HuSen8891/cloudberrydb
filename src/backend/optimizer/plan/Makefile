#-------------------------------------------------------------------------
#
# Makefile--
#    Makefile for optimizer/plan
#
# IDENTIFICATION
#    src/backend/optimizer/plan/Makefile
#
#-------------------------------------------------------------------------

subdir = src/backend/optimizer/plan
top_builddir = ../../../..
include $(top_builddir)/src/Makefile.global

BLD_TOP = $(top_builddir)/..

OBJS = \
	analyzejoins.o \
	createplan.o \
	initsplan.o \
	joinpartprune.o \
	planagg.o \
	planmain.o \
	planshare.o \
	planner.o \
	setrefs.o \
	subselect.o \
	transform.o

ifeq ($(enable_orca),yes)
OBJS += orca.o
endif

include $(top_srcdir)/src/backend/common.mk
