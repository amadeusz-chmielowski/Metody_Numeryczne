function [] = mandelbrot()
[X,Y]=meshgrid(linspace(-2,1, 1000), linspace(-1.5,1.5,1000));
C=X+1i*Y;
Z=zeros(1000);
K=zeros(1000);

for k = 1:100
    Z=Z.^2+C;
    K(and(abs(Z)>2, K==0)) = 100-k;
end

imagesc(K);