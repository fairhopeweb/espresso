#ifndef SCRIPT_INTERFACE_LOCAL_CONTEXT_HPP
#define SCRIPT_INTERFACE_LOCAL_CONTEXT_HPP

#include "Context.hpp"
#include "ObjectHandle.hpp"
#include "ObjectState.hpp"

#include <utils/Factory.hpp>

namespace ScriptInterface {
class LocalContext : public Context {
  Utils::Factory<ObjectHandle> m_factory;

public:
  explicit LocalContext(Utils::Factory<ObjectHandle> factory)
      : m_factory(std::move(factory)) {}

  void nofity_call_method(const ObjectHandle *, std::string const &,
                          VariantMap const &) override {}

  void notify_set_parameter(const ObjectHandle *, std::string const &,
                            Variant const &) override {}
  void nofity_delete_handle(const ObjectHandle *) override {}

  std::shared_ptr<ObjectHandle> make_shared(std::string const &name,
                                            const VariantMap &parameters) {
    auto sp = m_factory.make(name);
    set_manager(sp.get());
    set_name(sp.get(), m_factory.stable_name(name));

    sp->construct(parameters);

    return sp;
  }

  std::shared_ptr<ObjectHandle> deserialize(std::string const& state) {
    return deserialize_params([this](std::string const& name) {
      return make_shared(name, {});
    }, state);
  }

  std::string serialize(const ObjectHandle *o) {
    return serialize_params(o);
  }

  std::shared_ptr<ObjectHandle>
  make_shared(const ObjectHandle *, std::string const &name,
              const VariantMap &parameters) override {
    return make_shared(name, parameters);
  }
};
} // namespace ScriptInterface

#endif
