LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY counter_4 IS
  PORT (CLK:IN STD_LOGIC;
    CQ:OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END counter_4;
ARCHITECTURE behavior OF counter_4 IS
BEGIN
  PROCESS(CLK)
    VARIABLE CQI:STD_LOGIC_VECTOR(3 DOWNTO 0) := B"0000";
  BEGIN
    IF CLK'EVENT AND CLK='1' THEN
      CQI := CQI + 1;
    END IF;
    CQ<=CQI;
  END PROCESS;
END behavior;
