#pragma once

enum class OptionType
{
	Call,
	Put,
};

enum class BarrierType
{
	KnockIn,
	KnockOut,
}; 


enum class BarrierDirection
{
	Up,
	Down,
};