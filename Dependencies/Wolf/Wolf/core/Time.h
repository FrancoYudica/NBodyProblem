#ifndef WOLF_TIME_H
#define WOLF_TIME_H
#include <iostream>
#include <functional>
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
		friend std::ostream& operator << (std::ostream& stream, const Time& time);

	private:
		double _time;
	};

	class Clock
	{
	public:
		Clock() = default;
		void start() { _start = Time::current(); }
		Time elapsed() const { return Time::current() - _start; }

	private:
		Time _start;

	};

	class ScopeTimer
	{
		typedef std::function<void(Time)> ScopeTimerCallback;
		public:
			ScopeTimer(const ScopeTimerCallback& callback) : _callback(callback), _start(Time::current()){}
			~ScopeTimer() {_callback(Time::current() - _start); }
		private:
			Time _start;
			ScopeTimerCallback _callback;

	};

}
#endif
