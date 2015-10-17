%% 
clear;
f = fopen('run_report.txt', 'r');
testcase = 220;
total_cache = [];
d_cache = [];
i_cache = [];
benchmark = {};
ticks = [];
for i = 1:testcase,
    str = fgets(f);
    element = strsplit(str, ' ');
    C = cellstr(element);
    total_cache = [total_cache str2double(strjoin(C(1)))];
    d_cache = [d_cache str2double(strjoin(C(2)))];
    i_cache = [i_cache str2double(strjoin(C(3)))];
    benchmark{i} = C(4);
    ticks = [ticks str2double(strjoin(C(5)))];
end
fclose(f);

%%
% 
com_sum_A = [];
com_sum_B = [];
com_prod_A = [];
com_prod_B = [];
com_d_A = d_cache(1:10:testcase);
com_d_B = d_cache(6:10:testcase);
com_i_A = i_cache(1:10:testcase);
com_i_B = i_cache(6:10:testcase);
com_total = total_cache(1:10:testcase);
x = (1:testcase/10);

for i = 1:10:testcase,
    com_sum_A = [com_sum_A sum(ticks(i:i+4))];
    com_sum_B = [com_sum_B sum(ticks(i+5:i+9))];  
    
    com_prod_A = [com_prod_A prod(ticks(i:i+4)) .^ (1/5)];
    com_prod_B = [com_prod_B prod(ticks(i+5:i+9)) .^ (1/5)];
end
 

% subplot(2,2,1);
plot(x, com_sum_A, 'b-o', x, com_sum_B, 'r-o');
legend('machine A', 'machine B');
title('Arithmetic mean', 'FontSize', 16);
xlabel('Round', 'FontSize', 16); ylabel('Ticks(seconds x freq)', 'FontSize', 16);

% subplot(2,2,2);
figure;
plot(x, com_prod_A, 'b-o', x, com_prod_B, 'r-o');
legend('machine A', 'machine B');
title('Geometry mean', 'FontSize', 16);
xlabel('Round', 'FontSize', 16); ylabel('Ticks(seconds x freq)', 'FontSize', 16);


% subplot(2,2,3);
figure;
plot(x, com_d_A, 'b--o', x, com_d_B, 'r--o', x, com_total, 'm--o');
title('D Cache Size', 'FontSize', 16);
hleg1 = legend('machine A', 'machine B', 'Total cache size');
set(hleg1,'Location','NorthWest');
xlabel('Round', 'FontSize', 16); ylabel('Size(kB)', 'FontSize', 16);


% subplot(2,2,4);
figure;
plot(x, com_i_A, 'b--o', x, com_i_B, 'r--o', x, com_total, 'm--o');
title('I Cache Size', 'FontSize', 16);
hleg1 = legend('machine A', 'machine B', 'Total cache size');
set(hleg1,'Location','NorthWest');
xlabel('Round', 'FontSize', 16); ylabel('Size(kB)', 'FontSize', 16);

%%
figure;
for i = 0:4,
    com_A_bench = ticks(1+i:10:testcase);
    com_B_bench = ticks(6+i:10:testcase);
    subplot(2,3,i+1);
    % figure;
    plot(x, com_A_bench, 'b--o', x, com_B_bench, 'r--o');
    title(benchmark{i+1}, 'FontSize', 16);
    legend('machine A', 'machine B');
    xlabel('Round', 'FontSize', 16); ylabel('Ticks(seconds x freq)', 'FontSize', 16);
end

%% Create testcase MARKDOWN table for machine A

fptr = fopen('cache_table_A.txt', 'w');
for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_total(i));
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '|:---:');
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_d_A(i));
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_i_A(i));
end
fprintf(fptr, '| \n');
fclose(fptr);

%% Create testcase MARKDOWN table for machine B

fptr = fopen('cache_table_B.txt', 'w');
for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_total(i));
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '|:---:');
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_d_B(i));
end
fprintf(fptr, '| \n');

for i = 1:testcase/10,
    fprintf(fptr, '| %d ', com_i_B(i));
end
fprintf(fptr, '| \n');
fclose(fptr);


       