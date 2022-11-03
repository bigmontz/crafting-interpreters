defmodule EloxTest.Scanner do
  use ExUnit.Case, async: true

  test "Elox.Scanner.scan/1 should scan an empty string" do
    assert Elox.Scanner.scan("") == [eof_at_line()]
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
    @pair {lexeme, type}
    test "Elox.Scanner.scan/1 should scan \"#{lexeme}\"" do
      { l, t } = @pair
      assert Elox.Scanner.scan(l) === [single_char_at_line(t, l), eof_at_line()]
    end
  end

  def eof_at_line(line \\ 1) do
    %Elox.Token{type: :eof, line: line, lexeme: "", literal: nil}
  end

  def single_char_at_line(type, lexeme, line \\ 1) do
    %Elox.Token{type: type, line: line, lexeme: lexeme, literal: nil}
  end
end
