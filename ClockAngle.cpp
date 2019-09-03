#include <iostream>

// Smaller angle formed by hour hand and minute hand of a clock
// QUESTION: https://www.techiedelight.com/angle-between-hour-minute-hand/
// Explanation in google doc

class AngleFinder
{
public:
	int get(int hour, int min)
	{
		int dhour = ((hour * 360) / 12) + ((min * 360) / (12*60));
		int dmin = (min * 360) / 60;
		int angle = std::abs(dmin - dhour);

		if (angle > 180)
			angle = 360 - angle;

		return angle;
	}
};

int main()
{
	AngleFinder obj;
	int result1 = obj.get(5, 30);
	int result2 = obj.get(9, 0);
	int result3 = obj.get(12, 0);
	std::cout << "Smaller angle at 5:30 is " << result1 << std::endl;
	std::cout << "Smaller angle at 9:00 is " << result2 << std::endl;
	std::cout << "Smaller angle at 12:00 is " << result3 << std::endl;
	return 0;
}