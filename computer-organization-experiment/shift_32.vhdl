LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.numeric_std.all;

entity shift_32 is
  port(
    D: in std_logic_vector(31 downto 0);
    SA: in std_logic_vector(4 downto 0);
    Right: in std_logic;
    Arith: in std_logic;
    SH: out std_logic_vector(31 downto 0)
  );
end entity;

architecture behavioral of shift_32 is
begin
  SH <= 
         std_logic_vector(signed(D) srl to_integer(unsigned(SA))) when Right = '1' and Arith = '0'
    else std_logic_vector(signed(D) sll to_integer(unsigned(SA))) when Right = '0' and Arith = '0'
    else std_logic_vector(signed(D) sra to_integer(unsigned(SA)))  when Right = '1' and Arith = '1'
    else std_logic_vector(signed(D) sla to_integer(unsigned(SA))) when Right = '0' and Arith = '1';
end behavioral;
