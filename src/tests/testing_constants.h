/* Consts that are used across testing. For pricing tests, I want to ensure that 
pricing engines are within x ticks of expected price */


const double PENNY_TICK_SIZE = 0.01;   // for penny-pilot programs on options below $3.00
const double LISTED_TICK_SIZE = 0.05;  // for US-Listed options
const double MIN_TICK_SIZE = 0.01;