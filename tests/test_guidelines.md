# Unit Tests

## Testing Guidelines
* Test one function per test case
* Template all test cases on `VALID_TYPES`
* Name the test case according to what's being exercised
* Within the test case, define `constexpr TestArray` values for test inputs and expected outputs
    * Generally provide 4D inputs, unless the function under test doesn't exist for 4D vectors
    * Specify literals as `long double` by appending `L` as a literal suffix.
* Where appropriate, define `SUBCASE()` sections for 2D, 3D, and 4D vectors
    * Perform all test operations and assertions within a `SUBCASE()`
    * Utilize `getVec<Type, M>()` helper to get appropriately-sized vectors from `TestArray` values
* Exercise all operations in fully `constexpr` manner wherever possible
    * If the compile-time implementation of the function under test differs from the run-time 
      implementation (i.e. the function uses `std::is_constant_evaluated()`), test the function 
      in both a `constexpr` and non-`constexpr` context.
      
## Test Case Example
```C++
TEST_CASE_TEMPLATE("Vector-vector addition", Type, VALID_TYPES) {
   constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
   constexpr TestArray kExpected{2.0L, 4.0L, 6.0L, 8.0L};
   
   SUBCASE("2D") {
       constexpr auto v = getVec<Type, 2>(kInput);
       constexpr auto out = v + v;
       CHECK(out == getVec<Type, 2>(kExpected));
   }
   
   SUBCASE("3D") {
     constexpr auto v = getVec<Type, 3>(kInput);
     constexpr auto out = v + v;
     CHECK(out == getVec<Type, 3>(kExpected));
   }

   SUBCASE("4D") {
       constexpr auto v = getVec<Type, 4>(kInput);
       constexpr auto out = v + v;
       CHECK(out == getVec<Type, 4>(kExpected));
   }
}
```
