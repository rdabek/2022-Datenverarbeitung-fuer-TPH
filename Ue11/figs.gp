set size square
set xrange [-25:50]
set yrange [-25:50]
do for [i=1:8] {
  set style line i linewidth 2.5
}
plot 'Diamant' w l, 'Halo' w l, 'Spitz' w l, 'Wuschel' w l, \
'DiamantMove' w l, 'HaloMove' w l, 'SpitzMove' w l, 'WuschelMove' w l

