# Project Design

## Block Classes

### Transaction

Functions:

### Block
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
      - current accessed at `x` 
- `difficulty`
  - Type: `unsigned long long`
  - Difficulty for the blocks, could most likely be a `int` because of `diffPadding`
  - Default value:
    - `0`


Functions:

- `Block()`
  - Constructor
  - Parameters: `none`
  - Returns: `void`
  


- `getAmount()`
  - Returns the amount of currency in the transaction
- `setAmount()`
  - Modifies the amount of currency in the transaction

### BlockChain

Functions:

### Base

# Things to Fix

## Blockchain.cpp/.h
- Difficulty
