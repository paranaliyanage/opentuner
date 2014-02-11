#include <Halide.h>
using namespace Halide;

#define AUTOTUNE_HOOK(x)
#define BASELINE_HOOK(x)

int main(int argc, char **argv) {

	ImageParam input(Float(32), 3);
	Var x("x"), y("y"), z("z");

	Func heat("heat");
	RDom r(1, input.width() - 2, 1, input.height() - 2, 1,
			input.channels() - 1);

	heat(x, y, z) = input(x, y, z);

	heat(r.x, r.y, r.z) = 0.125f
			* (heat(r.x + 1, r.y, r.z - 1) - 2.0f * heat(r.x, r.y, r.z - 1)
					+ heat(r.x - 1, r.y, r.z - 1))
			+ 0.125f
					* (heat(r.x, r.y + 1, r.z - 1)
							- 2.0f * heat(r.x, r.y, r.z - 1)
							+ heat(r.x, r.y - 1, r.z - 1))
			+ heat(r.x, r.y, r.z - 1);

	AUTOTUNE_HOOK(heat);
	heat.compute_root();
	BASELINE_HOOK(heat);

	heat.compile_to_file("heat_2d_np", input);

	return 0;
}
