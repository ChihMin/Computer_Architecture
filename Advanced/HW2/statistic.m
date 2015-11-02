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
%%
x = [1:9];

plot(x, miss_rate, 'b-o');
axis([1,11,0.378,0.3806])
title('L2 Cache Miss Rate', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('miss rate', 'FontSize', 16);
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );

%%
figure;
plot(x, miss_latency, 'r-o');
% axis([1,9,-1,1])
title('L2 Cache Miss Latency', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('miss latency(cycle)', 'FontSize', 16);
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );
%%

figure;
plot(x, sim_seconds, 'm-o');
title('Sim seconds', 'FontSize', 16);
xlabel('cache size(MB)', 'FontSize', 16); 
ylabel('sim seconds(seconds)', 'FontSize', 16);
axis([1,9,0.0154170,0.015430])
set(gca,...
    'XTickLabel',2 .^ (x - 1),...
    'XTick', x );
