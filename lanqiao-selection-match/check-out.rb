#!/usr/bin/env ruby

require 'csv'

$result = {}
$answer = {
  'A' => [9, 11, 9],
  'B' => [10_199_346, 872_919_755, 21_850_795_004],
  'C' => [91, 898, 9006, 89_794]
}

# @param student_no [String]
# @param question_no [String]
# @param answer [Array]
def check(student_no, question_no, test_no)
  out_file = "./out/#{student_no}#{question_no}-#{test_no}.out"
  if File.read(out_file).to_i == $answer[question_no][test_no - 1]
    $result[student_no] ||= []
    $result[student_no] << "#{question_no}-#{test_no}"
  end
end

Dir.entries('./out').each do |f|
  next if ['.', '..'].include?(f)

  /(\d+)([ABC])-(\d)\.out/ =~ f
  if Regexp.last_match.nil?
    puts "Error: #{f}"
    exit 1
  end

  check(Regexp.last_match(1), Regexp.last_match(2), Regexp.last_match(3).to_i)
end

CSV.open('./result.csv', 'w') do |csv|
  qs = %w[A-1 A-2 A-3 B-1 B-2 B-3 C-1 C-2 C-3 C-4]
  csv << (['student no'] + qs)
  $result.each do |student_no, questions|
    csv << ([student_no] + qs.map { |q| questions.include?(q) ? 1 : 0 })
  end
end
