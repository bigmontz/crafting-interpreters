defmodule Elox.Error do
  def report(line, message, where \\ "") do
    IO.puts("[line #{line}] Error #{where}: #{message}")
  end
end
