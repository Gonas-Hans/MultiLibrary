# MultiDebug Library for Unreal Engine

🔥 Ultimate Blueprint Debugging Utility 🔥

**Reveal the hidden structure of your objects, structs, and arrays at runtime!**  
**Handcrafted for developers who want to see through the Blueprint veil.**

---

## 📜 Overview

**MultiDebug** is a powerful library plugin for Unreal Engine (C++ & Blueprints) that allows you to easily debug:

- Structs (`UStruct`)
- Objects (`UObject`, `Actor`, Interfaces)
- Arrays (`TArray`)
- Soft Object References (`TSoftObjectPtr`, `TSoftClassPtr`)
- Enums
- Nested structures

All through a single universal node without needing manual formatting!

---

## 🎯 Features

- 🧠 **Reflection-Based Parsing**  
  Walks through all properties of structs and objects, even nested ones.

- 🎨 **Custom Display Options**  
  Choose between `DisplayName` or `ObjectName`, custom colors, duration, and log types.

- 📚 **Supports Multiple Data Types**  
  Vectors, Rotators, Transforms, Enums, Soft References, Arrays, and more.

- 🧩 **Blueprint-Callable**  
  Integrated as a Blueprint Library with universal nodes (CustomThunk).

- 🚀 **Easy to Extend**  
  Future support planned for Maps (`TMap`) and Sets (`TSet`).

- 🛠 **Developer-Friendly**  
  Clean output formatting for fast reading and debugging.

---

## ⚡ How to Install

1. Add the MultiLibrary to your Unreal Engine C++ project in Plugins folder.
2. Regenerate Visual Studio project files.
3. Enjoy cleaner, faster debugging!

---

## 🛠️ Future Roadmap

- [ ] Support for `TMap` (Key-Value Pair Debugging)
- [ ] Support for `TSet` (Set Element Debugging)
- [ ] Refactoring for cleaner property resolution
- [ ] Dynamic Depth Limiting for Nested Structures
- [ ] Auto-Categorization in Blueprint Editor

---

## 📜 License

This project is licensed under the MIT License.

---