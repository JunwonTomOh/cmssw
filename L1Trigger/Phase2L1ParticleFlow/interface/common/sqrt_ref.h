#ifndef L1Trigger_Phase2L1ParticleFlow_sqrt_ref_h
#define L1Trigger_Phase2L1ParticleFlow_sqrt_ref_h

#include "ap_fixed.h"
#include <cmath>

namespace l1ct {

  template <class out_t, class in_t>
  inline out_t sqrt_ref(const in_t& input) {
    // Round the square root to the in_t fractional precision.
    ap_ufixed<in_t::width, in_t::iwidth, AP_RND_ZERO> rounded = std::sqrt(input.to_double());

    // midpoint = rounded + 0.5 LSB.
    ap_ufixed<in_t::width + 1, in_t::iwidth> midpoint = rounded;
    midpoint[0] = 1;

    // Reproduce HLS sqrt rounding
    if (input > midpoint * midpoint)
      rounded.range(in_t::width - 1, 0) = rounded.range(in_t::width - 1, 0) + 1;
    return out_t(rounded);
  }

}  // namespace l1ct

#endif
