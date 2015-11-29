function [ cache, assoc, block, ticks ] = readfile( filename )
    f = fopen(filename, 'r');
    cache = [];
    assoc = [];
    block = [];
    ticks = [];
    for i = 1:6,
        str = fgets(f);
        str
        element = strsplit(str, ' ');
        C = cellstr(element);
        
        cache = [cache str2double(C(2))];
        assoc = [assoc str2double(C(3))];
        block = [block str2double(C(4))];
        ticks = [ticks str2double(C(5))];
    end
    fclose(f);
end

