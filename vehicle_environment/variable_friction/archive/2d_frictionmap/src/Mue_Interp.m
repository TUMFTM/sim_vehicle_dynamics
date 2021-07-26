function [mue_Wheel] = Mue_Interp(Mue_1, Mue_2, Mue_3, Mue_4, InterpTime, Time)
%Mue_Interp: Returns friction coefficient
%Definition Pos_Wheel_m
%--------------------------
Grid_map_time_1=InterpTime(1);
Grid_map_time_2=InterpTime(2);
Grid_map_time_3=InterpTime(3);
Grid_map_time_4=InterpTime(4);

%Define Grid_mode
if Grid_map_time_2~=0
    if Grid_map_time_3~=0
        if Grid_map_time_4~=0
            if (Grid_map_time_2<=Grid_map_time_1)||(Grid_map_time_3<=Grid_map_time_2)||(Grid_map_time_4<=Grid_map_time_3)
                error('Grid Map Times are not consistent')
            end
            Grid_mode=4;
        else
            if (Grid_map_time_2<=Grid_map_time_1)||(Grid_map_time_3<=Grid_map_time_2)
                error('Grid Map Times are not consistent')
            end
            Grid_mode=3;
        end
    else
        if Grid_map_time_4~=0 || (Grid_map_time_2<=Grid_map_time_1)
        error('Grid Map Times are not consistent')
        end
        Grid_mode=2;
    end    
else
    if Grid_map_time_3~=0 || Grid_map_time_4~=0
        error('Grid Map Times are not consistent')
    end
    Grid_mode=1;
end

% %Create vectors
mue_Wheel=zeros(1,4);

switch Grid_mode
    case 1
        mue=Mue_1;
        mue_Wheel=mue'/100;
    case 2
        if Grid_map_time_2>Grid_map_time_1
            if Grid_map_time_1>=Time
                mue=Mue_1;
                mue_Wheel=mue'/100;
            elseif Grid_map_time_1<Time && Grid_map_time_2>Time
                mue=Mue_1+(Mue_2-Mue_1)*((Time-Grid_map_time_1)/(Grid_map_time_2-Grid_map_time_1));
                mue_Wheel=mue'/100;
            elseif Grid_map_time_2<=Time
                mue=Mue_2;
                mue_Wheel=mue'/100;
            end    
        end    
    case 3
        if Grid_map_time_2>Grid_map_time_1 && Grid_map_time_3>Grid_map_time_2
            if Grid_map_time_1>=Time
                mue=Mue_1;
                mue_Wheel=mue'/100;
            elseif Grid_map_time_1<Time && Grid_map_time_2>=Time
                mue=Mue_1+(Mue_2-Mue_1)*((Time-Grid_map_time_1)/(Grid_map_time_2-Grid_map_time_1));
                mue_Wheel=mue'/100;
            elseif Grid_map_time_2<Time && Grid_map_time_3>Time
                mue=Mue_2+(Mue_3-Mue_2)*((Time-Grid_map_time_2)/(Grid_map_time_3-Grid_map_time_2));
                mue_Wheel=mue'/100;
            elseif Grid_map_time_3<=Time
                mue=Mue_3;
                mue_Wheel=mue'/100;          
            end    
        end    
    case 4
        if Grid_map_time_2>Grid_map_time_1 && Grid_map_time_3>Grid_map_time_2 && Grid_map_time_4>Grid_map_time_3
            if Grid_map_time_1>=Time
                mue=Mue_1;
                mue_Wheel=mue'/100;
            elseif Grid_map_time_1<Time && Grid_map_time_2>=Time
                mue=Mue_1+(Mue_2-Mue_1)*((Time-Grid_map_time_1)/(Grid_map_time_2-Grid_map_time_1));
                mue_Wheel=mue'/100;
            elseif Grid_map_time_2<Time && Grid_map_time_3>=Time
                mue=Mue_2+(Mue_3-Mue_2)*((Time-Grid_map_time_2)/(Grid_map_time_3-Grid_map_time_2));
                mue_Wheel=mue'/100;   
            elseif Grid_map_time_3<Time && Grid_map_time_4>Time
                mue=Mue_3+(Mue_4-Mue_3)*((Time-Grid_map_time_3)/(Grid_map_time_4-Grid_map_time_3));
                mue_Wheel=mue'/100;
            elseif Grid_map_time_4<=Time
                mue=Mue_4;
                mue_Wheel=mue'/100;
            end    
        end      
end        
 end