LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity adder_8 is
    port (A, B:in std_logic_vector(7 downto 0);  CIN:in std_logic; S: out std_logic_vector(7 downto 0); COUT: out std_logic);
end adder_8;

architecture behavior of adder_8 is
    signal C : std_logic_vector(6 downto 0);
begin
    b0: entity work.adder_1
        port map (A=>A(0), B=>B(0), CIN=>CIN, S=>S(0), COUT=>C(0));
    b1: entity work.adder_1
        port map (A=>A(1), B=>B(1), CIN=>C(0), S=>S(1), COUT=>C(1));
    b2: entity work.adder_1
        port map (A=>A(2), B=>B(2), CIN=>C(1), S=>S(2), COUT=>C(2));
    b3: entity work.adder_1
        port map (A=>A(3), B=>B(3), CIN=>C(2), S=>S(3), COUT=>C(3));
    b4: entity work.adder_1
        port map (A=>A(4), B=>B(4), CIN=>C(3), S=>S(4), COUT=>C(4));
    b5: entity work.adder_1
        port map (A=>A(5), B=>B(5), CIN=>C(4), S=>S(5), COUT=>C(5));
    b6: entity work.adder_1
        port map (A=>A(6), B=>B(6), CIN=>C(5), S=>S(6), COUT=>C(6));
    b7: entity work.adder_1
        port map (A=>A(7), B=>B(7), CIN=>C(6), S=>S(7), COUT=>COUT);
end behavior;
