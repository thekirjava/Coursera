#include "sphere_projection.h"

namespace Sphere {

    Svg::Point Projector::operator()(Point point) const {
        return {
                long_idx.at(point.longitude) * x_step + padding_,
                height_ - padding_ - lat_idx.at(point.latitude) * y_step,
        };
    }

}
