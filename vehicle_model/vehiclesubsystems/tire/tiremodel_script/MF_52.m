function [FX,FY,MX,MY,MZ] = MF_52(FZ, KAPPA, ALPHA, GAMMA, VX, par_TIR, mounted_side)

%% Spiegelung der Reifencharakteristik

varsign = sign(par_TIR.TYRESIDE.*mounted_side+0.1);    %Vorzeichen entsprechend Reifenseite und vermessener Reifenseite definieren

ALPHA = varsign.*ALPHA;
GAMMA = varsign.*GAMMA;

%% Parameter aus par_TIR holen

% [TIRE DATA]
FNOMIN = par_TIR.WHEEL.FNOMIN;
UNLOADED_RADIUS = par_TIR.DIMENSION.UNLOADED_RADIUS;
LONGVL = par_TIR.LONGVL;

% [SCALING PURE SLIP]
LFZO = par_TIR.SCALING.LFZO;    % [LATERAL], Scale factor of nominal (rated) load
LCX = par_TIR.SCALING.LCX;      % [LONGITUDINAL], Scale factor of Fx shape factor
LMUX = par_TIR.SCALING.LMUX;    % [LONGITUDINAL], Scale factor of Fx peak friction coefficient
LEX = par_TIR.SCALING.LEX;      % [LONGITUDINAL], Scale factor of Fx curvature factor
LKX = par_TIR.SCALING.LKX;      % [LONGITUDINAL], Scale factor of Fx slip stiffness
LHX = par_TIR.SCALING.LHX;      % [LONGITUDINAL], Scale factor of Fx horizontal shift
LVX = par_TIR.SCALING.LVX;      % [LONGITUDINAL], Scale factor of Fx vertical shift
LGAX = par_TIR.SCALING.LGAX;    % [LONGITUDINAL], Scale factor of camber for Fx
LCY = par_TIR.SCALING.LCY;      % [LATERAL], Scale factor of Fy shape factor
LMUY = par_TIR.SCALING.LMUY;    % [LATERAL], Scale factor of Fy peak friction coefficient
LEY = par_TIR.SCALING.LEY;      % [LATERAL], Scale factor of Fy curvature factor
LKY = par_TIR.SCALING.LKY;      % [LATERAL], Scale factor of Fy cornering stiffness
LHY = par_TIR.SCALING.LHY;      % [LATERAL], Scale factor of Fy horizontal shift
LVY = par_TIR.SCALING.LVY;      % [LATERAL], Scale factor of Fy vertical shift
LGAY = par_TIR.SCALING.LGAY;    % [LATERAL], Scale factor of camber for Fy
LTR = par_TIR.SCALING.LTR;      % [ALIGNING], Scale factor of Peak of pneumatic trail
LRES = par_TIR.SCALING.LRES;    % [ALIGNING], Scale factor for offset of residual torque
LGAZ = par_TIR.SCALING.LGAZ;    % [ALIGNING], Scale factor of camber for Mz
LMX = par_TIR.SCALING.LMX;      % [OVERTURNING], Scale factor of overturning couple
LVMX = par_TIR.SCALING.LVMX;    % [OVERTURNING], Scale factor of Mx vertical shift
LMY = par_TIR.SCALING.LMY;    % [ROLLING], Scale factor of rolling resistance torque, Nutzung fehlt in MF52 nach TNO

% [SCALING COMBINED SLIP]
LXAL = par_TIR.SCALING.LXAL;    % [LONGITUDINAL], Scale factor of alpha influence on Fx
LYKA = par_TIR.SCALING.LYKA;    % [LATERAL], Scale factor of kappa influence on Fy
LVYKA = par_TIR.SCALING.LVYKA;  % [LATERAL], Scale factor of kappa induced Fy
LS = par_TIR.SCALING.LS;        % [ALIGNING], Scale factor of Moment arm of Fx

% [SCALING TRANSIENT RESPONSE]
% LSGKP = par_SCALE.LSGKP;     % Scale factor of Relaxation length of Fx, nur falls transiente Schlupfberechnung
% LSGAL = par_SCALE.LSGAL;    % Scale factor of Relaxation length of Fy, nur falls transiente Schlupfberechnung
% LGYR = par_SCALE.LGYR;      % Scale factor of gyroscopic torque, nur falls transiente Schlupfberechnung

