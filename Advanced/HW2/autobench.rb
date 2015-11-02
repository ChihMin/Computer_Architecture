#!/usr/bin/env ruby

# baseline computer as 64kb d_cache and 32kb i_cache 

class BenchMark
  def initialize(filename = "table.md")
    @f = File.open(filename, "w")
    @benchmarks = ["gcc", "perlbench", "bzip2", "bwaves", "calculix"]
  end

  def powOf2(x)
    # puts "START = #{x}"
    if x == 1
      return false
    end
    while x > 1
      if (x % 2) == 1
        return false
      end
      x = x / 2;
    end
    return true
  end

  def check(x, y)
   return powOf2(x) && powOf2(y)
  end

  def execute(d_cache, i_cache, l2_cache)
    total_cache = d_cache + i_cache
    ret_arr = Array.new
    
    bench = "gcc"
    `./run.sh #{bench} /home/chihmin/gem5/out #{d_cache} #{i_cache} #{total_cache} #{l2_cache} | grep "tick "`
    
    stat_file = "./out/#{l2_cache}MB/stats_#{l2_cache}MB.txt" 
    miss_rate = `cat #{stat_file} | grep -i l2.overall_miss_rate::total`.split(' ')[1]
    miss_latency = `cat #{stat_file} | grep -i l2.overall_avg_miss_latency::total`.split(' ')[1]
    sim_seconds = `cat #{stat_file} | grep -i sim_seconds`.split(' ')[1]

    new_element = "#{miss_rate} #{miss_latency} #{sim_seconds}"
    ret_arr.push(new_element)
    puts "Miss rate = #{miss_rate}, Miss latency = #{miss_latency}, sim_seconds = #{sim_seconds}"
    
    @f.write(new_element << "\n")
    ret_arr
  end
  
  def parse(l2_cache, set)
    stat_file = "out_assoc/#{l2_cache}MB/#{set}_SET/stats_#{l2_cache}MB_#{set}_SET.txt"
    l2_miss_rate = `cat #{stat_file} \
                    | grep -i l2.overall_miss_rate::total`.split(' ')[1].to_f

    d_access = `cat #{stat_file} \
                | grep -i dcache.overall_accesses::total`.split(' ')[1].to_f
    
    i_access = `cat #{stat_file} \
                | grep -i icache.overall_accesses::total`.split(' ')[1].to_f
    
    d_latency = `cat #{stat_file} \
                | grep -i dcache.overall_avg_miss_latency::total`.split(' ')[1]
    
    i_latency = `cat #{stat_file} \
                | grep -i icache.overall_avg_miss_latency::total`.split(' ')[1]
    
    d_miss_rate = `cat #{stat_file} \
                | grep -i dcache.overall_miss_rate::total`.split(' ')[1].to_f
    
    i_miss_rate = `cat #{stat_file} \
                | grep -i icache.overall_miss_rate::total`.split(' ')[1].to_f

    l1_miss_rate = (d_access * d_miss_rate + \
                          i_access * i_miss_rate) / \
                                  (d_access + i_access)
    
    amp = Array.new
    amp[1] = 10 + 150.0 * l2_miss_rate
    amp[0] = 1 + amp[1] * l1_miss_rate

    table = "|#{set} | #{d_access} | #{d_miss_rate} | #{i_access} | #{i_miss_rate}| #{l1_miss_rate.round(8)} | #{l2_miss_rate} | #{amp[0]} |"
    puts table
   - 
    @f.write(table << "\n")
  end
   
  def run
    for i in 0..10
      execute(64, 32, 2**i)
    end
    @f.close
  end

  def run_parse
    
    for size in [1, 2, 4, 8]
      @f.write("**L2 Cache #{size}MB**\n\n") 
      @f.write("|set         |d_access|d miss rate|i_access|i miss rate|L1 miss rate|L2 miss rate|AMAT|\n")
      @f.write("|:----------:|:------:|:---------:|:------:|:---------:|:----------:|:----------:|:----:|\n")
      for i in 0..7
        parse(size, 2**i)
      end
    end
    @f.close
    `open table.md`
  end
  
end

target = BenchMark.new
target.run_parse
