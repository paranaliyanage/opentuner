#include <Halide.h>
using namespace Halide;

#define AUTOTUNE_HOOK(x)
#define BASELINE_HOOK(x)

int main(int argc, char **argv) {

	ImageParam input(Float(32), 2);

	Var x("x"), y("y");
	Func heat_0("heat_0"), clamped_0("clamped_0"), heat_1("heat_1"), clamped_1(
			"clamped_1"), heat_2("heat_0"), clamped_2("clamped_0");
	clamped_0(x, y) = input(clamp(x, 1, input.width() -2), clamp(y, 1, input.height() -2));
	heat_0(x, y) = 0.125f
			* (clamped_0(x + 1, y) - 2.0f * clamped_0(x, y)
					+ clamped_0(x - 1, y))
			+ 0.125f
					* (clamped_0(x, y + 1) - 2.0f * clamped_0(x, y)
							+ clamped_0(x, y - 1)) + clamped_0(x, y);

	clamped_1(x, y) = heat_0(clamp(x, 1, input.width() -2), clamp(y, 1, input.height() -2));
	heat_1(x, y) = 0.125f
			* (clamped_1(x + 1, y) - 2.0f * clamped_1(x, y)
					+ clamped_1(x - 1, y))
			+ 0.125f
					* (clamped_1(x, y + 1) - 2.0f * clamped_1(x, y)
							+ clamped_1(x, y - 1)) + clamped_1(x, y);
	clamped_2(x, y) = heat_1(clamp(x, 1, input.width() -2), clamp(y, 1, input.height() -2));
	heat_2(x, y) = 0.125f
			* (clamped_2(x + 1, y) - 2.0f * clamped_2(x, y)
					+ clamped_2(x - 1, y))
			+ 0.125f
					* (clamped_2(x, y + 1) - 2.0f * clamped_2(x, y)
							+ clamped_2(x, y - 1)) + clamped_2(x, y);

	AUTOTUNE_HOOK(heat_2);
	heat_2.compute_root();
	BASELINE_HOOK(heat_2);

	heat_2.compile_to_file("heat_2d_np", input);
	return 0;
}
