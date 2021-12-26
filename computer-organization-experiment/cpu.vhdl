library ieee;
use ieee.std_logic_1164.all;

package cru is
    subtype word is std_logic_vector(31 downto 0);
    constant clock_time : time := 10 ns;
    constant ram_clock_time: time := 2.5 ns;
end package;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity reg is
    port (
        CLK: in std_logic; -- Rising edge -> Read; Falling edge -> Write.
        ENABLE: in std_logic; -- If 1 then at falling edge of clock, W will be written.
        W: in word; -- The data to write.
        R: out word -- The data to read.
    );
end entity;

architecture Behavioral of reg is
    signal V: word := (others => '0');
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            R <= V;
        end if;
        if falling_edge(CLK) and ENABLE = '1' then
            V <= W;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity reg_file_clock is
    port(CLK: out std_logic);
end entity;

architecture Behavioral of reg_file_clock is
    signal V: std_logic := '1';
begin
    l: process is
    begin
        CLK <= V;
        wait for 1 ns;
        loop
            V <= not V;
            wait for 1 ps;
            CLK <= V;
            wait for clock_time;
        end loop;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use work.cru.all;

entity register_file is
    port (
        ENABLE: in std_logic;
        R1, R2, W: in std_logic_vector(4 downto 0);
        WD: in std_logic_vector(31 downto 0);
        RD1, RD2: out std_logic_vector(31 downto 0)
    );
end entity;

architecture Behavioral of register_file is
    type reg_file_type is array (0 to 31) of std_logic_vector(31 downto 0);
    signal reg_file: reg_file_type := (others => (others => '0'));
    signal CLK : std_logic;
begin
    clock: entity work.reg_file_clock
        port map (CLK);
    process (CLK)
    begin
        if rising_edge(CLK) then
            RD1 <= reg_file(to_integer(unsigned(R1)));
            RD2 <= reg_file(to_integer(unsigned(R2)));
        end if;
        if falling_edge(CLK) and ENABLE = '1' then
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
         else std_logic_vector(signed(A) srl to_integer(unsigned(B))) when ALUC ?= B"0111"
         else std_logic_vector(signed(A) sra to_integer(unsigned(B))) when ALUC ?= B"1111";
    Z <= S ?= X"00000000" after 10 ps;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity clock is
    port(CLK: out std_logic);
end entity;

architecture Behavioral of clock is
    signal V: std_logic := '0';
begin
    V <= not V after clock_time;
    CLK <= V;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use work.cru.all;

entity ram_clock is
    port(CLK: out std_logic);
end entity;

architecture Behavioral of ram_clock is
    signal V: std_logic := '0';
begin
    l: process is
    begin
        CLK <= V;
        wait for 500 ps;
        loop
            V <= not V;
            wait for 1 ps;
            CLK <= V;
            wait for ram_clock_time;
        end loop;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.cru.all;

entity ram is
    port(
        R_DATA: out word;
        W_DATA: in word;
        R_ADDR: in word;
        W_ADDR: in word;
        READ: in std_logic;
        WRITE: in std_logic
    );
end entity;

