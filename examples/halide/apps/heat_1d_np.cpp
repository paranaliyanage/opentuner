#include <Halide.h>
using namespace Halide;

#define AUTOTUNE_HOOK(x)
#define BASELINE_HOOK(x)

int main(int argc, char **argv) {

	ImageParam input(Float(32), 2);
	Var x("x"), y("y");

	Func heat_1d_np("heat");
	RDom r(1, input.width() - 2, 1, input.height() - 1);

	heat_1d_np(x, y) = input(x, y);
	heat_1d_np(r.x, r.y) = 0.125f
			* (heat_1d_np(r.x - 1, r.y - 1) - 2.0f * heat_1d_np(r.x, r.y - 1)
					+ heat_1d_np(r.x + 1, r.y - 1));

	AUTOTUNE_HOOK(heat);
	heat_1d_np.compute_root();
	BASELINE_HOOK(heat);

	heat_1d_np.compile_to_file("heat_1d", input);

	return 0;
}
