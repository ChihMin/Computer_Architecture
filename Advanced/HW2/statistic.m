%%

clear;

f = fopen('run_report.txt');
miss_rate = [];
miss_latency = [];
sim_seconds = [];

for i = 1:9
    str = fgets(f);
    element = strsplit(str, ' ');
    miss_rate(i) = str2double(element(1));
    miss_latency(i) = str2double(element(2));
    sim_seconds(i) = str2double(element(3));
end

x = [1:9];

plot(x, miss_rate, 'b-o');
axis([1,11,0.378,0.3806])
title('L2 Cache Miss Rate', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('miss rate', 'FontSize', 16);
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );


figure;
plot(x, miss_latency, 'r-o');
% axis([1,9,-1,1])
title('L2 Cache Miss Latency', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('miss latency(cycle)', 'FontSize', 16);
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );

figure;
plot(x, sim_seconds, 'm-o');
title('Sim seconds', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('sim seconds(seconds)', 'FontSize', 16);
axis([1,9,0.0154170,0.015430])
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );

%%

clear;

for i = 1:5,
    cache_size_name = sprintf('%dMB_report.txt', 2 .^ (i-1))
    filename = strcat('run_assoc_report/', cache_size_name) 
    f = fopen(filename);
    
    cache_size(i) = 2 .^ (i-1)

    for j = 1:4,
        str = fgets(f);
        element = strsplit(str, ' ');
        set(i, j) = round(str2double(element(2)));
        miss_rate(i, j) = str2double(element(3));
        miss_latency(i, j) = str2double(element(4));
        sim_seconds(i, j) = str2double(element(5));
    end
    fclose(f);
end

x = [1 2 4 8];

plot(x, sim_seconds(1,1:4), 'b-o',... 
     x, sim_seconds(2,1:4), 'r-o',... 
     x, sim_seconds(3,1:4), 'm-o',...
     x, sim_seconds(4,1:4), 'k-o');
% axis([1,11,0.378,0.3806])
title('L2 Cache Sim seconds with different set', 'FontSize', 16);
legend('1MB', '2MB', '4MB', '8MB');
xlabel('Associativity(Set)', 'FontSize', 16); 
ylabel('sim seconds', 'FontSize', 16);
%{
set(gca,...
     'XTickLabel',[1 2 4 8],...
     'XTick', [1 2 3 4]);
%}