% [LONGITUDINAL COEFFICIENTS]
PCX1 = par_TIR.LONGITUDINAL.PCX1;
PDX1 = par_TIR.LONGITUDINAL.PDX1;
PDX2 = par_TIR.LONGITUDINAL.PDX2;
PDX3 = par_TIR.LONGITUDINAL.PDX3;
PEX1 = par_TIR.LONGITUDINAL.PEX1;
PEX2 = par_TIR.LONGITUDINAL.PEX2;
PEX3 = par_TIR.LONGITUDINAL.PEX3;
PEX4 = par_TIR.LONGITUDINAL.PEX4;
PKX1 = par_TIR.LONGITUDINAL.PKX1;
PKX2 = par_TIR.LONGITUDINAL.PKX2;
PKX3 = par_TIR.LONGITUDINAL.PKX3;
PHX1 = par_TIR.LONGITUDINAL.PHX1;
PHX2 = par_TIR.LONGITUDINAL.PHX2;
PVX1 = par_TIR.LONGITUDINAL.PVX1;
PVX2 = par_TIR.LONGITUDINAL.PVX2;
RBX1 = par_TIR.LONGITUDINAL.RBX1;
RBX2 = par_TIR.LONGITUDINAL.RBX2;
RCX1 = par_TIR.LONGITUDINAL.RCX1;
REX1 = par_TIR.LONGITUDINAL.REX1;
REX2 = par_TIR.LONGITUDINAL.REX2;
RHX1 = par_TIR.LONGITUDINAL.RHX1;

% [OVERTURNING COEFFICIENTS]
QSX1 = par_TIR.OVERTURNING.QSX1;
QSX2 = par_TIR.OVERTURNING.QSX2;
QSX3 = par_TIR.OVERTURNING.QSX3;

% [LATERAL COEFFICIENTS]
PCY1 = par_TIR.LATERAL.PCY1;
PDY1 = par_TIR.LATERAL.PDY1;
PDY2 = par_TIR.LATERAL.PDY2;
PDY3 = par_TIR.LATERAL.PDY3;
PEY1 = par_TIR.LATERAL.PEY1;
PEY2 = par_TIR.LATERAL.PEY2;
PEY3 = par_TIR.LATERAL.PEY3;
PEY4 = par_TIR.LATERAL.PEY4;
PKY1 = par_TIR.LATERAL.PKY1;
PKY2 = par_TIR.LATERAL.PKY2;
PKY3 = par_TIR.LATERAL.PKY3;
PHY1 = par_TIR.LATERAL.PHY1;
PHY2 = par_TIR.LATERAL.PHY2;
PHY3 = par_TIR.LATERAL.PHY3;
PVY1 = par_TIR.LATERAL.PVY1;
PVY2 = par_TIR.LATERAL.PVY2;
PVY3 = par_TIR.LATERAL.PVY3;
PVY4 = par_TIR.LATERAL.PVY4;
RBY1 = par_TIR.LATERAL.RBY1;
RBY2 = par_TIR.LATERAL.RBY2;
RBY3 = par_TIR.LATERAL.RBY3;
RCY1 = par_TIR.LATERAL.RCY1;
REY1 = par_TIR.LATERAL.REY1;
REY2 = par_TIR.LATERAL.REY2;
RHY1 = par_TIR.LATERAL.RHY1;
RHY2 = par_TIR.LATERAL.RHY2;
RVY1 = par_TIR.LATERAL.RVY1;
RVY2 = par_TIR.LATERAL.RVY2;
RVY3 = par_TIR.LATERAL.RVY3;
RVY4 = par_TIR.LATERAL.RVY4;
RVY5 = par_TIR.LATERAL.RVY5;
RVY6 = par_TIR.LATERAL.RVY6;

% [ROLLING COEFFICIENTS]
QSY1 = par_TIR.ROLLING.QSY1;
QSY2 = par_TIR.ROLLING.QSY2;
QSY3 = par_TIR.ROLLING.QSY3;
QSY4 = par_TIR.ROLLING.QSY4;

