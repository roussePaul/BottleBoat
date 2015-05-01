#!/usr/bin/bash

gnuplot << EOF

set term svg size 600,800
set size ratio -1
plot "traj.dat"  using 1:2 title "Simulation" with lines\
    ,"commande.dat" using 1:2 title "Trajectoire" with lines