@echo off
tcc -j4 -Ic:\INCLUDE -Lc:\LIB -e%1 GRAPHICS.lib EGAVGA.OBJ %1
