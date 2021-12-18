#!/usr/bin/env ruby
# frozen_string_literal: true

# @patam count [Integer]
# @param file [File]
def generate(count, file)
  alphabets = ('a'..'z').to_a
  prng = Random.new
  file.write(50)
  file.write("\n")
  count.times do
    file.write(alphabets[prng.rand(0...26)])
  end
end

4.times do |i|
  file = File.open("C-#{i + 1}.in", 'w')
  count = case i
          when 0 then 100
          when 1 then 1000
          when 2 then 10_000
          else 100_000
          end
  generate count, file
  file.close
end
