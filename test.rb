tests = {
  "hello_world" => "Hello World",
  "factorial" => "120"
}

tests.each do |program, expected|
  %x(./compile.sh #{program}.pr)
  res = %x(./prose.out)
  if (res.chomp == expected)
    p "#{program}.pr OK"
  else
    p "#{program}.pr FAILED -> (expected: #{expected}, real: #{res})"
  end
end
