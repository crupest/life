#!/usr/bin/env ruby

Dir.glob('./codes/*.cpp').each do |f|
  output_file_name = f.sub('codes', 'build').gsub('.cpp', '')
  `clang++ -std=c++11 #{f} -o #{output_file_name}`
end
