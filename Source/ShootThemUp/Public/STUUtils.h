#pragma once


class STUUtils
{
public: 
	template<typename T>
	static T* GetSTUPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};