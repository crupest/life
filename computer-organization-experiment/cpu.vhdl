library ieee;
use ieee.std_logic_1164.all;

package cru is
    subtype word is std_logic_vector(31 downto 0);
    constant clock_time : time := 10 ns;
end package;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity generic_clock is
    generic(delay, interval: time);
    port(CLK: out std_logic);
end entity;

architecture Behavioral of generic_clock is
    signal V : std_logic := '1';
begin
    l: process is
    begin
        CLK <= '0';
        wait for delay;
        loop
            CLK <= V;
            V <= not V;
            wait for interval;
        end loop;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity reg is
    port (
        CLK: in std_logic; -- Rising edge -> Read; Falling edge -> Write.
        WRITE: in std_logic; -- If 1 then at falling edge of clock, W will be written.
        W_DATA: in word; -- The data to write.
        R_DATA: out word -- The data to read.
    );
end entity;

architecture Behavioral of reg is
    signal V: word := X"00000000";
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            R_DATA <= V;
        end if;
        if falling_edge(CLK) and WRITE = '1' then
            V <= W_DATA;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.cru.all;

entity register_file is
    port (
        CLK: in std_logic;
        WRITE: in std_logic;
        R1, R2, W: in std_logic_vector(4 downto 0);
        WD: in std_logic_vector(31 downto 0);
        RD1, RD2: out std_logic_vector(31 downto 0)
    );
end entity;

architecture Behavioral of register_file is
    type reg_file_type is array (0 to 31) of word;
    signal reg_file: reg_file_type := (others => X"00000000");
begin
    process (CLK)
    begin
        if rising_edge(CLK) then
            RD1 <= reg_file(to_integer(unsigned(R1)));
            RD2 <= reg_file(to_integer(unsigned(R2)));
        end if;
        if falling_edge(CLK) and WRITE = '1' then
            reg_file(to_integer(unsigned(W))) <= WD;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use work.cru.all;

entity alu is
    port (
        A, B: in std_logic_vector(31 downto 0);
        ALUC: in std_logic_vector(3 downto 0);
        S: out std_logic_vector(31 downto 0);
        Z: out std_logic
    );
end entity;

architecture Behavioral of alu is
begin
    S <= A + B when ALUC(2 downto 0) ?= B"000"
         else A - B when ALUC(2 downto 0) ?= B"010"
         else A and B when ALUC(2 downto 0) ?= B"100"
         else A or B when ALUC(2 downto 0) ?= B"101"
         else A xor B when ALUC(2 downto 0) ?= B"110"
         else std_logic_vector(signed(A) sll 16) and X"FFFF0000" when ALUC(2 downto 0) ?= B"110"
         else std_logic_vector(signed(A) sll to_integer(unsigned(B))) when ALUC ?= B"0011"
         else std_logic_vector(signed(A) srl to_integer(unsigned(B))) when ALUC ?= B"1011"
         else std_logic_vector(signed(A) sra to_integer(unsigned(B))) when ALUC ?= B"1111";
    Z <= S ?= X"00000000" after 10 ps;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.cru.all;

entity ram is
    port(
        CLK: in std_logic;
        R_DATA: out word;
        W_DATA: in word;
        ADDR: in word;
        READ: in std_logic;
        WRITE: in std_logic
    );
end entity;

