%% Q1
clear;
filename = 'row_100.txt';
[cacheA, assocA, blockA, missA] = readfile(filename);

filename = 'col_100.txt';
[cacheB, assocB, blockB, missB] = readfile(filename);

plot([missA; missB]')
set(gca,...
    'XTickLabel', cacheA,...
    'XTick', 1:32);
legend('row major', 'column major');
xlabel('Cache Size & Block Size(sec)', 'FontSize', 16); 
ylabel('cache miss', 'FontSize', 16);

%% Q2

clear;
filename = 'row_100_assoc.txt';
[cacheA, assocA, blockA, missA] = readfile(filename);

filename = 'col_100_assoc.txt';
[cacheB, assocB, blockB, missB] = readfile(filename);

plot([missA; missB]')
set(gca,...
    'XTickLabel', assocA,...
    'XTick', 1:32);
legend('row major', 'column major');
xlabel('Cache Size & Block Size(sec)', 'FontSize', 16); 
ylabel('cache miss', 'FontSize', 16);