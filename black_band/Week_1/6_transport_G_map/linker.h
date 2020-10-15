#pragma once

#include <memory>
#include "database.h"

namespace TransportDatabase {
    class Linker {
    public:
        Linker() {
            db_ = std::make_shared<Database>();
        }

        explicit Linker(std::shared_ptr<Database> base) {
            changeDatabase(base);
        }

        virtual void changeDatabase(std::shared_ptr<Database> base) {
            db_ = std::move(base);
        }

        virtual ~Linker() = default;

    protected:
        std::shared_ptr<Database> db_;
    };
}