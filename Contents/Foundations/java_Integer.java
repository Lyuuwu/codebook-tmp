// 常量
MAX_VALUE, MIN_VALUE, BYTES, SIZE, TYPE

// 轉換/解析
static int    parseInt(String s)
static int    parseInt(String s, int radix)
static int    parseUnsignedInt(String s)
static int    parseUnsignedInt(String s, int radix)
static Integer valueOf(int i)
static Integer valueOf(String s)
static Integer valueOf(String s, int radix)
static String  toString(int i)
static String  toString(int i, int radix)
static String  toUnsignedString(int i)
static String  toUnsignedString(int i, int radix)
static long    toUnsignedLong(int x)
static Integer decode(String nm)                    // 支援 0x/0/# 前綴
static Integer getInteger(String nm[, int val])     // 從系統屬性讀取整數

// 比較/雜湊/聚合
static int compare(int x, int y)
static int compareUnsigned(int x, int y)
static int hashCode(int value)
static int min(int a, int b)
static int max(int a, int b)
static int sum(int a, int b)

// 位元操作
static int bitCount(int i)      // 設定位數
static int highestOneBit(int i)
static int lowestOneBit(int i)
static int numberOfLeadingZeros(int i)
static int numberOfTrailingZeros(int i)
static int rotateLeft(int i, int distance)
static int rotateRight(int i, int distance)
static int reverse(int i)
static int reverseBytes(int i)

// 無號運算
static int divideUnsigned(int dividend, int divisor)
static int remainderUnsigned(int dividend, int divisor)