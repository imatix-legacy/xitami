@echo off
:-
:-  Build script for iMatix SFL Package, for generic MS-DOS.
:-  Requires the iMatix 'c' batch file.
:-
:-  Generated by Otto v2.2 from buildsfl.txt on 100/04/01, 16:20:25
:-  For more info see Otto documentation at http://www.imatix.com.
:-  Bug reports & questions to <ph@imatix.com>
:-  ---------------------------------------------------------------
:-
echo Building sfl.h header file...

:-  delete sfl.h
if exist sfl.h del sfl.h
rem>sfl.h

:-  append sflhead.h  sfl.h
type sflhead.h >> sfl.h

:-  append prelude.h  sfl.h
type prelude.h >> sfl.h

:-  append sflvers.h  sfl.h
type sflvers.h >> sfl.h

:-  append sflbits.h  sfl.h
type sflbits.h >> sfl.h

:-  append sflcomp.h  sfl.h
type sflcomp.h >> sfl.h

:-  append sflcons.h  sfl.h
type sflcons.h >> sfl.h

:-  append sflconv.h  sfl.h
type sflconv.h >> sfl.h

:-  append sflcryp.h  sfl.h
type sflcryp.h >> sfl.h

:-  append sfldate.h  sfl.h
type sfldate.h >> sfl.h

:-  append sflexdr.h  sfl.h
type sflexdr.h >> sfl.h

:-  append sflfind.h  sfl.h
type sflfind.h >> sfl.h

:-  append sflfile.h  sfl.h
type sflfile.h >> sfl.h

:-  append sfllang.h  sfl.h
type sfllang.h >> sfl.h

:-  append sfllbuf.h  sfl.h
type sfllbuf.h >> sfl.h

:-  append sfllist.h  sfl.h
type sfllist.h >> sfl.h

:-  append sflmath.h  sfl.h
type sflmath.h >> sfl.h

:-  append sflmesg.h  sfl.h
type sflmesg.h >> sfl.h

:-  append sflmem.h   sfl.h
type sflmem.h >> sfl.h

:-  append sflmime.h  sfl.h
type sflmime.h >> sfl.h

:-  append sflnode.h  sfl.h
type sflnode.h >> sfl.h

:-  append sfldir.h   sfl.h
type sfldir.h >> sfl.h

:-  append sflslot.h  sfl.h
type sflslot.h >> sfl.h

:-  append sflstr.h   sfl.h
type sflstr.h >> sfl.h

:-  append sflsock.h  sfl.h
type sflsock.h >> sfl.h

:-  append sflsymb.h  sfl.h
type sflsymb.h >> sfl.h

:-  append sflproc.h  sfl.h
type sflproc.h >> sfl.h

:-  append sflsyst.h  sfl.h
type sflsyst.h >> sfl.h

:-  append sflhttp.h  sfl.h
type sflhttp.h >> sfl.h

:-  append sflini.h   sfl.h
type sflini.h >> sfl.h

:-  append sflenv.h   sfl.h
type sflenv.h >> sfl.h

:-  append sfltok.h   sfl.h
type sfltok.h >> sfl.h

:-  append sfltree.h  sfl.h
type sfltree.h >> sfl.h

:-  append sfltron.h  sfl.h
type sfltron.h >> sfl.h

:-  append sfluid.h   sfl.h
type sfluid.h >> sfl.h

:-  append sflxml.h   sfl.h
type sflxml.h >> sfl.h

:-  append sflxmll.h  sfl.h
type sflxmll.h >> sfl.h

:exit
:-- end script
