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

%% Q1(b)

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

%% Q2(b)

clear;
filename = 'unroll_o2.txt';
[cacheB, assocB, blockB, missB] = readfile(filename);

plot(missB)
set(gca,...
    'XTickLabel', [1 2 4 8 16 32],...
    'XTick', 1:6);
xlabel('Cache Size & Block Size(sec)', 'FontSize', 16); 
ylabel('Ticks', 'FontSize', 16);
