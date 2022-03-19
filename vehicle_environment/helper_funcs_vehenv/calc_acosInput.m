function arg = calc_acosInput(a, b)
% calculate normalized dot product and enforce result to be within limits
% [-1, 1] to avoid acos function throwing an error caused by numerical
% inaccuracy

    expr = dot(a,b)/(norm(a)*norm(b));

    % fix to avoid error due to numerical inaccuracy in combination with
    % acos calculation
    arg = max(min(expr, 1.0), -1.0);

end
