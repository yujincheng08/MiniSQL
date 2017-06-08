# BufferManager

## Function

Try to implement a effective and smart buffer manager. 

## Usage

File is the main structure for programmer to use. It implemented the following interfaces, which are similar to iostream.

```C++
slots:
bool open(string fileName); //Open file. Return if the file is successfully opened.
void flush(); //Commit changing to disk. Without calling this function, changing will lost.
void reset(); //Reload file without saving it.
bool close(); //Free all buffer of the file after automatically calling flush().
signals:
size_type blockSize(); //return block size;
void opened(); //Emit after successfully opened.
void flushed(); //Emit after successfully flushed.
void closed(); //Emit after successfully  closed.
member functions:
File(string fileName); //Constructor
pos_type tellg(); //Return the reading cursor position.
pos_type tellp(); //Return the writing cursor position.
pos_type telle(); //Return the max cursor position: end position.
bool eof(); //If the reading touch the end of file.
bool seekg(pos_type pos); //Move the reading cursor to pos; Return false if pos is grater than file size.
bool seekp(pos_type pos); //Move the writing cursor to pos;
const T &get<T>(); //Get provided type reference.
const T &get<T>(pos_type pos); //Get provided type reference at pos, but not changing the cursor.
bool vaild<T>(); //If it's vaild to get the provided type.
const T &peek<T>(); //Get the provided type without moving the cursor.
void unget<T>(); //unget one provided type, which simply moves the cursor sizeof(T) before.
void put(const T&); //Put a charactor to the buffer. Notablly, data will be overwritten at the cursor instead of appending.
void put<T>(const T& pos_type pos); //Put a object data to the buff.
File &operator>>(T &target); //Equals to target = get<T>();
File &operator<<(const T &source); //Equals to put<T>(source);
```
## Example

```C++
//Only read something
class E
{
  int x;
  char y[28];
public:
  void plus(){x++;}
}
File f("db.db");
while(f.vaild<E>())
{
  const E &e = f.get<E>();
  cout<<e.x<<e.y<<endl;
  e.plus(); strcpy(e.y,"sss");
  f<<e;
}
```
## Attention

1. Adjust element size according to block size. Avoid to read one element but accessing two block.

2. Writing and reading only access raw data:

   ```C++
   T &source;
   memcpy((const char *)&T, buff + pos, sizeof(T));
   ```

   So it's better to specific your own `operator>>(File &, T)` and `operator<<(File &, T)`.

3. Both `get()`, `peek()` and `operator>>` get a constant reference of the target and have to write back to the buffer. It's useful if you only read the value. But writing seems costly. 

4. If get something exceed the end of file, the result will be undefined. So try to use `valid()` to determine.

5. Buffer overwrites data after cursor, not insert into cursor. If you are going to delete or inserting something, **use lazy deletion and free space link**.

6. `Pointer` seems dummy and has been eliminated.
