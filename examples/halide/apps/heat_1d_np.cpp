#include <Halide.h>
using namespace Halide;

#define AUTOTUNE_HOOK(x)
#define BASELINE_HOOK(x)

int main(int argc, char **argv) {

	ImageParam input(Float(32), 1);

	Var x("x");
	Func heat_0("heat_0"), clamped_0("clamped_0"), heat_1("heat_1"), clamped_1(
			"clamped_1"), heat_2("heat_0"), clamped_2("clamped_0");
	clamped_0(x) = input(clamp(x, 1, input.width() -2));
	heat_0(x) = 0.125f
			* (clamped_0(x - 1) - 2.0f * clamped_0(x) + clamped_0(x + 1));
	clamped_1(x) = heat_0(clamp(x, 1, input.width() -2));
	heat_1(x) = 0.125f
			* (clamped_1(x - 1) - 2.0f * clamped_1(x) + clamped_1(x + 1));
	clamped_2(x) = heat_1(clamp(x, 1, input.width() -2));
	heat_2(x) = 0.125f
			* (clamped_2(x - 1) - 2.0f * clamped_2(x) + clamped_2(x + 1));

	AUTOTUNE_HOOK(heat_2);
	heat_2.compute_root();
	BASELINE_HOOK(heat_2);

	heat_2.compile_to_file("heat_1d_np", input);
	return 0;
}
