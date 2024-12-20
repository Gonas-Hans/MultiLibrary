//Copyright (c) 2024 Alexander Goncharov. All Rights Reserved.

#include "MultiLibraryBPLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UMultiLibraryBPLibrary::UMultiLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UMultiLibraryBPLibrary::PrintAll(const int& InputValue, const UObject* WorldContextObject, bool bViewSourceName, EObjectPrintableName ObjectPrintableName,
	 bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, const FName Key)
{
}

DEFINE_FUNCTION(UMultiLibraryBPLibrary::execPrintAll)
{
	// Steps into the stack, walking to the next property in it
	Stack.Step(Stack.Object, NULL);

	// Grab the last property found when we walked the stack
	// This does not contains the property value, only its type information
	FProperty* Property = CastField<FProperty>(Stack.MostRecentProperty);

	// Grab the base address where the struct actually stores its data
	// This is where the property value is truly stored
	void* PropertyPtr = Stack.MostRecentPropertyAddress;

	PARAM_PASSED_BY_VAL(WorldContextObject, FObjectProperty, UObject*)
	PARAM_PASSED_BY_VAL(bViewSourceName, FBoolProperty, bool)
	PARAM_PASSED_BY_VAL(ObjectPrintableName, FEnumProperty, EObjectPrintableName)
	PARAM_PASSED_BY_VAL(bPrintToScreen, FBoolProperty, bool)
	PARAM_PASSED_BY_VAL(bPrintToLog, FBoolProperty, bool)
	PARAM_PASSED_BY_VAL(TextColor, FStructProperty, FLinearColor)
	PARAM_PASSED_BY_VAL(Duration, FFloatProperty, float)
	PARAM_PASSED_BY_VAL(Key, FNameProperty, FName)
	
	// We need this to wrap up the stack
	P_FINISH;

	P_NATIVE_BEGIN;
	// Iterate through the struct
	ReceiveSomeProperty(Property, PropertyPtr, bViewSourceName, ObjectPrintableName, WorldContextObject,
		bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	P_NATIVE_END
}


void UMultiLibraryBPLibrary::ReceiveSomeProperty(FProperty* Property, void* PropertyPtr,
	bool bViewSourceName,EObjectPrintableName ObjectPrintableName, const UObject* WorldContextObject, bool bPrintToScreen,
	bool bPrintToLog, FLinearColor TextColor, float Duration, const FName Key)
{
	FString OutString;
	FString SourceName;
	// This is the property name if you need it (struct or single property)
	if (bViewSourceName)
	{
		SourceName =  FString::Printf(TEXT("%s: "), *Property->GetAuthoredName());
	}
	
	FStructProperty* StructProperty = CastField<FStructProperty>(Property);
	//Check for struct
	if (StructProperty)
	{
		//Check struct for FVector
		if (StructProperty->Struct == TBaseStructure<FVector>::Get())
		{
			if (PropertyPtr)
			{
				// Transform data into FVector
				FVector* Vector = static_cast<FVector*>(PropertyPtr);
				OutString = FString::Printf(TEXT("X=%s, Y=%s, Z=%s"),
					*FString::SanitizeFloat(Vector->X),
					*FString::SanitizeFloat(Vector->Y),
					*FString::SanitizeFloat(Vector->Z));
				if (!SourceName.IsEmpty())
				{
					OutString = SourceName.Append(OutString);
				}
				
				UKismetSystemLibrary::PrintString(WorldContextObject, OutString, bPrintToScreen, bPrintToLog, TextColor,
					Duration, Key);
			}
		}
		//Check struct for FRotator
		else if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
		{
			if (PropertyPtr)
			{
				// Transform data into FRotator
				FRotator* Rotator = static_cast<FRotator*>(PropertyPtr);
				OutString = FString::Printf(TEXT("R=%s, P=%s, Y=%s"),
					*FString::SanitizeFloat(Rotator->Roll),
					*FString::SanitizeFloat(Rotator->Pitch),
					*FString::SanitizeFloat(Rotator->Yaw));
				if (!SourceName.IsEmpty())
				{
					OutString = SourceName.Append(OutString);
				}
				UKismetSystemLibrary::PrintString(WorldContextObject, OutString, bPrintToScreen, bPrintToLog, TextColor,
					Duration, Key);
			}
		}
		//Check struct for FTransform
		else if (StructProperty->Struct == TBaseStructure<FTransform>::Get())
		{
			if (PropertyPtr)
			{
				// Transform data into FTransform
				FTransform* Transform = static_cast<FTransform*>(PropertyPtr);
				OutString = FString::Printf(TEXT("Loc: X=%s, Y=%s, Z=%s, Rot: R=%s, P=%s, Y=%s, Sca: X=%s, Y=%s, Z=%s"),
					*FString::SanitizeFloat(Transform->GetLocation().X),
					*FString::SanitizeFloat(Transform->GetLocation().Y),
					*FString::SanitizeFloat(Transform->GetLocation().Z),
					*FString::SanitizeFloat(Transform->GetRotation().Euler().X),
					*FString::SanitizeFloat(Transform->GetRotation().Euler().Y),
					*FString::SanitizeFloat(Transform->GetRotation().Euler().Z),
					*FString::SanitizeFloat(Transform->GetScale3D().X),
					*FString::SanitizeFloat(Transform->GetScale3D().Y),
					*FString::SanitizeFloat(Transform->GetScale3D().Z));
				if (!SourceName.IsEmpty())
				{
					OutString = SourceName.Append(OutString);
				}
				UKismetSystemLibrary::PrintString(WorldContextObject, OutString, bPrintToScreen, bPrintToLog, TextColor,
					Duration, Key);
			}
		}
		else
		{
			// Walk the structs' properties
			for (TFieldIterator<FProperty> PropertyIt(StructProperty->Struct); PropertyIt; ++PropertyIt)
			{
				FString VariableName = SourceName;
				// This is the struct variable name if you need it
				if (bViewSourceName)
            		{
						VariableName.Append(FString::Printf(TEXT("%s: "), *PropertyIt->GetAuthoredName()));
            		}
				// Never assume ArrayDim is always 1
				for (int32 ArrayIndex = 0; ArrayIndex < PropertyIt->ArrayDim; ArrayIndex++)
					{
						// This grabs the pointer to where the property value is stored
						void* ValuePtr = PropertyIt->ContainerPtrToValuePtr<void>(PropertyPtr, ArrayIndex);
            
						// Parse this property
					ParseProperty(*PropertyIt, ValuePtr, bViewSourceName, ObjectPrintableName, WorldContextObject,
						bPrintToScreen, bPrintToLog, TextColor, Duration, Key, VariableName);
					}
			}
		}
	}
	//If property not struct
	else
	{
		ParseProperty(Property, PropertyPtr, bViewSourceName, ObjectPrintableName, WorldContextObject,
			bPrintToScreen, bPrintToLog, TextColor, Duration, Key, SourceName);
	}
}

void UMultiLibraryBPLibrary::ParseProperty(FProperty* Property, void* ValuePtr, bool bViewSourceName,
	EObjectPrintableName ObjectPrintableName, const UObject* WorldContextObject, bool bPrintToScreen, bool bPrintToLog,
	FLinearColor TextColor, float Duration, const FName Key, FString SourceName)
{
	FString OutString;
	
	// Read booleans
	if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	{
		bool BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
		OutString = (BoolValue ? TEXT("true") : TEXT("false"));
	}

	//Read bytes and enums
	else if (FByteProperty* ByteProperty = CastField<FByteProperty>(Property))
	{
		uint8 ByteValue = ByteProperty->GetPropertyValue(ValuePtr);
		UEnum* EnumValue = ByteProperty->GetIntPropertyEnum();

		if (EnumValue)
		{
			OutString = EnumValue->GetDisplayNameTextByValue(ByteValue).ToString();
		}
		else
		{
			OutString = FString::Printf(TEXT("%d"), ByteValue);
		}
	}

	// Here's how to read integer and float properties
	else if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
	{
		if (NumericProperty->IsFloatingPoint())
		{
			float FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
			OutString = FString::SanitizeFloat(FloatValue);
		}
		else if (NumericProperty->IsInteger())
		{
			int32 IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
			OutString = FString::Printf(TEXT("%d"), IntValue);
		}
	}

	// Reading names
	else if (FNameProperty* NameProperty = CastField<FNameProperty>(Property))
	{
		FName NameValue = NameProperty->GetPropertyValue(ValuePtr);
		OutString = NameValue.ToString();
	}

	// Reading strings
	else if (FStrProperty* StringProperty = CastField<FStrProperty>(Property))
	{
		FString StringValue = StringProperty->GetPropertyValue(ValuePtr);
		OutString = StringValue;
	}

	// Reading texts
	else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
	{
		FText TextValue = TextProperty->GetPropertyValue(ValuePtr);
		OutString = TextValue.ToString();
	}

	//Reading objects
	else if(FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
	{
		UObject* ObjectValue = ObjectProperty->GetObjectPropertyValue(ValuePtr);
		switch (ObjectPrintableName)
		{
			case EObjectPrintableName::Display_Name:
				OutString = UKismetSystemLibrary::GetDisplayName(ObjectValue);
			break;
			
			case EObjectPrintableName::Object_Name:
				OutString = UKismetSystemLibrary::GetObjectName(ObjectValue);
			break;
			
			default:
				OutString = UKismetSystemLibrary::GetObjectName(ObjectValue);
		}
	}
	
	//Reading classes
	else if(FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
	{
		UClass* ClassValue = ClassProperty->MetaClass;
		OutString = UKismetSystemLibrary::GetClassDisplayName(ClassValue); 
	}

	//Reading soft objects
	else if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		UObject* SoftObjectValue = SoftObjectProperty->LoadObjectPropertyValue(ValuePtr);
		OutString = UKismetSystemLibrary::GetObjectName(SoftObjectValue);
	}

	//Reading soft classes
	else if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		UClass* SoftClassValue = SoftClassProperty->MetaClass;
		OutString = UKismetSystemLibrary::GetClassDisplayName(SoftClassValue); 
	}
	
	//Reading interfaces
	else if (FInterfaceProperty* InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		UClass* IntefaceValue = InterfaceProperty->InterfaceClass;
		OutString = UKismetSystemLibrary::GetClassDisplayName(IntefaceValue);
	}
		
	// Reading an array
	else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		// We need the helper to get to the items of the array       
		FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
		for (int32 i = 0, n = Helper.Num(); i < n; ++i)
		{
			ParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i), bViewSourceName, ObjectPrintableName, WorldContextObject,
				bPrintToScreen, bPrintToLog, TextColor, Duration, Key, SourceName);
		}
	}

	// Reading a nested struct
	else if (Property)
	{
		ReceiveSomeProperty(Property, ValuePtr, bViewSourceName, ObjectPrintableName, WorldContextObject,
			bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	
	//Check and print out string
	if (!OutString.IsEmpty())
	{
		if (!SourceName.IsEmpty())
		{
			OutString = SourceName.Append(OutString);
		}
		UKismetSystemLibrary::PrintString(WorldContextObject, OutString, bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

