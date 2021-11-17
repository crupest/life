LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiplexer_1_2 is
  port (A0, A1, S : in std_logic; Y: out std_logic);
end multiplexer_1_2;

architecture behaviour of multiplexer_1_2 is
begin
  b: process is
  begin
    if S = '1' then
      Y <= A1;
    else
      Y <= A0;
    end if;
    wait for 1 ps;
  end process b;
end behaviour;
