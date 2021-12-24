library ieee;

entity register_file is
    port (
        CLK: in std_logic;
        WRITE: in std_logic;
        R1, R2, W: in std_logic_vector(4 downto 0);
        WD: in std_logic_vector(31 downto 0);
        RD1, RD2: out std_logic_vector(31 downto 0);
    )
end entity;

architecture Behavioral of register_file is
    type reg_file_type is array (0 to 31) of std_logic_vector(31 downto 0);
    signal reg_file: reg_file_type := (others => '0');
begin
    process (CLK)
    begin
        if rising_edge(CLK) then
        begin
            if WRITE then
                reg_file(W) <= WD;
            end;
            RD1 <= reg_file(R1);
            RD2 <= reg_file(R2);
        end;
    end;
end architecture;
