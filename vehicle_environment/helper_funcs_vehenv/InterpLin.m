% Interpolation Linear
function y = InterpLin(DX, DY, x)
    y = DY(1) + ((DY(2) - DY(1)) / (DX(2) - DX(1))) * (x-DX(1));
end