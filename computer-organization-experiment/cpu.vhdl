library ieee;

subtype word of std_logic_vector(31 downto 0);
constant clock_time : time := 10 ns;

entity register is
    port (
        CLK: in std_logic; -- Rising edge -> Read; Falling edge -> Write.
        W: in word; -- The data to write.
        ENABLE: in std_logic; -- If 1 then at falling edge of clock, W will be written.
        ZERO: in std_logic; -- If 1 then at rising edge of clock, 0 will be output to R.
        R: out word; -- The data to read.
    )
end entity;

architecture Behavioral of register is
    signal V: word;
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            if ZERO = '1' then
                R <= (others => '0');
            else
                R <= V;
            end if;
        end if;
        if falling_edge(CLK) and ENABLE = '1' then
            V <= W;
        end if;
    end process;
end architecture;

entity register_file is
    port (
        CLK: in std_logic;
        ENABLE: in std_logic;
        ZERO1, ZERO2: in std_logic;
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
            if ZERO1 = '1' then
                RD1 <= (others => '0');
            else
                RD1 <= reg_file(to_integer(R1));
            end if;
            if ZERO2 = '1' then
                RD2 <= (others => '0');
            else
                RD2 <= reg_file(to_integer(R2));
            end if;
        end if;
        if falling_edge(CLK) and ENABLE = '1' then
            reg_file(to_integer(W)) <= WD;
        end if;
    end;
end architecture;

entity alu is
    port (
        A, B: in std_logic_vector(31 downto 0);
        ALUC: in std_logic_vector(3 downto 0);
        S: out std_logic_vector(31 downto 0);
        Z: out std_logic);
end entity;

architecture Behavioral of alu is
begin
    S <= A + B when ALUC(2 downto 0) ?= B"000"
         else A - B when ALUC(2 downto 0) ?= B"010"
         else A and B when ALUC(2 downto 0) ?= B"100"
         else A or B when ALUC(2 downto 0) ?= B"101"
         else A xor B when ALUC(2 downto 0) ?= B"110"
         else std_logic_vector(signed(A) sll 16) and H"FFFF0000" when ALUC(2 downto 0) ?= B"110"
         else std_logic_vector(signed(A) sll to_integer(unsigned(B))) when ALUC ?= B"0011"
         else std_logic_vector(signed(A) srl to_integer(unsigned(B))) when ALUC ?= B"0111"
         else std_logic_vector(signed(A) sra to_integer(unsigned(B))) when ALUC ?= B"1111";
    Z <= S ?= H"00000000";
end architecture;

entity clock is
    port(CLK: out std_logic)
end entity;

architecture Behavioral of clock is
begin
    CLK <= not CLK after clock_time;
end architecture;

type memory_type = array (0 to 1023) of std_logic_vector(31 downto 0);

entity cpu is
    port (memory: in memory_type)
end entity;

architecture Behavioral of cpu is
    signal pc: std_logic_vector(31 downto 0);
    signal pc_to_write: std_logic_vector(31 downto 0);

    signal CLK: in std_logic;
    signal WRITE_REG: in std_logic;
    signal R1, R2, W: in std_logic_vector(4 downto 0);
    signal WD: in std_logic_vector(31 downto 0);
    signal RD1, RD2: out std_logic_vector(31 downto 0);

    signal A, B: in std_logic_vector(31 downto 0);
    signal ALUC: in std_logic_vector(3 downto 0);
    signal S: out std_logic_vector(31 downto 0);
    signal Z: out std_logic);
begin
    pc_reg: register
        port map (
            CLK => CLK,
            ENABLE => '1',
            ZERO => '0',
            W => pc_to_write,
            R => pc
        );
    reg: register_file
        port map(
            CLK => CLK,
            ENABLE => WRITE_REG,
            R1 => R1,
            R2 => R2,
            W => W,
            WD => WD,
            RD1 => RD1,
            RD2 => RD2
        );
    alu: alu
        port map(
            A => A,
            B => B,
            ALUC => ALUC,
            S => S,
            Z => Z
        );
    logic: process is
        variable ins: std_logic_vector(31 downto 0);
    begin
        ins <= memory(to_integer(pc));
        pc_to_write <= pc + H"00000001";

        if ins(31 downto 26) = B"000000" then
            if ins(5) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);
                ALUC <= ins(3 downto 0);
                A <= RD1;
                B <= RD2;
                W <= ins(15 downto 11);
                WRITE_REG <= '1';
                WD <= S;
            else if ins(3) = '0' then
                R1 <= ins(20 downto 16);
                ALUC(3 downto 2) <= ins(1 downto 0);
                ALUC(1 downto 0) <= B"11";
                A <= RD1;
                B(31 downto 5) <= (others => '0');
                B(4 downto 0) <= ins(10 downto 6);
                W <= ins(15 downto 11);
                WRITE_REG <= '1';
                WD <= S;
            else
                R1 <= ins(25 downto 16)
                WRITE_REG <= '0';
                pc_to_write <= RD1;
            end if;
        else
            -- TODO: Implement this.
        end if;
        
    end process;
end architecture;
