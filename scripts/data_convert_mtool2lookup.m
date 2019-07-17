function [] = data_convert_mtool2lookup(machinemap)
% Author: Thomas Herrmann    Date: 19.04.2019
% 
% Requirement: Efficiency Map-Data must be loaded into workspace
% 
% Description:  Puts efficiency map of machine tool into correct format for
% a lookup table for the use within Simulink
% 
% Input:        machinemap: eff. map as a sctruct
% 
% Output:       efficiency map saved in data-dictionary
% db_ElectricMotor.sldd
%% Algorithm

dictPath = 'parameters/powertrain/db_ElectricMotor.sldd';
machinemap = load(machinemap);
machinemap = machinemap.KennfeldMaschine;

nn = machinemap.n(1,:);
MM = machinemap.M(:,1)';
% flip torque
MM = MM(end:-1:1);
% flip efficiency map
etaeta = machinemap.etages(end:-1:1,:);

%% Write to DD
DictionaryObj = Simulink.data.dictionary.open(dictPath);
dDataSectObj = getSection(DictionaryObj,'Design Data');
rlObj = getEntry(dDataSectObj,'db_etaMotor_tb');
setValue(rlObj,etaeta);
rlObj = getEntry(dDataSectObj,'db_MMotorTrq_tb_Nm');
setValue(rlObj,MM);
rlObj = getEntry(dDataSectObj,'db_nMotorRev_tb_pmin');
setValue(rlObj,nn);
% Save changes currently made
saveChanges(DictionaryObj);

end