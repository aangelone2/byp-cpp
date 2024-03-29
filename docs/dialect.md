# Basic YAML {#BasicYAML}


## General specifications

- Basic YAML declarations should follow the `key: value` scheme.
- At least one space between `:` and the value is required.
- Spaces are not allowed in key names.
- Duplicate keys are not allowed.
- Commented lines should begin with `#`.
- Inline comments (e.g., `key: 3   # info`) are allowed.
  Anything following the first `#` will be ignored.

Any line not following the rules above is invalid, and will be
marked as such by the parser.

- All leading and trailing spaces for the keys and values will
  be discarded (e.g., `  key  :  abc  ` will be parsed as simply
  `abc` under the name `key`).


## Boolean values

`byp-cpp` allows to parse these values as the `bool` C++ type.

- Boolean values should be specified as `true` or `false`
  (lowercase).

    ```YAML
    # valid
    flag: true
    ```

## Integer values

`byp-cpp` allows to parse several C++ integral types (`short`,
`int`, `long` and `long long`).

- Integer values can be unsigned (`12`), explicitly positive
  (`+12`) or negative (`-12`) collections of digits.
- Floating-point values (i.e., relying on silent truncation)
  are not allowed.

    ```YAML
    # valid
    flag_1: 12

    # not valid
    flag_2: 12.0
    ```

- Spaces or other non-numerical characters are not allowed.


## Unsigned integer values

`byp-cpp` allows to parse several C++ unsigned integral types
(`unsigned short`, `unsigned int`, `unsigned long` and
`unsigned long long`).

The rules specified for integer types above hold, with the
following addendum:

- Unsigned integer values only allow unsigned values (i.e., no
  explicitly positive or negative values).


## Floating-point values

`byp-cpp` allows to parse several C++ floating-point types
(`float`, `double`, and `long double`).

Allowed values should have:
- An integral part, composed by an optional sign followed by
  *one or more* digits;
- An optional decimal part, composed by a decimal point `.`
  followed by *one or more* digits;
- An optional exponential part (in scientific notation), with
  the letter `e` or `E` followed by an optional sign and one or
  more digits.

```YAML
# valid (-> 12.0)
flt_1: 12
# valid
flt_2: 12.1
# valid
flt_3: 12e+4
# valid
flt_4: 12.0e08

# invalid
invalid_flt_1: 1.
# invalid
invalid_flt_2: 1.e+03
```


## String values

`byp-cpp` allows to parse these values as the `std::string` C++
type.

- Strings should be specified without quotes (quotes will be
  parsed as part of the string itself).
- Leading and trailing spaces will be removed as usual, but
  internal spaces will be kept.
- All hashes (`#`) will be interpreted as beginning a comment,
  with them and any character following them ignored.
- All colons (`:`) after the first in the line (separating key
  and value) will be normally parsed.
- If the string is not parsed as an element within a vector,
  commas (`,`) will be normally parsed.

  ```YAML
  # parsed as "abc def ghi" (outer spaces ignored)
  flag_1:    abc def ghi   

  # parsed as "\"abc def ghi   \""
  flag_2:   "abc def ghi   "

  # parsed as "abc"
  flag_3: abc#def

  # parsed as "a:b"
  flag_4: a:b

  # parsed as "abc,def"
  flag_5: abc,def
  ```


## Vectors

`byp-cpp` allows to parse these values as the `std::vector<T>`
C++ template type, where `T` can be any of the types above
(excluded `bool`).

- Vector elements should be specified within enclosing square
  brackets `[]`, and should be separated by commas.
- Square brackets are not allowed within the bounding ones,
  which may affect strings (for any other type it would be an
  error).
- Any amount of space is allowed within the vector definition
  in any position. Space inside strings will be parsed as per
  above; any other will be ignored.
- The value `[]` will generate an empty vector. No spaces are
  allowed between brackets in this case.
- Any valid value for the specified vector element type will be
  parsed as a component. Invalid values will raise an error.
- Vectors allow a trailing comma after the last component and
  before the vector is closed.
- When parsing `vector<string>`, commas will be interpreted as
  separators, and no longer parsed within the strings.

  ```YAML
  # valid as vector<int>
  flag_1: [1,2,3]

  # not valid (brackets not closed)
  flag_2: [1,2,3

  # not valid as vector<int> (invalid component)
  flag_3: [1, a, 3]

  # valid as vector<int>, spaces and trailing comma
  flag_4: [1 , 2, 3,]

  # vector<string>, parsed as {"abc", "def"}
  flag_5: [abc,def]
  ```


## 2D vectors (tables)

`byp-cpp` allows to parse these values as the
`std::vector<std::vector<T>>` C++ template type, where `T` can
be any of the types above (excluded `bool`).

- The overall table should be enclosed within square brackets
  `[]`.
- Each of the sub-vector elements should be a value parsable as
  `std::vector<T>` (see the rules above) and should be
  separated by comma by the others.
- Any amount of space is allowed within the table definition in
  any position. Space inside strings will be parsed as per
  above; any other will be ignored.
- Tables allow a trailing comma after the last component and
  before the table is closed.
- The value `[[]]` will generate an empty table. No spaces are
  allowed between brackets in this case.

  ```YAML
  # valid as vector<vector<int>>
  flag_1: [[1,2,3,], [4,5,6]]

  # valid as vector<vector<int>>, spaces and trailing comma
  flag_2: [[1,2,3] , [4  ,5 ,6],]
  ```
