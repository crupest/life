LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity test_bench is
end test_bench;

architecture test_counter_4 of test_bench is
  signal CLK : STD_LOGIC;
  signal CQ: STD_LOGIC_VECTOR(3 DOWNTO 0);
begin
  counter: entity work.counter_4(behavior)
      port map (CLK, CQ);
  stimulus: process is
  begin
    for count_value in 0 to 2 ** 4 - 1 loop
      if count_value mod 2 = 0 then
        CLK <= '1';
        wait for 5 ns;
      else
        CLK <= '0';
        wait for 5 ns;
      end if;
    end loop;
  end process stimulus;
end architecture test_counter_4;


architecture test_full_adder_1 of test_bench is
  subtype v3 is std_logic_vector(2 downto 0);
  signal I: v3 := B"000";
  signal S, CO : STD_LOGIC;
begin
  adder: entity work.full_adder_1(behavior)
      port map (I(2), I(1), I(0), S, CO);
  stimulus: process is
    variable ii : v3 := B"000";
  begin
    loop
      ii := ii + 1;
      I <= ii;
      wait for 5 ns;
    end loop;
  end process stimulus;
end architecture test_full_adder_1;

architecture test_multiplexer_32_2 of test_bench is
  signal A0: std_logic_vector(31 downto 0) := B"11111111111111111111111111111111";
  signal A1: std_logic_vector(31 downto 0) := B"00000000000000000000000000000000";
  signal S: std_logic;
  signal Y: std_logic_vector(31 downto 0);
begin
  multiplexer: entity work.multiplexer_32_2(behaviour)
      port map (A0, A1, S, Y);
  stimulus: process is
  begin
    loop
      S <= '0';
      wait for 5 ns;
      S <= '1';
      wait for 5 ns;
    end loop;
  end process stimulus;
end architecture test_multiplexer_32_2;

architecture test_adder_32 of test_bench is
  signal A: std_logic_vector(31 downto 0) := B"00000000000000000000000000000000";
  signal B: std_logic_vector(31 downto 0) := B"00000000000000000000000000000000";
  signal CIN: std_logic;
  signal S: std_logic_vector(31 downto 0);
  signal COUT: std_logic;
begin
  adder: entity work.adder_32(behavior)
      port map (A, B, CIN, S, COUT);
  stimulus: process is
  begin
    loop
      A <= A + 1;
      B <= B + 2;
      CIN <= '0';
      wait for 5 ns;
      CIN <= '1';
      wait for 5 ns;
    end loop;
  end process stimulus;
end architecture test_adder_32;

architecture test_shift_32 of test_bench is
  signal D: std_logic_vector(31 downto 0) := B"00000000000000000000000000000011";
  signal SA: std_logic_vector(4 downto 0) := B"00000";
  signal Right: std_logic;
  signal Arith: std_logic;
  signal SH: std_logic_vector(31 downto 0);
begin
  shift: entity work.shift_32(behavioral)
      port map (D, SA, Right, Arith, SH);
  stimulus: process is
  begin
    loop
      D <= B"00000000000000000000000000000011" and D;
      Right <= '0';
      Arith <= '0';
      wait for 5 ns;
      Arith <= '1';
      wait for 5 ns;
      Right <= '1';
      Arith <= '0';
      wait for 5 ns;
      Arith <= '1';
      wait for 5 ns;
      D <= B"10000000000000000000000000000000" or D;
      Right <= '0';
      Arith <= '0';
      wait for 5 ns;
      Arith <= '1';
      wait for 5 ns;
      Right <= '1';
      Arith <= '0';
      wait for 5 ns;
      Arith <= '1';
      wait for 5 ns;

      SA <= SA + 1;
    end loop;
  end process stimulus;
end architecture test_shift_32;
