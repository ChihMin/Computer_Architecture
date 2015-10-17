#!/usr/bin/env ruby

# baseline computer as 64kb d_cache and 32kb i_cache 

class BenchMark
  def initialize(filename = "run_report.txt")
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
    # puts "check #{x} #{y}" 
   return powOf2(x) && powOf2(y)
  end

  def execute(d_cache, i_cache)
    total_cache = d_cache + i_cache
    ret_arr = Array.new
    @benchmarks.each do |bench|
      ret = `./run.sh #{bench} /home/chihmin/gem5/out #{d_cache} #{i_cache} #{total_cache} | grep "tick "`
      ticks = ret.split(" ")[3]
      new_element = "#{total_cache} #{d_cache} #{i_cache} #{bench} #{ticks}"
      ret_arr.push(new_element)
      @f.write(new_element << "\n")
    end
    ret_arr
  end
  
  def run
    for x in 96..1024
      count  = 0
      for i in 1..(x/2)
        if check(i, x-i)
          count = count + 1
          puts "answer #{i} #{x-i}"
          execute(i, x-i)
          execute(x-i, i)
        end
      end
    end
    @f.close
  end
end

target = BenchMark.new
target.run
