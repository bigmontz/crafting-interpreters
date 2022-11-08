defmodule Elox.Scanner do
  def scan(source, tokens \\ [], start \\ 0, current \\ 0, line \\ 1) do
    case is_at_end(source, current) do
      true ->
        [%Elox.Token{type: :eof, lexeme: "", literal: nil, line: line} | tokens]
        |> Enum.reverse()

      false ->
        _scan(source, tokens, start, current, line)
    end
  end

  defguard is_digit(c) when c >= "0" and c <= "9"
  defguard is_alpha(c) when c >= "a" and c <= "z" or c >= "A" and c <= "Z" or c == "_"

  def _scan(source, tokens, start, current, line) do
    new_token = fn type, size, literal, line_inc ->
      [
        %Elox.Token{
          type: type,
          lexeme: String.slice(source, start..(current + size - 1)),
          line: line,
          literal: literal
        },
        size,
        line_inc
      ]
    end

    new_token_nil = fn type, size ->
      new_token.(type, size, nil, 0)
    end

    [token, size, line_inc] =
      case String.at(source, current) do
        "(" ->
          new_token_nil.(:left_paren, 1)

        ")" ->
          new_token_nil.(:right_paren, 1)

        "{" ->
          new_token_nil.(:left_brace, 1)

        "}" ->
          new_token_nil.(:right_brace, 1)

        "," ->
          new_token_nil.(:comma, 1)

        "." ->
          new_token_nil.(:dot, 1)

        "-" ->
          new_token_nil.(:minus, 1)

        "+" ->
          new_token_nil.(:plus, 1)

        "*" ->
          new_token_nil.(:star, 1)

        ";" ->
          new_token_nil.(:semicolon, 1)

        "!" ->
          if String.at(source, current + 1) == "=",
            do: new_token_nil.(:bang_equal, 2),
            else: new_token_nil.(:bang, 1)

        "=" ->
          if String.at(source, current + 1) == "=",
            do: new_token_nil.(:equal_equal, 2),
            else: new_token_nil.(:equal, 1)

        "<" ->
          if String.at(source, current + 1) == "=",
            do: new_token_nil.(:less_equal, 2),
            else: new_token_nil.(:less, 1)

        ">" ->
          if String.at(source, current + 1) == "=",
            do: new_token_nil.(:greater_equal, 2),
            else: new_token_nil.(:greater, 1)

        "/" ->
          if String.at(source, current + 1) == "/",
            do: [nil, move_until_next_line(source, start, current + 1), 1],
            else: new_token_nil.(:slash, 1)

        "\n" ->
          [nil, 1, 1]

        c when c in [" ", "\r", "\t"] ->
          [nil, 1, 0]

        "\"" ->
          [literal, size, line_inc] = scan_string(source, start, current + 1, line)

          if literal != nil,
            do: new_token.(:string, size, literal, line_inc),
            else: [nil, size, line_inc]

        d when is_digit(d) ->
          [literal, size] = scan_number(source, start, current + 1, line)
          if literal != nil, do: new_token.(:number, size, literal, 0), else: [nil, size, 0]

        c when is_alpha(c) -> 
          [literal, size] = scan_identifier(source, start, current + 1, line)
          if literal != nil, do: new_token.(:identifier, size, literal, 0), else: [nil, size, 0]

        unexpectedChar ->
          Elox.Error.report(line, "Unexpected character: #{unexpectedChar}")
          [nil, 1, 0]
      end

    case token do
      nil -> scan(source, tokens, current + size, current + size, line + line_inc)
      _ -> scan(source, [token | tokens], current + size, current + size, line + line_inc)
    end
  end

  def move_until_next_line(source, start, current) do
    case String.at(source, current) do
      "\n" -> current - start
      nil -> current - start
      _ -> move_until_next_line(source, start, current + 1)
    end
  end

  def scan_string(source, start, current, line, line_inc \\ 0) do
    case is_at_end(source, current) do
      true ->
        Elox.Error.report(line, "Unterminated string")
        [nil, current - start, line_inc]

      false ->
        case String.at(source, current) do
          "\"" ->
            [String.slice(source, (start + 1)..(current - 1)), current - start + 1, line_inc]

          "\n" ->
            scan_string(source, start, current + 1, line + 1, line_inc + 1)

          _ ->
            scan_string(source, start, current + 1, line, line_inc)
        end
    end
  end

  def scan_number(source, start, current, line, has_dot \\ false) do 
    c = String.at(source, current)
    case is_digit(c) do 
      true -> scan_number(source, start, current+1, line, has_dot)
      false -> 
          case has_dot or c != "." or not is_digit(String.at(source, current + 1)) do 
            true -> 
              { literal, _ } = String.slice(source, start..(current-1)) |> Float.parse()
              [literal, current - start]
            false -> 
              scan_number(source, start, current+1, line, true)
          end
    end
  end

  def scan_identifier(source, start, current, line) do 
    c = String.at(source, current)
    case is_digit(c) or is_alpha(c) do 
      true -> scan_identifier(source, start, current+1, line)
      false -> 
          literal = String.slice(source, start..(current-1)) 
          [literal, current - start]
    end
  end

  def is_at_end(source, current) do
    String.length(source) <= current
  end
end
