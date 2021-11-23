LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity adder_1 is
    port (A, B, CIN:in std_logic; S, COUT: out std_logic);
end adder_1;

architecture behavior of adder_1 is
begin
    S <= (A XOR B) XOR CIN;
    COUT <= (A AND B) OR (B AND CIN) OR (CIN AND A);
end behavior;
