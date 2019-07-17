function y = CoordinateTransformation(u,c,x)
%% Transformation function
% This function is needed for the dual track model to transforms the vector u arount the axes in c with respective angles in x.
% Input Variables:
% u [3x1] or [1x3]     vector to be transformed
% c [mx1] or [1xm]     transformation axes (1=x, 2=y, 3=z)
% x [mx1] or [1xm]     transformation angles in radian
% Output Variables:
% y [3x1] or [1x3]     transformed vector

%% Testing input vector u for errors
if ~isvector(u) || numel(u)~=3
    error('First input argument must be a vector of dimension 3.');
end

%% Testing input vectors x and c
if numel(x)~=numel(c)
    error('Dimensions of rotation angle vector and rotation coordinate vector mismatch');
end
if any(c<0)||any(c>3)
    error('Error in axis definition for transformation direction.');
end

%% Testing dimension row/column
if isrow(u)
    u=u';
    changedimension=1;
else
    changedimension=0;
end

%% Vectorrotations
for i=1:numel(c)
    if c(i)==1
        u = [1 0 0;0 cos(x(i)) sin(x(i));0 -sin(x(i)) cos(x(i))]*u;
    end
    if c(i)==2
        u = [cos(x(i)) 0 -sin(x(i));0 1 0;sin(x(i)) 0 cos(x(i))]*u;
    end
    if c(i)==3
        u = [cos(x(i)) sin(x(i)) 0;-sin(x(i)) cos(x(i)) 0;0 0 1]*u;
    end
end

%% change of dimension row/column
if changedimension==1
    y=u';
else
    y=u;
end

end

