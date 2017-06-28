tests = {
  "hello_world" => "Hello World",
  "factorial" => "120",
  "str_concat" => "HelloWorld",
  "if" => "OK",
  "end" => "Antes de terminar",
  "resta_str" => "hola te va espero que muy "
}

results = {}

tests.each do |program, expected|
  %x(./compile.sh ./tests/#{program}.pr)
  res = %x(./prose.out)
  if (res.chomp == expected)
    p "#{program}.pr OK"
    results[program] = "OK"
  else
    p "#{program}.pr FAILED -> (expected: #{expected}, real: #{res})"
    results[program] = "FAILED -> (expected: #{expected}, real: #{res})"
  end
end

results.each do |program, result|
    puts "#{program} => #{result}"
end
