clear
clc

[file,path] = uigetfile('/*.TXT','Multiselect','on');
filepath = fullfile(path,file);

% gen_path = "/Users/Ted/GDrive/OpenOBS/Calibrations_v2/";
gen_path = "/Users/Ted/GDrive/Sag2022/Data/OOBS/calibrations/";
standards = [0,100,250,500,1000];

%look for the sensor serial number in each file.

fid = fopen(filepath);
for j = 1:5 %scan first 5 lines
    tline = fgetl(fid);
    if contains(tline,"OpenOBS SN:")
        sn = str2double(tline(12:end));
        break
    end
end
fclose(fid);

burstID = [];
%     timeInterp = [];

data = readtable(filepath);

data.dt = datetime(data.time, 'ConvertFrom', 'posixtime','Format','dd-MM-yyyy HH:mm:ss.SSSS');
isWrongDay = data.dt < datetime(file(1:8),'InputFormat','yyyyMMdd');
data(isWrongDay,:) = [];
isWrongDay = data.dt > datetime(file(1:8),'InputFormat','yyyyMMdd') + 1;
data(isWrongDay,:) = [];


% clearvars -except sn data file
close all

figure
colormap flag
set(gcf,'Units','normalized')
set(gcf,'Position',[0.1 0.1 0.8 0.6])
hold on
plot(data.dt,data.scattered_light,'b.','markersize',10);
plot(data.dt,data.ambient_light,'r.','markersize',10);
title(sprintf("Serial no. %03d", sn))
zoom on


figure
plot(data.dt,data.hydrostatic_pressure,'b.','markersize',10);


%% save calibration data
%{
    Before running this section, make sure you use the brush tool to select
    each set of data and right click -> export using the variable names
    used below... 
%}
close all

measured = [mean(a(:,2)), std(a(:,2)); 
        mean(b(:,2)), std(b(:,2)); 
        mean(c(:,2)), std(c(:,2));
        mean(d(:,2)), std(d(:,2)); 
        mean(e(:,2)), std(e(:,2))];

lm = fitlm(measured(:,1),standards);
NTU = predict(lm,measured(:,1));
        
eb = errorbar(standards,measured(:,1),measured(:,2));
eb.LineWidth = 1;
xlabel("Standard (NTU)");
ylabel("Measured (Volts)");


save_path = sprintf(strcat(gen_path,"%03d"),sn);
if ~exist(save_path, 'dir')
    mkdir(save_path)
end
save(fullfile(save_path,file(1:8)),"measured","standards","NTU","lm","data")

%% look at a bunch of cal data
date_string = "20221002";
sn_ignore = [];

cal_path = dir(fullfile(gen_path,"*",date_string+".mat"));
lgd_names = {};

close all
figure
for i = 1:numel(cal_path)
    load(fullfile(cal_path(i).folder,cal_path(i).name))
    cal_data(i).sn = str2double(cal_path(i).folder(end-2:end));
    cal_data(i).standards = standards;
    cal_data(i).measured = measured(:,1);
    cal_data(i).measured_sd = measured(:,2);
    cal_data(i).NTU = NTU;
    cal_data(i).lm = lm;
    
    if any(cal_data(i).sn == sn_ignore)
        continue
    end
    
    
    subplot(1,2,1)
    hold on
    plot(standards,measured(:,1),'o-','Linewidth',1.5)
    
    subplot(1,2,2)
    hold on
    plot(standards+1,NTU'-standards,'o-','Linewidth',1.5)
    
    lgd_names{numel(lgd_names)+1} = cal_path(i).folder(end-2:end);
end

subplot(1,2,1)
xlabel("Standard (NTU)");
ylabel("Measured (Volts)");
title('Raw Signal')
axis square
box on
% lgd = legend(lgd_names,'Location','NorthWest');
% title(lgd,"S/N")

subplot(1,2,2)
xlabel("Standard (NTU)");
ylabel("Calibration - Standard (NTU)");
title('Calibration Error')
axis square
box on
% set(gca,'XScale','log')
xlim = get(gca,'XLim');
plot(xlim,[0,0],'k--','Linewidth',1)

% set(gca,'YScale','log')



set(gcf,'Units','normalized')
set(gcf,'Position',[0.3 0.4 0.4 0.3]);

saveas(gcf,fullfile(gen_path,"calibration_"+date_string+".png"))


% lims = get(gca,'XLim') + [-50,50];
% set(gca,'XLim',lims,'YLim',lims)
