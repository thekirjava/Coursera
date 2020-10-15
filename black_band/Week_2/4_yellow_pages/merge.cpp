#include "yellow_pages.h"

#include <algorithm>
#include <tuple>

namespace YellowPages {

    void
    MergeRepeated(Company &company, const google::protobuf::FieldDescriptor *fieldDescriptor, const Signals &signals,
                  const Providers &providers) {
        auto field = company.GetDescriptor()->FindFieldByName(fieldDescriptor->name());
        std::set<std::string> objects;
        int priority = 0;
        for (const auto &signal: signals) {
            const auto &provider = providers.at(signal.provider_id());
            const auto &signalCompany = signal.company();
            auto reflection = company.GetReflection();
            auto size = reflection->FieldSize(signalCompany, field);
            if (provider.priority() < priority) {
                break;
            }
            if (size == 0) {
                continue;
            }
            if (provider.priority() > priority) {
                priority = provider.priority();
                objects.clear();
            }
            for (size_t i = 0; i < size; i++) {
                objects.insert(reflection->GetRepeatedMessage(signalCompany, field, i).SerializeAsString());
            }
        }
        for (const auto &object:objects) {
            auto item = company.GetReflection()->AddMessage(&company, field);
            item->ParseFromString(object);
        }
    }

    void MergeSingle(Company &company, const google::protobuf::FieldDescriptor *fieldDescriptor, const Signals &signals,
                     const Providers &providers) {
        auto field = company.GetDescriptor()->FindFieldByName(fieldDescriptor->name());
        std::string object;
        for (const auto &signal:signals) {
            const auto &signalCompany = signal.company();
            auto reflection = company.GetReflection();
            if (reflection->HasField(signalCompany, field)) {
                object = reflection->GetMessage(signalCompany, field).SerializeAsString();
                break;
            }
        }
        if (!object.empty()) {
            auto item = company.GetReflection()->MutableMessage(&company, field);
            item->ParseFromString(object);
        }
    }

    Company Merge(const Signals &signals, const Providers &providers) {
        auto sorted_signals = signals;
        std::sort(begin(sorted_signals), end(sorted_signals), [&providers](const Signal &lhs, const Signal &rhs) {
            return providers.at(lhs.provider_id()).priority() > providers.at(rhs.provider_id()).priority();
        });
        Company company = Company();
        const auto *message_descriptor = company.GetDescriptor();
        for (size_t i = 0; i < message_descriptor->field_count(); i++) {
            const auto *current_field = message_descriptor->field(i);
            if (current_field->is_repeated()) {
                MergeRepeated(company, current_field, sorted_signals, providers);
            } else {
                MergeSingle(company, current_field, sorted_signals, providers);
            }
        }
        return company;
    }

}
