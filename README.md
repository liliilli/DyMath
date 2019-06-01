# DyMath
C++17 Math, Graphics Shape Library of Dy. This library can be used independently.

## Usage

This library is header-only library. Just add the path of include files into your project.

## Features

This math library suports below things.

- Fixed vector `DVector` types, `DVector2` `DVector3` `DVector4` with value types as template parameter.
- Fixed squared matrix `DMatrix` types `DVector2` `DVector3` `DVector4`,
  that only support real type (`TF32` as float, `TF64` as double.)
  - Matrix types are column-major type for compatibility `glsl` and `SPIR-V`.
  - DVector4<TI32> and DVector4<TF32> can use SIMD when enabling MATH_ENABLE_SIMD macro. This needs ~SSE4.1 support.
- 2D 3D Area type that has start point and width `x`, height `y` (and depth as `z` when using 3D area),
  `DArea2D` and `DArea3D`, with value types as template parameter.
- Plane type that has normal and d value, as $$ ax + by + cz + d = 0 $$ and $$ |(a, b, c)| == 1 $$, `DPlane`.
  That only support real type `TF32 ` and `TF64`.
- Clamping type that has compile time range `TStart` and `TEnd`, and supporting compile type. `DClamp`
- Quaternion
- Random value creation functions.
- UUID type (To use this, need to import static library file `DyMath.lib`.)
- and, miscellaneous helper math functions...

Implemented container type's arithmethic operators and functions are automatically proceeded by converting to more coverable type following value category description.

### Value Category

Dy(DianYing) Common Math (a.k.a `DyMath`) has value category to support automatic type conversion between two different types of same container type.

`DyMath` has below types and categories.

| Types  | Description                                          | Category  |
| ------ | ---------------------------------------------------- | --------- |
| TWchr  | Wide character type (16bit or 32bit dependent on OS) | Character |
| TChr8  | 8-bit character type                                 | Character |
| TChr16 | 16-bit character type                                | Character |
| TChr32 | 32-bit character type                                | Character |
| TI8    | 8-bit Signed integer type                            | Signed    |
| TI16   | 16-bit Signed integer type                           | Signed    |
| TI32   | 32-bit Signed integer type                           | Signed    |
| TI64   | 64-bit Signed integer type                           | Signed    |
| TU8    | 8-bit Unsigned integer type                          | Unsigned  |
| TU16   | 16-bit Unsignedinteger type                          | Unsigned  |
| TU32   | 32-bit Unsignedinteger type                          | Unsigned  |
| TU64   | 64-bit Unsignedinteger type                          | Unsigned  |
| TF32   | 32-bit Real type                                     | Real      |
| TF64   | 64-bit Real type                                     | Real      |

- Types in each category are automatically convertible to more-bit types of same category.
- Except for `Character` category, all of category types are convertible to `Real` category type.
- `Signed` and `Unsigned` category types are not convertible to each other because of value coverage.

## Installation (Library file)

`DyMath` can be used as header only library, except for `DUuid` that uses boost library internally. If you want to use `DUuid`, library file should be linked to your project.

* Make subdirectory `build`, and follow below sequences in terminal (powershell, etc).

``` bash
> cmake ..
> build . // If you want to build it as Debug mode
> build . --config Release // If you want to build it as Release mode
```

## Log

2019-03-30 Add Quaternion. Move Random function into DyMath<br>
2019-03-31 Add DBounds (AABB) 2D & 3D Type. Add `ExtractMin` `ExtractMax` math api for DVectors.<br>
2019-04-02 Add SIMD version of DVector4<TI32> and DVector4<TF32>.<br>
2019-04-19 Add UUID type for code reusability.<br>
2019-06-01 Seperate DyMath codes from DyUtil to independent library `DyMath`.<br>