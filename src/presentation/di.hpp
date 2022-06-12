#pragma once

#include <di.hpp>
namespace di = boost::di;

#include "infrastructure/repo/groupRepo.hpp"
#include "infrastructure/repo/userRepo.hpp"

// based off of:
// https://github.com/boost-ext/di/issues/518#issuecomment-969463977

inline auto MakeDiInjector() {
	return di::make_injector(
		di::bind<IUserRepo>.to<UserRepo>(),
		di::bind<IGroupRepo>.to<GroupRepo>()
	);
}

using DiInjectorType = decltype(MakeDiInjector());

const DiInjectorType* GlobalInjector; // NOLINT

template <typename T>
auto DiCreate() -> decltype(GlobalInjector->template create<T>()) {
	return GlobalInjector->template create<T>();
}
