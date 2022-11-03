defmodule Elox.CLI do
  def main(args) do
    case args do
      [file_name] -> run_file(file_name)
      [] -> run_prompt()
      _ -> notify_error("Usage: elox [script]")
    end
  end

  def run_file(file_name) do
    case File.read(file_name) do
      {:ok, source} -> run(source)
      {:error, reason} -> notify_error("Error opening #{file_name}: #{reason}")
    end
  end

  def run_prompt() do
    case IO.gets("> ") do
      :eof ->
        IO.puts("bye!!")

      source ->
        run(source)
        run_prompt()
    end
  end

  def run(source) do
    Elox.Scanner.scan(source)
    |> Enum.map(fn token -> "#{inspect(token)} \n" end)
    |> IO.puts()
  end

  def notify_error(error) do
    IO.puts(error)
    System.halt(64)
  end
end
