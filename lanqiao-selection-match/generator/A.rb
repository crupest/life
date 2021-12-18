#!/usr/bin/env ruby
# frozen_string_literal: true

# @param file [File]
def generate(count, file)
  range = -100_000..100_000
  prng = Random.new
  file.write(count)
  file.write("\n")
  count.times do
    file.write(prng.rand(range))
    file.write(' ')
  end
end

3.times do |i|
  file = File.open("A-#{i + 1}.in", 'w')
  count = case i
          when 0 then 1000
          when 1 then 10_000
          else 100_000
          end
  generate count, file
  file.close
end
