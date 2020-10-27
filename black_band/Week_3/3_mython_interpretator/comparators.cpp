#include "comparators.h"
#include "object.h"
#include "object_holder.h"

#include <functional>
#include <optional>
#include <sstream>

using namespace std;

namespace Runtime {

bool Equal(ObjectHolder lhs, ObjectHolder rhs) {
    if ((lhs.TryAs<Class>()) && (rhs.TryAs<Class>())) {
        return lhs.TryAs<Class>()->GetName() ==
               rhs.TryAs<Class>()->GetName();
    }

    if ((lhs.TryAs<ClassInstance>()) && (rhs.TryAs<ClassInstance>())) {
        if (lhs.TryAs<ClassInstance>()->GetClassName() ==
            rhs.TryAs<ClassInstance>()->GetClassName()) {
            std::ostringstream one, two;
            lhs->Print(one);
            rhs->Print(two);

            return one.str() == two.str();
        }
        return false;
    }

    std::ostringstream one, two;
    lhs->Print(one);
    rhs->Print(two);
    return one.str() == two.str();
}

bool Less(ObjectHolder lhs, ObjectHolder rhs) {
    if ((lhs.TryAs<Number>()) && (rhs.TryAs<Number>())) {
        return lhs.TryAs<Number>()->GetValue() <
               rhs.TryAs<Number>()->GetValue();
    }

    if ((lhs.TryAs<String>()) && (rhs.TryAs<String>())) {
        return lhs.TryAs<String>()->GetValue() <
               rhs.TryAs<String>()->GetValue();
    }

    throw runtime_error("Bad Comparison!");
}

} /* namespace Runtime */
