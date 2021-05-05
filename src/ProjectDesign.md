# Project Design

## Block Classes

### Transaction

Functions:

### Block
Private variables:

- `previousHash`
    - Type: `string`
    - Hash from the previous block
- `transaction`
    - Type: `list<Transaction>`
    - List of transactions contained in this block

Functions:

- Constructor
- getAmount
    - Returns the amount of currency in the transaction
- setAmount
    - Modifies the amount of currency in the transaction

### BlockChain

Functions:

### Base

# Things to Fix

## Blockchain.cpp/.h
- Difficulty
