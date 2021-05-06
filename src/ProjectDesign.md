# Project Design

## Block Classes

### Transaction
Included Libraties:
- Header
- Implementation

Namespace:
- `std`

Private Variables:

Functions:



### Block
Included Libraries:
- Header
  - `<cstdlib>`
  - `<iostream>`
  - `<string>`
  - `<vector>`
  - `<list>`
  - `<thread>`
  - `"sha256.h"`
  - `"transaction.h"`
  - `<ctime>`
  - `<sstream>"`
  - `<algorithm>`


- Implementation
  - `"block.h"`
  - `<cstdlib>`
  - `<iostream>`
  - `<string>`
  - `<vector>`
  - `"sha256.h"`
  - `"transaction.h"`
  - `<ctime>`
  - `<algorithm>`
  
Namespace:
- `std`

Private variables:

- `previousHash`
  - Type: `string`
  - Hash from the previous block
  - Default value:
    - `""`
- `transactions`
  - Type: `list<Transaction>`
  - List of transactions contained in this block
  - Default value:
    - empty `list` of class `Transaction`
- `diffPadding`
  - Type: `int`
  - Number of zeros after difficulty
  - Default value:
    - `0`
  - Access Locations:
    - `getDiffPadding()` returns the padding.
      - currently never called
  - Modifer Locations:
    - `setDiffPadding(int padding)` changes the padding to `padding`
      - current accessed at `base.cpp` line `131` using `BlockChain.getDiffPadding()` 
- `difficulty`
  - Type: `unsigned long long`
  - Difficulty for the blocks, could most likely be a `int` because of `diffPadding`
  - Default value:
    - `0`
- `timeFound`
  - Type: `time_t`
  - The time when the `Block` has been found
- `filler`
  - Type: `long`
  - The filler currently being used, or the final filler that finishes the block
- `found`
  - Type: `bool`
  - If the block has found a `filler` that finishes the block
- `hash`
  - Type: `string`
  - The final hash of the block
- `adjustmentFactor`
  - Type: `int`
  - Adjustment factor that will or had been used for difficulty adjustments, not in use right now.

Functions:

- `Block()`
  - Constructor
  - Parameters: `none`
  - Returns: `void`
 - `hex_greater(basic_string<char, char_traits<char>, allocator<char>> first, std::string &second)` 


- `getAmount()`
  - Returns the amount of currency in the transaction
- `setAmount()`
  - Modifies the amount of currency in the transaction

### BlockChain
Included libraries:
- Header
- Implementation
  - `"blockChain.h"`
  - `<iostream>`
  - `<string>`
  - `<vector>`
  - `"block.h"`
  - `"transaction.h"`
  - `<algorithm>`
  - `<sctime>`
  - `<fstream>`

Namespace:
- `std`

Private Variables:

Functions:


### Base
Included libraries:
- Implementation
  - if `_WIN32` `<windows.h>` else `unistd.h`
  - `<iostream>`
  - `<string>`
  - `<vector>`
  - `<thread>`
  - `"sha256.h"`
  - `"blockChain.h`
  - `"transaction.h"`
  - `"block.h"`


Namespace:
- `std`

Global Variables:

Functions:



# Things to Fix

## Blockchain.cpp/.h
- Dynamic difficulty
