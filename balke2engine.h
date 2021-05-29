//
// Created by Puneet Rehal on 5/10/21.
//

#ifndef FINAL_BALKE2ENGINE_H
#define FINAL_BALKE2ENGINE_H

#include <iostream>
#include <limits>

namespace lbcrypto {
    class Blake2Engine {
    public:

        using result_type = uint32_t;

/**
  * @brief maximum value used by C+11 distribution generators when no upper
  * bound is explicitly specified by the user
  */
        static constexpr result_type max() {
            return std::numeric_limits<result_type>::max();
        }
    };
}
#endif //FINAL_BALKE2ENGINE_H