% [ALIGNING COEFFICIENTS]
QBZ1 = par_TIR.ALIGNING.QBZ1;
QBZ2 = par_TIR.ALIGNING.QBZ2;
QBZ3 = par_TIR.ALIGNING.QBZ3;
QBZ4 = par_TIR.ALIGNING.QBZ4;
QBZ5 = par_TIR.ALIGNING.QBZ5;
QBZ9 = par_TIR.ALIGNING.QBZ9;
QBZ10 = par_TIR.ALIGNING.QBZ10;
QCZ1 = par_TIR.ALIGNING.QCZ1;
QDZ1 = par_TIR.ALIGNING.QDZ1;
QDZ2 = par_TIR.ALIGNING.QDZ2;
QDZ3 = par_TIR.ALIGNING.QDZ3;
QDZ4 = par_TIR.ALIGNING.QDZ4;
QDZ6 = par_TIR.ALIGNING.QDZ6;
QDZ7 = par_TIR.ALIGNING.QDZ7;
QDZ8 = par_TIR.ALIGNING.QDZ8;
QDZ9 = par_TIR.ALIGNING.QDZ9;
QEZ1 = par_TIR.ALIGNING.QEZ1;
QEZ2 = par_TIR.ALIGNING.QEZ2;
QEZ3 = par_TIR.ALIGNING.QEZ3;
QEZ4 = par_TIR.ALIGNING.QEZ4;
QEZ5 = par_TIR.ALIGNING.QEZ5;
QHZ1 = par_TIR.ALIGNING.QHZ1;
QHZ2 = par_TIR.ALIGNING.QHZ2;
QHZ3 = par_TIR.ALIGNING.QHZ3;
QHZ4 = par_TIR.ALIGNING.QHZ4;
SSZ1 = par_TIR.ALIGNING.SSZ1;
SSZ2 = par_TIR.ALIGNING.SSZ2;
SSZ3 = par_TIR.ALIGNING.SSZ3;
SSZ4 = par_TIR.ALIGNING.SSZ4;

%% INITIALISIERUNG

% Referenzgeschwindigkeit auf diejenige aus dem Reifenfile festlegen
VREF = LONGVL;

% % Nutzung der korrekten Definitionen für den Fall großer Schräglaufwinkel/Sturzwinkel (entsprechend Pacejka 4.3.2)
% ALPHA = tan(ALPHA); % ohne *sign(VX), da dies keinen Sinn macht, wenn alpha nicht ebenfalls mit sign(VX) versehen wird für den Fall der Rückwärtsfahrt
% GAMMA = sin(GAMMA);

% calculate normalized vertical load increment dFZ
FNOMIN_ = FNOMIN.*LFZO;
dFZ = (FZ-FNOMIN_)./FNOMIN_;

%% LONGITUDINAL

% pure slip
GAMMAX = GAMMA.*LGAX;
SHX = (PHX1+PHX2.*dFZ).*LHX;
SVX = FZ.*(PVX1+PVX2.*dFZ).*LVX.*LMUX;
KAPPAX = KAPPA+SHX;
MUX = (PDX1+PDX2.*dFZ).*(1-PDX3.*GAMMAX.^2).*LMUX;
CX = PCX1.*LCX;
DX = MUX.*FZ;
EX = (PEX1+PEX2.*dFZ+PEX3.*dFZ.^2).*(1-PEX4.*sign(KAPPAX)).*LEX;
EX(EX>1) = 1;
KX = FZ.*(PKX1+PKX2.*dFZ).*exp(PKX3.*dFZ).*LKX;
BX = KX./(CX.*DX);
FX0 = DX.*sin(CX.*atan(BX.*KAPPAX-EX.*(BX.*KAPPAX-atan(BX.*KAPPAX))))+SVX;

% combined slip
SHXA = RHX1;
ALPHAS = ALPHA+SHXA;
BXA = RBX1.*cos(atan(RBX2.*KAPPA)).*LXAL;
CXA = RCX1;
EXA = REX1+REX2.*dFZ;
% if EXA>1
%     EXA = 1;
% end
GXA0 = cos(CXA.*atan(BXA.*SHXA-EXA.*(BXA.*SHXA-atan(BXA.*SHXA))));
GXA = cos(CXA.*atan(BXA.*ALPHAS-EXA.*(BXA.*ALPHAS-atan(BXA.*ALPHAS))))./GXA0;
FX = GXA.*FX0;

%% LATERAL

% pure slip
GAMMAY = GAMMA.*LGAY;
SHY = (PHY1+PHY2.*dFZ).*LHY+PHY3.*GAMMAY;
ALPHAY = ALPHA+SHY;
MUY = (PDY1+PDY2.*dFZ).*(1-PDY3.*GAMMAY.^2).*LMUY;
SVY = FZ.*((PVY1+PVY2.*dFZ).*LVY+(PVY3+PVY4.*dFZ).*GAMMAY).*LMUY;
DY = MUY.*FZ;
CY = PCY1.*LCY;
EY = (PEY1+PEY2.*dFZ).*(1-(PEY3+PEY4.*GAMMAY).*sign(ALPHAY)).*LEY;
EY(EY>1) = 1;
KY = PKY1.*FNOMIN.*sin(2.*atan(FZ./(PKY2.*FNOMIN.*LFZO))).*(1-PKY3.*abs(GAMMAY)).*LFZO.*LKY;
BY = KY./(CY.*DY);
FY0 = DY.*sin(CY.*atan(BY.*ALPHAY-EY.*(BY.*ALPHAY-atan(BY.*ALPHAY))))+SVY;

