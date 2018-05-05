function [dwumian] = dwumian(n, k)
dwumian = silnia(n)/(silnia(n-k)*silnia(k));
disp(dwumian);
