clear
clc
close all

%the calibration standards. If you cange the number of samples here, make
%sure to change to a-e variables in the next code chunk.
standards = [0 100 250 500 1000]';

[file,path] = uigetfile('/*.TXT','Multiselect','off');
filepath = fullfile(path,file);

%where we will store calibrations
gen_path = "/Users/Ted/GDrive/OpenOBS-328/calibrations/";

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

data = readtable(filepath);
data.dt = datetime(data.time, 'ConvertFrom', 'posixtime','Format','dd-MM-yyyy HH:mm:ss.SSSS');

%try the autocalibration routine
hasPressure = any(strncmp('pressure',data.Properties.VariableNames,8));
autoCal = 0;
if hasPressure
    %remove noise from pressure and find likely submerged periods
    data.pressure(data.pressure>2E5) = NaN; %remove any unreasonably high values
    pressureTrend = movmedian(data.pressure,length(data.pressure)/10,'omitnan');
    pressureDetrend = data.pressure-pressureTrend;
    pressureDetrend(pressureDetrend<0) = 0;
    pressureThreshold = double(pressureDetrend > 100);
    TF = find(ischange(pressureThreshold));
    
    %remove any brief changes in pressure, likely noise.
    shortChanges = find(diff(TF)<10);
    if any(shortChanges)
        TF(shortChanges:shortChanges+1) = [];
    end

    %if we get the right number of periods, we'll try autocal.
    if numel(TF)==(numel(standards)*2)
        autoCal = 1;
        autoCalText = ['Automatic calibration samples found using pressure data.\n' ...
        'Use the brush tool to fix and export any or all standards ''a'' through ''e''.'];
    else
         autoCalText = ['Automatic calibration failed.\n' ...
        'Use the brush tool to highlight and export standards ''a'' through ''e''.'];
    end
else
    autoCalText = ['Automatic calibration requires pressure data.\n' ...
        'Use the brush tool to highlight and export each calibration sample\n' ...
        'and name them ''a'' through ''e''.'];
end

figure
colormap flag
set(gcf,'Units','normalized')
set(gcf,'Position',[0.1 0.1 0.8 0.6])
hold on
if autoCal
    for i=1:(numel(TF)/2)
        idx = TF(i*2-1)+1:TF(i*2)-1;
        measured(i,:) = [mean(data.backscatter(idx)), std(data.backscatter(idx))];
        plot(data.dt(idx),data.backscatter(idx),'ro', 'HandleVisibility', 'off')
        text(mean(data.dt(idx)),measured(i,1)+1000, char(96+i), ...
            'FontSize',24, ...
            'HorizontalAlignment','center', ...
            'VerticalAlignment','baseline')
    end
end
plot(data.dt,data.backscatter,'b.','markersize',10);
text(0.05,0.9,sprintf(autoCalText),'Units','normalized','FontSize',14)
ylabel("Backscatter");


% plot(data.dt,TF,'markersize',10);
title(sprintf("Serial no. %03d", sn))
zoom on





%% save calibration data
%{
    Before running this section, make sure the autocalibration selected the
    right data, or use the brush tool to select and export the right data
    to match the standards. 
%}
close all

if exist('a','var') 
    measured(1,:) = [mean(a{:,2}), std(a{:,2})]; 
end
if exist('b','var') 
    measured(2,:) = [mean(b{:,2}), std(b{:,2})]; 
end
if exist('c','var') 
    measured(3,:) = [mean(c{:,2}), std(c{:,2})]; 
end
if exist('d','var') 
    measured(4,:) = [mean(d{:,2}), std(d{:,2})]; 
end
if exist('e','var') 
    measured(5,:) = [mean(e{:,2}), std(e{:,2})]; 
end


lm = fitlm(measured(:,1),standards);
NTU = predict(lm,measured(:,1));
        
eb = errorbar(standards,measured(:,1),measured(:,2).*3);
eb.LineWidth = 1;
xlabel("Standard (NTU)");
ylabel("Measured (DN)");


save_path = sprintf(strcat(gen_path,"%03d"),sn);
if ~exist(save_path, 'dir')
    mkdir(save_path)
end
save(fullfile(save_path,file(1:8)),"measured","standards","NTU","lm","data")

%% look at a bunch of cal data
date_string = "20230602";
sn_ignore = [];

cal_path = dir(fullfile(gen_path,"*",date_string+".mat"));
lgd_names = {};

close all
figure
for i = 1:numel(cal_path)
    load(fullfile(cal_path(i).folder,cal_path(i).name))
    NTU_sd = measured(:,2) .* lm.Coefficients.Estimate(2);

    cal_data(i).sn = str2double(cal_path(i).folder(end-2:end));
    cal_data(i).standards = standards;
    cal_data(i).measured = measured(:,1);
    cal_data(i).measured_sd = measured(:,2);
    cal_data(i).NTU = NTU;
    cal_data(i).NTU_sd = NTU_sd;
    cal_data(i).lm = lm;
    
    if any(cal_data(i).sn == sn_ignore)
        continue
    end
    
    
    subplot(1,2,1)
    hold on
    plot(standards,measured(:,1),'o-','Linewidth',1)
    
    subplot(1,2,2)
    hold on
    eb = errorbar(standards,NTU-standards,NTU_sd);
    eb.LineWidth = 1;
%     plot(standards+1,NTU-standards,'o-','Linewidth',1.5)
    
    lgd_names{numel(lgd_names)+1} = cal_path(i).folder(end-2:end);
end

subplot(1,2,1)
xlabel("Standard (NTU)");
ylabel("Measured (DN)");
title('Readings')
set(gca,'XTick',[0,100,250,500,1000])
axis square
box on

subplot(1,2,2)
xlabel("Standard (NTU)");
ylabel("Calibration - Standard (NTU)");
title('Calibration Error')
set(gca,'XTick',[0,100,250,500,1000])
axis square
box on
xlim = get(gca,'XLim');
plot(xlim,[0,0],'k--','Linewidth',1)

% lgd = legend(lgd_names,'Location','East Outside');
% title(lgd,"S/N")



set(gcf,'Units','normalized')
set(gcf,'Position',[0.3 0.4 0.4 0.3]);

exportgraphics(gcf,fullfile(gen_path,"calibration_"+date_string+".png"),'resolution',600)


% lims = get(gca,'XLim') + [-50,50];
% set(gca,'XLim',lims,'YLim',lims)