architecture Behavioral of ram is
    type memory_type is array (0 to 16#30#) of word;
    signal memory: memory_type := (
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
                others => (others => '0')
        );
    signal V: std_logic := '0';
    signal CLK: std_logic;
begin
    clock: entity work.ram_clock
        port map (CLK);
    b: process(CLK) is 
    begin
        if rising_edge(CLK) and READ = '1' then
            R_DATA <= memory(to_integer(unsigned(R_ADDR)) / 4);
        end if;
        if falling_edge(CLK) and WRITE = '1' then
            memory(to_integer(unsigned(W_ADDR)) / 4) <= W_DATA;
        end if;
    end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
use work.cru.all;

entity cpu is
    port (
        CLK: in std_logic
    );
end entity;

architecture Behavioral of cpu is
    signal pc: word := X"00000000";
    signal pc_to_write: word;

    signal ins: word;

    signal mem_r_addr: word := X"00000000";
    signal mem_w_addr: word := X"00000000";
    signal mem_r_data: word;
    signal mem_w_data: word := X"00000000";
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
    pc_reg: entity work.reg
        port map (
            CLK => CLK,
            ENABLE => '1',
            W => pc_to_write,
            R => pc
        );
    reg: entity work.register_file
        port map(
            ENABLE => WRITE_REG,
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
            R_DATA => mem_r_data,
            W_DATA => mem_w_data,
            R_ADDR => mem_r_addr,
            W_ADDR => mem_w_addr,
            READ => mem_read,
            WRITE => mem_write
        );

    logic: process is
    begin
        wait until rising_edge(CLK);

        wait for 250 ps;

        mem_read <= '1';
        mem_r_addr <= pc;
        pc_to_write <= pc + 4;

        wait for 500 ps;

        ins <= mem_r_data;

        mem_write <= '0';

        WRITE_REG <= '0';
        
        wait for 100 ps;

        if ins(31 downto 27) = B"00001" then -- j / jal, not read reg
            if ins(26) = '1' then -- jal
                W <= B"11111";
                WD <= pc + 4;
                WRITE_REG <= '1';
            end if;

            ALUC <= B"0011";
            A <= (25 downto 0 => ins(25 downto 0), others => '0');
            B <= X"00000002";
            wait for 100 ps;
            pc_to_write <= S; 
        elsif ins(31 downto 26) = B"000000" then
            if ins(5) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);

                wait for 500 ps;

                ALUC <= ins(3 downto 0);
                A <= RD1;
                B <= RD2;

                wait for 100 ps;

                W <= ins(15 downto 11);
                WRITE_REG <= '1';
                WD <= S;
            elsif ins(3) = '0' then
                R1 <= ins(20 downto 16);

                wait for 500 ps;

                ALUC(3 downto 2) <= ins(1 downto 0);
                ALUC(1 downto 0) <= B"11";
                A <= RD1;
                B <= (4 downto 0 => ins(10 downto 6), others => '0');

                wait for 100 ps;

                W <= ins(15 downto 11);
                WRITE_REG <= '1';
                WD <= S;
            else
                R1 <= ins(25 downto 21);

                wait for 500 ps;

                pc_to_write <= RD1;
            end if;
        else
            if ins(31) = '1' then
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);

                wait for 500 ps;

                ALUC <= B"0000";
                A <= RD1;
                B <= (15 downto 0 => ins(15 downto 0), others => '0' );

                wait for 100 ps;

                if ins(29) = '1' then
                    R2 <= ins(20 downto 16);
                    mem_write <= '1';
                    mem_w_addr <= S;
                    mem_w_data <= RD2;

                else
                    W <= ins(20 downto 16);
                    mem_read <= '1';
                    mem_r_addr <= S;

                    wait for ram_clock_time * 2;

                    WD <= mem_r_data;
                    WRITE_REG <= '1';
                end if;
            elsif ins(29 downto 26) = B"1111" then
                WRITE_REG <= '1';
                W <= ins(20 downto 16);
                WD(31 downto 16) <= ins(15 downto 0);
            elsif ins(29) = '1' then
                R1 <= ins(25 downto 21);

                wait for 500 ps;

                ALUC <= ins(29 downto 26);
                A <= RD1;
                B(15 downto 0) <= ins(15 downto 0);
                if ins(15) = '0' then
                    B(31 downto 16) <= X"0000";
                else
                    B(31 downto 16) <= X"FFFF";
                end if;

                wait for 100 ps;

                W <= ins(20 downto 16);
                WRITE_REG <= '1';
                WD <= S;
            else
                R1 <= ins(25 downto 21);
                R2 <= ins(20 downto 16);
                
                wait for 500 ps;
                
                ALUC <= B"0010";
                A <= RD1;
                B <= RD2;

                wait for 100 ps;

                if Z = '1' xor ins(26) = '1' then
                    pc_to_write <= pc_to_write + to_integer(signed(ins(15 downto 0)) * 4);
                end if;
                WRITE_REG <= '0';
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
    clock: entity work.clock
        port map (
            CLK
        );
    cpu : entity work.cpu
        port map (
            CLK
        );
end architecture;
