LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiplexer_8_2 is
  port (A0, A1 : in std_logic_vector(7 downto 0); S : in std_logic; Y : out std_logic_vector(7 downto 0));
end multiplexer_8_2;

architecture behaviour of multiplexer_8_2 is
begin
  b: process is
  begin
    if S = '1' then
      Y <= A1;
    else
      Y <= A0;
    end if;
    wait for 5 ns;
  end process b;
end behaviour;