% combined slip
SHYK = RHY1+RHY2.*dFZ;
KAPPAS = KAPPA+SHYK;
BYK = RBY1.*cos(atan(RBY2.*(ALPHA-RBY3))).*LYKA;
CYK = RCY1;
EYK = REY1+REY2.*dFZ;
% if EYK>1
%     EYK = 1;
% end
DVYK = MUY.*FZ.*(RVY1+RVY2.*dFZ+RVY3.*GAMMA).*cos(atan(RVY4.*ALPHA));
SVYK = DVYK.*sin(RVY5.*atan(RVY6.*KAPPA)).*LVYKA;
GYK0 = cos(CYK.*atan(BYK.*SHYK-EYK.*(BYK.*SHYK-atan(BYK.*SHYK))));
GYK = cos(CYK.*atan(BYK.*KAPPAS-EYK.*(BYK.*KAPPAS-atan(BYK.*KAPPAS))))./GYK0;
FY = GYK.*FY0+SVYK;

%% ALIGNING TORQUE

% pure slip
GAMMAZ = GAMMA.*LGAZ;
SHT = QHZ1+QHZ2.*dFZ+(QHZ3+QHZ4.*dFZ).*GAMMAZ;
ALPHAT = ALPHA+SHT;
BT = (QBZ1+QBZ2.*dFZ+QBZ3.*dFZ.^2).*(1+QBZ4.*GAMMAZ+QBZ5.*abs(GAMMAZ)).*LKY./LMUY;
CT = QCZ1;
DT = FZ.*(QDZ1+QDZ2.*dFZ).*(1+QDZ3.*GAMMAZ+QDZ4.*GAMMAZ.^2).*(UNLOADED_RADIUS./FNOMIN).*LTR;
ET = (QEZ1+QEZ2.*dFZ+QEZ3.*dFZ.^2).*(1+(QEZ4+QEZ5.*GAMMAZ).*2./pi.*atan(BT.*CT.*ALPHAT));
ET(ET>1) = 1;
% T = DT.*cos(CT.*atan(BT.*ALPHAT-ET.*(BT.*ALPHAT-atan(BT.*ALPHAT)))).*cos(ALPHA); % pneumatic trail
SHR = SHY+SVY./KY;
ALPHAR = ALPHA+SHR;
DR = FZ.*((QDZ6+QDZ7.*dFZ).*LRES+(QDZ8+QDZ9.*dFZ).*GAMMAZ).*UNLOADED_RADIUS.*LMUY;
BR = QBZ9.*LKY./LMUY+QBZ10.*BY.*CY;
% MZR = DR.*cos(atan(BR.*ALPHAR)).*cos(ALPHA);
% MZ0 = -T.*FY0+MZR;
% KZ = -T.*KY; % approximation for the aligning moment stiffness

% combined slip
ALPHATEQ = atan(sqrt((tan(ALPHAT)).^2+(KX./KY).^2.*KAPPA.^2)).*sign(ALPHAT);
ALPHAREQ = atan(sqrt((tan(ALPHAR)).^2+(KX./KY).^2.*KAPPA.^2)).*sign(ALPHAR);
T = DT.*cos(CT.*atan(BT.*ALPHATEQ-ET.*(BT.*ALPHATEQ-atan(BT.*ALPHATEQ)))).*cos(ALPHA);
FY_ = FY-SVYK;
MZR = DR.*cos(atan(BR.*ALPHAREQ)).*cos(ALPHA);
S = (SSZ1+SSZ2.*(FY./FNOMIN)+(SSZ3+SSZ4.*dFZ).*GAMMA).*UNLOADED_RADIUS.*LS;
MZ = -T.*FY_+MZR+S.*FX;

%% OVERTURNING MOMENT

MX = UNLOADED_RADIUS.*FZ.*(QSX1.*LVMX+(-QSX2.*GAMMA+QSX3.*FY./FNOMIN).*LMX);

%% ROLLING RESISTANCE TORQUE

if QSY1==0 && QSY2==0
    MY = UNLOADED_RADIUS.*(SVX+KX.*SHX).*sign(VX);
else
    MY = -UNLOADED_RADIUS.*FZ.*(QSY1+QSY2.*FX./FNOMIN+QSY3.*abs(VX./VREF)+QSY4.*(VX./VREF).^4).*sign(VX).*LMY;
end

%% Spiegelung der Reifencharakteristik

FY = varsign.*FY;
MX = varsign.*MX;
MZ = varsign.*MZ;

end