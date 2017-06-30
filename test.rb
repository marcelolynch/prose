tests = {
  "hello_world" => "Hello World",
  "factorial" => "120",
  "str_concat" => "HelloWorld",
  "if" => "OK",
  "end" => "Antes de terminar",
  "resta_str" => "hola te va espero que muy ",
  "array_sub" => "['como', 'vaaa']",
  "array_sort" => "[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]",
  "array_append" => "[1, 2, 3, 4, 5, 'Hola']",
  "empty_array" => "[]",
  "precedencia_1" => "31",
  "precedencia_2" => "1holahola",
  "asociatividad_1" => "2hola",
  "asociatividad_2" => "hola210",
  "stringdiv" => "['ab', 'cd', 'ef']"
}

results = {}

%x(cd compiler ; make all ; cd ..)

tests.each do |program, expected|
  %x(./compile.sh ./tests/#{program}.pr)
  res = %x(./prose.out)
  if (res.chomp == expected)
    results[program] = "OK"
  else
    results[program] = "FAILED -> (expected: #{expected}, real: #{res})"
  end
end

results.each do |program, result|
    puts "#{program} => #{result}"
end
