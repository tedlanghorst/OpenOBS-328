clear
clc

calPath = "/Users/Ted/GDrive/OpenOBS_v2/Calibrations/";
[files,path] = uigetfile('/*.TXT','multiselect','on');

if isa(files,'char')
    filepath = fullfile(path,files);
    %look for the sensor serial number in header.
    fid = fopen(filepath);
    for j = 1:5 %scan first 5 lines
        tline = fgetl(fid);
        if contains(tline,"OpenOBS SN:")
            sn = str2double(tline(12:end));
            break
        end 
    end
    fclose(fid);
    d = readtable(filepath);

else
    d = table();
    for i = 1:numel(files)
        filepath = fullfile(path,files{i});
        %look for the sensor serial number in header.
        fid = fopen(filepath);
        for j = 1:5 %scan first 5 lines
            tline = fgetl(fid);
            if contains(tline,"OpenOBS SN:")
                sn(i) = str2double(tline(12:end));
                break
            end 
        end
        fclose(fid);
    
        d = vertcat(d,readtable(filepath));
    end
end

if numel(unique(sn)) ~= 1
    error("Multiple serial numbers found in files");
else
    sn = sn(1);
    if sn==65535
        warning("Serial number not set.")
    end
end

d.battery_V = d.battery ./ 2^10 .* 3.3 .* 2;

%%



%convert timestamp
d.dt = datetime(d.time, 'ConvertFrom', 'posixtime','Format','dd-MM-yyyy HH:mm:ss.SSSS');


%find and apply the most recent calibration file
calDir = dir(sprintf("%s%03u/*.mat",calPath,sn));
if isempty(calDir)
    d.NTU = NaN(height(d),1);
else
    [~,mostRecent] = max([calDir.datenum]);
    calFile = fullfile(calDir(mostRecent).folder,calDir(mostRecent).name);
    load(calFile,"lm");
    d.NTU = predict(lm,d.R0_V);
    d.NTU_sd = predict(lm,d.R0_V_sd);
end


% plots
close all

figure
set(gcf,'Units','normalized')
set(gcf,'Position',[0.1 0.1 0.8 0.8])
hold on

plot(d.dt,d.ambient_light)
yyaxis right
plot(d.dt,d.battery_V)

% figure
% set(gcf,'Units','normalized')
% set(gcf,'Position',[0.3 0.3 0.5 0.4])
% plot(rs.dt,rs.NTU,'.')
% title("Lab Calibrated NTUs")
% ylabel('NTU')


