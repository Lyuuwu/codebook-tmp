// 長度/容量
int  length()
int  capacity()
void ensureCapacity(int minimumCapacity)
void trimToSize()
void setLength(int newLength)

// 存取/修改
char          charAt(int index)
void          setCharAt(int index, char ch)
StringBuilder append(... 各種型別 ...)
StringBuilder insert(int offset, ... 各種型別 ...)
StringBuilder delete(int start, int end)
StringBuilder deleteCharAt(int index)
StringBuilder replace(int start, int end, String str)
StringBuilder reverse()

// 子字串/查找
String       substring(int start)
String       substring(int start, int end)
CharSequence subSequence(int start, int end)
int          indexOf(String str[, int fromIndex])
int          lastIndexOf(String str[, int fromIndex])

// 轉換
String toString()