// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultiLibraryBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UENUM()
enum class EObjectPrintableName : uint8
{
	Display_Name	UMETA(DisplayName = "Display Name"),
	Object_Name		UMETA(DisplayName = "Object Name")
};

UCLASS()
class UMultiLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, CustomThunk,
		meta=(CustomStructureParam="InputValue", WorldContext="WorldContextObject",
			CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly),
		Category="Development")
	static void PrintAll(const int& InputValue, const UObject* WorldContextObject, bool bViewSourceName = false,
	                     EObjectPrintableName ObjectPrintableName = EObjectPrintableName::Display_Name,
	                     bool bPrintToScreen = true, bool bPrintToLog = true,
	                     FLinearColor TextColor = FLinearColor(0.0, 0.66, 1.0),
	                     float Duration = 2.f, const FName Key = NAME_None);
	DECLARE_FUNCTION(execPrintAll);
	
	/*
	* Example function for iterating through all properties of a struct
	* @param Property    The struct property reflection data
	* @param PropertyPtr        The pointer to the struct value
	*/
	static void ReceiveSomeProperty(FProperty* Property, void* PropertyPtr,
	                                bool bViewSourceName, EObjectPrintableName ObjectPrintableName,
	                                const UObject* WorldContextObject, bool bPrintToScreen, bool bPrintToLog,
	                                FLinearColor TextColor, float Duration, const FName Key);
	
	/* Example function for parsing a single property
	* @param Property    the property reflection data
	* @param ValuePtr    the pointer to the property value
	*/
	static void ParseProperty(FProperty* Property, void* ValuePtr,
	                          bool bViewSourceName, EObjectPrintableName ObjectPrintableName,
	                          const UObject* WorldContextObject, bool bPrintToScreen, bool bPrintToLog,
	                          FLinearColor TextColor, float Duration, const FName Key, FString SourceName);
};
