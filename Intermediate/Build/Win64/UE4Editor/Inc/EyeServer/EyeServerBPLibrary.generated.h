// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EYESERVER_EyeServerBPLibrary_generated_h
#error "EyeServerBPLibrary.generated.h already included, missing '#pragma once' in EyeServerBPLibrary.h"
#endif
#define EYESERVER_EyeServerBPLibrary_generated_h

#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_SPARSE_DATA
#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEyeServerSampleFunction) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Param); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=UEyeServerBPLibrary::EyeServerSampleFunction(Z_Param_Param); \
		P_NATIVE_END; \
	}


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEyeServerSampleFunction) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Param); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=UEyeServerBPLibrary::EyeServerSampleFunction(Z_Param_Param); \
		P_NATIVE_END; \
	}


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEyeServerBPLibrary(); \
	friend struct Z_Construct_UClass_UEyeServerBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UEyeServerBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/EyeServer"), NO_API) \
	DECLARE_SERIALIZER(UEyeServerBPLibrary)


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUEyeServerBPLibrary(); \
	friend struct Z_Construct_UClass_UEyeServerBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UEyeServerBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/EyeServer"), NO_API) \
	DECLARE_SERIALIZER(UEyeServerBPLibrary)


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEyeServerBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEyeServerBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEyeServerBPLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEyeServerBPLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEyeServerBPLibrary(UEyeServerBPLibrary&&); \
	NO_API UEyeServerBPLibrary(const UEyeServerBPLibrary&); \
public:


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEyeServerBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEyeServerBPLibrary(UEyeServerBPLibrary&&); \
	NO_API UEyeServerBPLibrary(const UEyeServerBPLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEyeServerBPLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEyeServerBPLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEyeServerBPLibrary)


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_PRIVATE_PROPERTY_OFFSET
#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_25_PROLOG
#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_PRIVATE_PROPERTY_OFFSET \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_SPARSE_DATA \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_RPC_WRAPPERS \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_INCLASS \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_PRIVATE_PROPERTY_OFFSET \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_SPARSE_DATA \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_INCLASS_NO_PURE_DECLS \
	DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h_28_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class EyeServerBPLibrary."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EYESERVER_API UClass* StaticClass<class UEyeServerBPLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DaqTest_Plugins_EyeServer_Source_EyeServer_Public_EyeServerBPLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
