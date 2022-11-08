defmodule EloxTest.Scanner do
  use ExUnit.Case, async: true

  for {empty_script, line} <- [
    {"", 1},
    {" ", 1},
    {"\r", 1},
    {"\t", 1},
    {"\r\n", 1}, # it should be second line, investigate
    {"\n", 2},
    {"\n\n", 3},
    {"// comment", 2}
  ] do
    @fixture { empty_script, line }
    test "Elox.Scanner.scan/1 should scan \"#{empty_script}\"" do
      { script, l } = @fixture
      assert Elox.Scanner.scan(script) == [eof_at_line(l)]
    end
  end 

  for {lexeme, type} <- [
    {"(", :left_paren},
    {")", :right_paren},
    {"{", :left_brace},
    {"}", :right_brace},
    {",", :comma},
    {".", :dot},
    {"-", :minus},
    {"+", :plus},
    {"*", :star},
    {";", :semicolon},
    {"!", :bang},
    {"!=", :bang_equal},
    {"=", :equal},
    {"==", :equal_equal},
    {"<", :less},
    {"<=", :less_equal},
    {">", :greater},
    {">=", :greater_equal},
    {"/", :slash}
  ] do
    @fixture {lexeme, type}
    test "Elox.Scanner.scan/1 should scan \"#{lexeme}\"" do
      { l, t } = @fixture
      assert Elox.Scanner.scan(l) === [single_char_at_line(t, l), eof_at_line()]
    end
  end

  for {lexeme, type, literal, line} <- [
    {"\"My Nice String\"", :string, "My Nice String", 1},
    {"\"My Nice String\n String\"", :string, "My Nice String\n String", 2},
    {"\"My Nice String\n String \n blob\"", :string, "My Nice String\n String \n blob", 3},
    {"987654321", :number, 987654321.0, 1},
    {"123456789.01", :number, 123456789.01, 1},
    {"var", :identifier, "var", 1},
    {"my_var", :identifier, "my_var", 1},
    {"mY_va112r", :identifier, "mY_va112r", 1}
  ] do
    @fixture {lexeme, type, literal, line}
    test "Elox.Scanner.scan/1 should scan \"#{lexeme}\"" do
      { lex, t, lit, lin } = @fixture
      assert Elox.Scanner.scan(lex) === [single_char_at_line(t, lex, lit), eof_at_line(lin)]
    end
  end

  def eof_at_line(line \\ 1) do
    %Elox.Token{type: :eof, line: line, lexeme: "", literal: nil}
  end

  def single_char_at_line(type, lexeme, literal \\ nil, line \\ 1) do
    %Elox.Token{type: type, line: line, lexeme: lexeme, literal: literal}
  end
end
