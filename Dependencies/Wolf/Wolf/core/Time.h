#ifndef WOLF_TIME_H
#define WOLF_TIME_H

namespace Wolf
{

	struct Time
	{
		Time() = default;
		Time(double seconds) { _time = seconds; }
		inline double millis() const { return _time / 1000.0; }
		inline double seconds() const { return _time; }
		static Time current();

		Time operator -(const Time& other) { return Time(_time - other.seconds()); }
		Time operator +(const Time& other) { return Time(_time + other.seconds()); }

	private:
		double _time;
	};

	class Clock
	{
	public:
		Clock() = default;
		void start() { _start = Time::current(); }
		Time elapsed() { return Time::current() - _start; }

	private:
		Time _start;

	};

}
#endif
