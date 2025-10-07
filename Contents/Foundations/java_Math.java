// 常量
static final double E, PI

// 絕對值/比較
static int/long/float/double abs(x)
static T max(a, b)
static T min(a, b)

// 取整/四捨五入
static double floor(double a)
static double ceil(double a)
static double rint(double a)                  // 最接近整數(偶數優先)
static long   round(double a) / int round(float a)
static int    floorDiv(int x, int y)
static int    floorMod(int x, int y)

// 溢位保護（exact 系列, Java 8+）
static int/long addExact(a, b)
static int/long subtractExact(a, b)
static int/long multiplyExact(a, b)
static int/long incrementExact(a)
static int/long decrementExact(a)
static int     toIntExact(long value)
static int/long negateExact(a)

// 指對數/冪根
static double pow(double a, double b)
static double sqrt(double a)
static double cbrt(double a)
static double exp(double a)
static double expm1(double x)
static double log(double a)
static double log10(double a)
static double log1p(double x)

// 三角/雙曲
static double sin/cos/tan(double a)
static double asin/acos/atan(double a)
static double atan2(double y, double x)
static double sinh/cosh/tanh(double a)

// 其他實用
static double hypot(double x, double y)
static double toDegrees(double angrad)
static double toRadians(double angdeg)
static double copySign(double magnitude, double sign)
static double nextUp/nextDown(double a)
static double nextAfter(double start, double direction)
static double ulp(double d)
static double random()
static double scalb(double d, int scaleFactor)
static double fma(double a, double b, double c)     // (since 8)
static long   multiplyHigh(long x, long y)          // (since 9)
static long   multiplyFull(int x, int y)            // (since 9, 回傳 long)