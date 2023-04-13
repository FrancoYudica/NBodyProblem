#ifndef WOLF_TIME_H
#define WOLF_TIME_H

namespace Wolf
{

	struct Time
	{
		Time() = default;
		Time(double seconds) { _time = seconds; }
		double millis() const { return _time / 1000.0; }
		double seconds() const { return _time; }
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
		void Start() { _start = Time::current(); }
		Time Elapsed() { return Time::current() - _start; }

	private:
		Time _start;

	};

}
#endif
