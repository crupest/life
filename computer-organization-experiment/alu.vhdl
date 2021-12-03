LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.numeric_std.all;

entity alu is
    port (A, B: in std_logic_vector(31 downto 0); ALUC: in std_logic_vector(3 downto 0); S: out std_logic_vector(31 downto 0); Z: out std_logic);
end entity;

architecture Behavioral of alu is
begin
    S <= A + B when ALUC(2 downto 0) = B"000"
         else A and B when ALUC(2 downto 0) ?= B"001"
         else A - B when ALUC(2 downto 0) ?= B"100"
         else A or B when ALUC(2 downto 0) ?= B"101"
         else A xor B when ALUC(2 downto 0) ?= B"010"
         else std_logic_vector(signed(A) sll 16) and B"11111111111111110000000000000000" when ALUC(2 downto 0) ?= B"110"
         else std_logic_vector(signed(A) sll to_integer(unsigned(B))) when ALUC ?= B"0011"
         else std_logic_vector(signed(A) srl to_integer(unsigned(B))) when ALUC ?= B"0111"
         else std_logic_vector(signed(A) sra to_integer(unsigned(B))) when ALUC ?= B"1111";
    Z <= S ?= "00000000000000000000000000000000";
end architecture;
