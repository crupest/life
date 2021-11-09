LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity full_adder_1 is
    port (A, B, CI:in std_logic; S, CO: out std_logic);
end full_adder_1;

architecture behavior of full_adder_1 is
begin
    S <= (A XOR B) XOR CI;
    CO <= (A AND B) OR (B AND CI) OR (CI AND A);
end architecture;
