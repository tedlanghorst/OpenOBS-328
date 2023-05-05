clear
clc

calPath = "/Users/Ted/GDrive/OpenOBS-328/Calibrations/";
[files,path] = uigetfile('/*.TXT','multiselect','on');

if isa(files,'char')
    filepath = fullfile(path,files);
    outpath = fullfile(path,[files(1:end-4) '.csv']);
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
    outpath = fullfile(path,[files{1}(1:end-4) '.csv']);
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


if any(strcmp('battery',d.Properties.VariableNames))
    d.battery_V = d.battery ./ 2^10 .* 3.3 .* 2;
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
    d.pressure_mbar = d.pressure./10;
end

% total time in measurement
fprintf("Total record time: %0.1f days\n",days(max(d.datetime)-min(d.datetime)))

%% plots
close all
figure
hold on
yyaxis left
plot(d.datetime,d.backscatter)
plot(d.datetime,d.ambient_light)
ylabel("light sensor")
yyaxis right
plot(d.datetime,d.pressure_mbar)
ylabel("pressure (mbar)")
title(filepath)


% writetable(d,outpath);
% exportgraphics(gcf,[outpath(1:end-4),'.png'],'Resolution',600)



