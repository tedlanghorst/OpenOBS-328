clear
clc

calPath = "/Users/Ted/GDrive/OpenOBS-328/Calibrations/";
[files,path] = uigetfile('/*.TXT','multiselect','on');

if isa(files,'char')
    filepath = fullfile(path,files);
    outpath = fullfile(path,files(1:end-4));
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
    filename = sn + "-" + files{1}(1:end-4) + "-" + files{end}(1:end-4);
    outpath = fullfile(path,filename);
end

if numel(unique(sn)) ~= 1
    error("Multiple serial numbers found in files");
else
    sn = sn(1);
    if sn==65535
        warning("Serial number not set.")
    end
end


if any(strcmp('battery',d.Properties.VariableNames))
    d.battery_V = d.battery ./ 2^10 .* 3.3 .*11;
end

%convert timestamp
d.datetime = datetime(d.time, 'ConvertFrom', 'posixtime','Format','dd-MM-yyyy HH:mm:ss.SSSS');
d = sortrows(d,'datetime');

%find and apply the most recent calibration file
calDir = dir(sprintf("%s%03u/*.mat",calPath,sn));
if isempty(calDir)
    d.NTU = NaN(height(d),1);
else
    [~,mostRecent] = max([calDir.datenum]);
    calFile = fullfile(calDir(mostRecent).folder,calDir(mostRecent).name);
    load(calFile,"lm");
    d.NTU = predict(lm,d.backscatter);
end

if any("pressure" == string(d.Properties.VariableNames))
    d.pressure_mbar = d.pressure./100;
    d.depth = NaN(length(d.pressure),1);%1E5 * (d.pressure_mbar./1000-1)/(1000*9.80665);
    d.water_temp_C = d.water_temp./100;
end


% total time in measurement
fprintf("Total record time: %0.1f days\n",days(max(d.datetime)-min(d.datetime)))

%% plots
close all

tiledlayout(4,1);
ax(1) = nexttile;
plot(d.datetime,d.NTU)
% set(gca,'YLim',[0,1000])
ylabel("NTU")
title(["OpenOBS SN: " + sn])


ax(2) = nexttile;
plot(d.datetime,d.pressure_mbar)
% set(gca,'YLim',[0,1])
ylabel("pressure (mbar)")

ax(3) = nexttile;
plot(d.datetime,d.water_temp_C)
ylabel("temp (C)")

ax(4) = nexttile;
plot(d.datetime,d.battery_V)
ylabel("battery (V)")
set(gca,'YLim',[3.3,4.2])

linkaxes(ax,'x')
set(gcf,'Units','normalized')
set(gcf,'Position',[0.3 0.05 0.35 0.8])

writetable(d,outpath+".csv");
exportgraphics(gcf,outpath+".png",'Resolution',600)



