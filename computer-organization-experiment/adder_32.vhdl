LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity adder_32 is
    port (A, B:in std_logic_vector(31 downto 0);  CIN:in std_logic; S: out std_logic_vector(31 downto 0); COUT: out std_logic);
end adder_32;

architecture behavior of adder_32 is
    signal C : std_logic_vector(2 downto 0);
begin
    c0: entity work.adder_8
        port map (A=>A(7 downto 0), B=>B(7 downto 0), CIN=>CIN, S=>S(7 downto 0), COUT=>C(0));
    c1: entity work.adder_8
        port map (A=>A(15 downto 8), B=>B(15 downto 8), CIN=>C(0), S=>S(15 downto 8), COUT=>C(1));
    c2: entity work.adder_8
        port map (A=>A(23 downto 16), B=>B(23 downto 16), CIN=>C(1), S=>S(23 downto 16), COUT=>C(2));
    c3: entity work.adder_8
        port map (A=>A(31 downto 24), B=>B(31 downto 24), CIN=>C(2), S=>S(31 downto 24), COUT=>COUT);
end behavior;
