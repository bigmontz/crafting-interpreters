defmodule Elox.Token do
  defstruct [:type, :lexeme, :literal, :line]

  @types [
    left_paren: :single_char,
    right_paren: :single_char,
    left_brace: :single_char,
    right_brace: :single_char,
    comma: :single_char,
    dot: :single_char,
    minus: :single_char,
    plus: :single_char,
    semicolon: :single_char,
    slash: :single_char,
    star: :single_char,
    bang: :one_or_two_chars,
    bang_equal: :one_or_two_chars,
    equal: :one_or_two_chars,
    equal_equal: :one_or_two_chars,
    greater: :one_or_two_chars,
    greater_equal: :one_or_two_chars,
    less: :one_or_two_chars,
    less_equal: :one_or_two_chars,
    identifier: :literal,
    number: :literal,
    string: :literal,
    eof: :eof
  ]
end
