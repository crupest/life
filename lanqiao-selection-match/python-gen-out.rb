#!/usr/bin/env ruby

require 'timeout'

def run(no, count)
  Dir.glob("./codes/*#{no}.py").each do |f|
    count.times do |i|
      in_file = "./generator/#{no}-#{i + 1}.in"
      out_file = "#{f.sub('codes', 'out').sub('.py', '')}-#{i + 1}.out"
      pid = Process.spawn "python3 #{f} < #{in_file} > #{out_file}"
      Timeout.timeout(5) do
        Process.wait pid
      end
    rescue Timeout::Error
      puts "Timeout for #{f} when tests #{i + 1} case"
      File.delete out_file
      Process.kill 'KILL', pid
    end
  rescue StandardError
    puts "Error for #{f}"
  end
end

run 'A', 3
run 'B', 3
run 'C', 4
