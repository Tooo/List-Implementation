# List Implementation
Use this C list abstract data type to store any type set.
All functions are O(1) except for the first creation, free and search.

## Installation
1. Clone the repository
```bash
git clone https://github.com/Tooo/List-Implementation.git
```
2. Make the objects and executable file: 
```bash
make
```
3. Run the executable:
```bash
test
```

## Functions
| Function | Input | Output | Information |
| :------- | :---- | :----- | :---------- |
| List_create | N/A | List * | Make a new and empty list |
| List_count | List * | int | Return number of items in List |
| List_first | List * | void * | Return pointer to first item in List <br/> Make first item the current item | 
| List_last | List * | void * | Return pointer to last item in List <br/>  Make last item the current item |
| List_next | List * | void * | Advance List's current item by one <br/> Return new current item's pointer |
| List_prev | List * | void * | Back up List's current item by one <br/> Return new current item's pointer |
| List_curr | List * | void * | Return current item |
| List_add | List * <br/> void * | int | Add new item to List after current item <br/> Return 0 on sucess, Else -1 |
| List_insert | List * <br/> void * | int | Add new item to List before current item <br/> Return 0 on sucess, Else -1 |
| List_append | List * <br/> void * | int | Add new item to end of List <br/> Return 0 on sucess, Else -1 |
| List_prepend | List * <br/> void * | int | Add new item to front of List <br/> <br/> Return 0 on sucess, Else -1 |
| List_remove | List * | void * | Return and remove current item |
| List_concat | List * <br/> List * | N/A | Add List2 at end of List1 |
| List_free | List * <br/> Free Function | N/A | Delete list and free with Free Function |
| List_trim | List * | void * | Return and remove last item |
| List_search | List * <br/> Comparator Function <br/> void * | void * | Search through list starting from current item <br/> Compare with Comparator Function and Comparison item <br/> Return found item, Else NULL |

## Test
The test file [(test.c)](/test.c) is provided to prove the correctness of each function. 

## Configuration
The maximum amount of heads and nodes can be managed in [list.h](/list.h)

Maximum of heads is managed by: 
```c
LIST_MAX_NUM_HEADS 10
```
Maximum of nodes is managed by:
```c
LIST_MAX_NUM_NODES 100
```
