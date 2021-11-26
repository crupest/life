LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiplexer_8_2 is
  port (A0, A1 : in std_logic_vector(7 downto 0); S : in std_logic; Y : out std_logic_vector(7 downto 0));
end multiplexer_8_2;

architecture behaviour of multiplexer_8_2 is
begin
  Y <= A0 when S = '0' else A1;
end behaviour;
