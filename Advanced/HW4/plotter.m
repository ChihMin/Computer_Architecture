f = fopen('run_report.txt');
times(1:2, 1:9, 1:3) = 0;
for i = 1:2,
    for j = 1:9,
        for k = 1:3,
            str = fgets(f);
            cells = strsplit(str, ' ');
            ticks = cell2struct(cells(5), 'ticks');
            ticks = str2double(ticks.ticks);
            times(i, j, k) = ticks;
        end
    end
end

gcc(1:9, 1:3) = times(2, 1:9, 1:3);
bar(gcc);
xlabel('Round', 'FontSize', 16); 
ylabel('Run time (ticks)', 'FontSize', 16);
legend('timing CPU', 'atomic CPU', 'out-of-order CPU');