architecture Behavioral of ram is
    type memory_type is array (0 to 16#30#) of word;
    signal memory: memory_type := (
/*
                X"3c010000",
                X"34240080",
                X"20050004",
                X"0c000018",
                X"ac820000",
                X"8c890000",
                X"01244022",
                X"20050003",
                X"20a5ffff",
                X"34a8ffff",
                X"39085555",
                X"2009ffff",
                X"312affff",
                X"01493025",
                X"01494026",
                X"01463824",
                X"10a00001",
                X"08000008",
                X"2005ffff",
                X"000543c0",
                X"00084400",
                X"00084403",
                X"000843c2",
                X"08000017",
                X"00004020",
                X"8c890000",
                X"20840004",
                X"01094020",
                X"20a5ffff",
                X"14a0fffb",
                X"00081000",
                X"03e00008",
                X"000000A3",
                X"00000027",
                X"00000079",
                X"00000115",
*/
                X"3C010000",
                X"3421004C",
                X"8C240000",
                X"20210004",
                X"8C250000",
                X"20210004",
                X"0C000009",
                X"AC230000",
                X"08000008",
                X"20020010",
                X"00001820",
                X"30A60001",
                X"10060001",
                X"00641820",
                X"00042040",
                X"00052842",
                X"2042FFFF",
                X"1440FFF9",
                X"03e00008",
                X"0000C9AE",
                X"0000F6E5",
                others => (others => '0')
        );
begin
    l: process(CLK) is 
    begin
        if rising_edge(CLK) and READ = '1' then
            r_data <= memory(to_integer(unsigned(ADDR)) / 4);
        end if;
        if falling_edge(CLK) and WRITE = '1' then
            memory(to_integer(unsigned(ADDR)) / 4) <= w_data;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use work.cru.all;

entity cpu is
end entity;

architecture Behavioral of cpu is
    signal pc_clk: std_logic := '0';
    signal reg_clk: std_logic := '0';
    signal mem_clk: std_logic := '0';

    signal pc: word := X"00000000";
    signal pc_to_write: word;

    signal ins: word;

    signal mem_addr: word;
    signal mem_r_data: word;
    signal mem_w_data: word;
    signal mem_read: std_logic := '0';
    signal mem_write: std_logic := '0';

    signal WRITE_REG: std_logic := '0';
    signal R1: std_logic_vector(4 downto 0) := B"00000";
    signal R2: std_logic_vector(4 downto 0)  := B"00000";
    signal W: std_logic_vector(4 downto 0)  := B"00000";
    signal WD: std_logic_vector(31 downto 0) := X"00000000";
    signal RD1: std_logic_vector(31 downto 0) := X"00000000";
    signal RD2: std_logic_vector(31 downto 0) := X"00000000";

    signal A: std_logic_vector(31 downto 0) := X"00000000";
    signal B: std_logic_vector(31 downto 0) := X"00000000";
    signal ALUC: std_logic_vector(3 downto 0) := B"0000";
    signal S: std_logic_vector(31 downto 0);
    signal Z: std_logic;
begin
    pc_clock: entity work.generic_clock
        generic map (delay => 1 ps, interval => clock_time)
        port map (CLK => pc_clk);

    mem_clock: entity work.generic_clock
        generic map (delay => 1 ns, interval => clock_time / 2)
        port map (CLK => mem_clk);

    reg_clock: entity work.generic_clock
        generic map (delay => 2 ns, interval => clock_time)
        port map (CLK => reg_clk);

    pc_reg: entity work.reg
        port map (
            CLK => pc_clk,
            WRITE => '1',
            R_DATA => pc,
            W_DATA => pc_to_write
        );
    
    reg_file: entity work.register_file
        port map(
            CLK => reg_clk,
            WRITE => WRITE_REG,
            R1 => R1,
            R2 => R2,
            W => W,
            WD => WD,
            RD1 => RD1,
            RD2 => RD2
        );

    alu: entity work.alu
        port map(
            A => A,
            B => B,
            ALUC => ALUC,
            S => S,
            Z => Z
        );

    ram: entity work.ram
        port map (
            CLK => mem_clk,
            r_data => mem_r_data,
            w_data => mem_w_data,
            addr => mem_addr,
            READ => mem_read,
            WRITE => mem_write
        );

    logic: process is
    begin
        wait until rising_edge(pc_clk);

        wait for 100 ps;

        mem_read <= '1';
        mem_addr <= pc;
        pc_to_write <= pc + 4;

        wait for 1 ns;

        ins <= mem_r_data;

        wait for 100 ps;

        if ins(31 downto 27) = B"00001" then -- j / jal, not read reg
            R1 <= (others => '0');
            R2 <= (others => '0');
        elsif ins(31 downto 26) = B"000000" then
            if ins(5) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);
            elsif ins(3) = '0' then
                R1 <= ins(20 downto 16);
                R2 <= (others => '0');
            else
                R1 <= ins(25 downto 21);
                R2 <= (others => '0');
            end if;
        else
            if ins(31) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);
            elsif ins(29 downto 26) = B"1111" then
                R1 <= (others => '0');
                R2 <= (others => '0');
            elsif ins(29) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= (others => '0');
            else
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);
            end if;
        end if;

        wait for 1 ns;

        if ins(31 downto 27) = B"00001" then -- j / jal, not read reg

            ALUC <= B"0011";
            A <= (25 downto 0 => ins(25 downto 0), others => '0');
            B <= X"00000002";
        elsif ins(31 downto 26) = B"000000" then
            if ins(5) = '1' then
                ALUC <= ins(3 downto 0);
                A <= RD1;
                B <= RD2;
            elsif ins(3) = '0' then
                ALUC(3 downto 2) <= ins(1 downto 0);
                ALUC(1 downto 0) <= B"11";
                A <= RD1;
                B <= (4 downto 0 => ins(10 downto 6), others => '0');
            else
                ALUC <= (others => '0');
                A <= (others => '0');
                B <= (others => '0');
            end if;
        else
            if ins(31) = '1' then
                ALUC <= B"0000";
                A <= RD1;
                B <= (15 downto 0 => ins(15 downto 0), others => '0' );
            elsif ins(29 downto 26) = B"1111" then
                ALUC <= (others => '0');
                A <= (others => '0');
                B <= (others => '0');
            elsif ins(29) = '1' then
                ALUC <= ins(29 downto 26);
                A <= RD1;
                B(15 downto 0) <= ins(15 downto 0);
                if ins(15) = '0' then
                    B(31 downto 16) <= X"0000";
                else
                    B(31 downto 16) <= X"FFFF";
                end if;
            else
                ALUC <= B"0010";
                A <= RD1;
                B <= RD2;
            end if;
        end if;

        wait for 100 ps;

        if ins(31 downto 27) = B"00001" then -- j / jal, not read reg
            if ins(26) = '1' then -- jal
                W <= B"11111";
                WD <= pc + 4;
                WRITE_REG <= '1';
            else
                WRITE_REG <= '0';
            end if;
            pc_to_write <= S; 
        elsif ins(31 downto 26) = B"000000" then
            if ins(5) = '1' then
                WRITE_REG <= '1';
                W <= ins(15 downto 11);
                WD <= S;
            elsif ins(3) = '0' then
                WRITE_REG <= '1';
                W <= ins(15 downto 11);
                WD <= S;
            else
                WRITE_REG <= '0';
                pc_to_write <= RD1;
            end if;
        else
            if ins(31) = '1' then
                if ins(29) = '1' then
                    R2 <= ins(20 downto 16);
                    mem_write <= '1';
                    mem_addr <= S;
                    mem_w_data <= RD2;

                    wait until falling_edge(mem_clk);

                    wait for 100 ps;

                    mem_write <= '0';

                else
                    W <= ins(20 downto 16);
                    mem_read <= '1';
                    mem_addr <= S;

                    wait until rising_edge(mem_clk);
                    
                    wait for 100 ps;

                    WD <= mem_r_data;
                    WRITE_REG <= '1';
                end if;
            elsif ins(29 downto 26) = B"1111" then
                WRITE_REG <= '1';
                W <= ins(20 downto 16);
                WD(31 downto 16) <= ins(15 downto 0);
            elsif ins(29) = '1' then
                WRITE_REG <= '1';
                W <= ins(20 downto 16);
                WD <= S;
            else
                WRITE_REG <= '0';
                if Z = '1' xor ins(26) = '1' then
                    pc_to_write <= pc_to_write + to_integer(signed(ins(15 downto 0)) * 4);
                end if;
            end if;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use work.cru.all;

entity cpu_test_bench is
end entity;

architecture Behavioral of cpu_test_bench is
    signal CLK: std_logic;
begin
    cpu : entity work.cpu;
end architecture;
