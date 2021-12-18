#!/usr/bin/env ruby

require 'timeout'

def run(no, count)
  Dir.glob("./build/*#{no}").each do |f|
    count.times do |i|
      in_file = "./generator/#{no}-#{i + 1}.in"
      out_file = "#{f.sub('build', 'out')}-#{i + 1}.out"
      pid = Process.spawn "#{f} < #{in_file} > #{out_file}"
      Timeout.timeout(1) do
        Process.wait pid
      end
    rescue Timeout::Error
      puts "Timeout for #{f} when tests #{i + 1} case"
      File.delete out_file
      Process.kill 'KILL', pid
    end
  end
end

run 'A', 3
run 'B', 3
run 'C', 4
