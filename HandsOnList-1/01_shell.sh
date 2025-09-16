#============================================================================
#Name : 1a,1b,1c Shell
#Author : Prasanna Kumar M
#Description : Shell Program to Perform Hardlink,Softlink and FIFO  
#Date: 29th Aug, 2025.
#============================================================================

#1a
ln -s source.txt softLink.txt

#1b
ln source.txt hardLink.txt

#1c
mkfifo fifo
