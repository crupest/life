library ieee;

entity register is
    port (
        D : in std_logic_vector(31 downto 0);
        CLK, EN, CLRN: in std_logic;
        Q: out std_logic_vector(31 downto 0)
    )
end register;

architecture Behavioral of register is
begin
    storage: process is
    begin
        if CLRN = '0' then
            Q <= H"00000000";
        elsif rising_edge(CLK) and EN = '1' then
            Q <= D;
        end if;
    end process;
end Behavioral;
