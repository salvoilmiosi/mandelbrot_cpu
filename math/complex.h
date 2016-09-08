class complex_num {
public:
    double real;
    double imaginary;

public:
    complex_num() {
        real = 0.d;
        imaginary = 0.d;
    }

    complex_num(double r, double i) {
        real = r;
        imaginary = i;
    }

    complex_num(const complex_num& c) {
        real = c.real;
        imaginary = c.imaginary;
    }

    virtual ~complex_num() {}

public:
    static complex_num polar(double t, double m);

public:
    complex_num conjugate() const {
        return complex_num(real, -imaginary);
    }

    complex_num squared() const;

    double mod() const;

    double mod_squared() const;

    double theta() const;

public:
    complex_num &operator = (double r) {
        real = r;
        imaginary = 0.d;
        return *this;
    }

    complex_num &operator = (const complex_num &n) {
        real = n.real;
        imaginary = n.imaginary;
        return *this;
    }

    complex_num operator + (double r) const {
        return complex_num(real + r, imaginary);
    }

    complex_num &operator += (double r) {
        real += r;
        return *this;
    }

    complex_num operator + (const complex_num &n) const {
        return complex_num(real + n.real, imaginary + n.imaginary);
    }

    complex_num &operator += (const complex_num &n) {
        real += n.real;
        imaginary += n.imaginary;
        return *this;
    }

    complex_num operator - () const {
        return complex_num(-real, -imaginary);
    }

    complex_num operator - (double r) const {
        return complex_num(real - r, imaginary);
    }

    complex_num &operator -= (double r) {
        real -= r;
        return *this;
    }

    complex_num operator - (const complex_num &n) const {
        return complex_num(real - n.real, imaginary - n.imaginary);
    }

    complex_num &operator -= (const complex_num &n) {
        real -= n.real;
        imaginary -= n.imaginary;
        return *this;
    }

    complex_num operator * (double r) const {
        return complex_num(real * r, imaginary * r);
    }

    complex_num &operator *= (double r) {
        real *= r;
        imaginary *= r;
        return *this;
    }

    complex_num operator * (const complex_num &n) const {
        double r = real * n.real - imaginary * n.imaginary;
        double i = real * n.imaginary + n.real * imaginary;
        return complex_num(r, i);
    }

    complex_num &operator *= (const complex_num &n) {
        real = real * n.real - imaginary * n.imaginary;
        imaginary = real * n.imaginary + n.real * imaginary;
        return *this;
    }

    complex_num operator / (double r) const {
        return complex_num(real / r, imaginary / r);
    }

    complex_num &operator /= (double r) {
        real /= r;
        imaginary /= r;
        return *this;
    }

    complex_num operator / (const complex_num &n) const {
        double d = (n.real * n.real + n.imaginary * n.imaginary);
        double r = (real * n.real + imaginary * n.imaginary) / d;
        double i = (imaginary * n.real - real * n.imaginary) / d;
        return complex_num(r, i);
    }

    complex_num operator /= (const complex_num &n) {
        double d = (n.real * n.real + n.imaginary * n.imaginary);
        real = (real * n.real + imaginary * n.imaginary) / d;
        imaginary =(imaginary * n.real - real * n.imaginary) / d;
        return *this;
    }
};

const complex_num I_UNIT(0, 1);
