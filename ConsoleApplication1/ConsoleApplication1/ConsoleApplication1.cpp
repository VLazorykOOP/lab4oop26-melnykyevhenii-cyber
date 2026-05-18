#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

// ========================= ZAVDANNYa 1.2 =========================
// Klas VectorFloat

class VectorFloat {
private:
    float* data;
    int size;
    int codeError;
    static int objectCount;

    void setError(int error) {
        codeError = error;
    }

public:
    // Konstruktory
    VectorFloat() : size(1), codeError(0) {
        data = new float[1];
        data[0] = 0;
        objectCount++;
    }

    VectorFloat(int s) : size(s), codeError(0) {
        if (s <= 0) {
            size = 1;
            setError(1);
        }
        data = new float[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
        objectCount++;
    }

    VectorFloat(int s, float initVal) : size(s), codeError(0) {
        if (s <= 0) {
            size = 1;
            setError(1);
        }
        data = new float[size];
        for (int i = 0; i < size; i++)
            data[i] = initVal;
        objectCount++;
    }

    VectorFloat(const VectorFloat& other) : size(other.size), codeError(other.codeError) {
        data = new float[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        objectCount++;
    }

    ~VectorFloat() {
        delete[] data;
        objectCount--;
    }

    // Funktsiyi dostupu
    int getSize() const { return size; }
    int getError() const { return codeError; }
    static int getObjectCount() { return objectCount; }
    void clearError() { codeError = 0; }

    // Unarni prefiksni ++ ta --
    VectorFloat& operator++() {
        for (int i = 0; i < size; i++)
            data[i] += 1.0f;
        return *this;
    }

    VectorFloat& operator--() {
        for (int i = 0; i < size; i++)
            data[i] -= 1.0f;
        return *this;
    }

    // Unarni postfiksni ++ ta --
    VectorFloat operator++(int) {
        VectorFloat temp = *this;
        ++(*this);
        return temp;
    }

    VectorFloat operator--(int) {
        VectorFloat temp = *this;
        --(*this);
        return temp;
    }

    // Unarna lohichna !
    bool operator!() const {
        return size != 0;
    }

    // Unarnyj aryfmetychnyj -
    VectorFloat operator-() const {
        VectorFloat result(size);
        for (int i = 0; i < size; i++)
            result.data[i] = -data[i];
        return result;
    }

    // Prysvoyennya =
    VectorFloat& operator=(const VectorFloat& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            codeError = other.codeError;
            data = new float[size];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Prysvoyennya +=
    VectorFloat& operator+=(const VectorFloat& other) {
        if (size != other.size) {
            setError(2);
            return *this;
        }
        for (int i = 0; i < size; i++)
            data[i] += other.data[i];
        return *this;
    }

    // Prysvoyennya -=
    VectorFloat& operator-=(const VectorFloat& other) {
        if (size != other.size) {
            setError(2);
            return *this;
        }
        for (int i = 0; i < size; i++)
            data[i] -= other.data[i];
        return *this;
    }

    // Prysvoyennya *=
    VectorFloat& operator*=(float scalar) {
        for (int i = 0; i < size; i++)
            data[i] *= scalar;
        return *this;
    }

    // Prysvoyennya /=
    VectorFloat& operator/=(float scalar) {
        if (scalar == 0) {
            setError(3);
            return *this;
        }
        for (int i = 0; i < size; i++)
            data[i] /= scalar;
        return *this;
    }

    // Prysvoyennya %=
    VectorFloat& operator%=(int scalar) {
        if (scalar == 0) {
            setError(3);
            return *this;
        }
        for (int i = 0; i < size; i++)
            data[i] = fmod(data[i], scalar);
        return *this;
    }

    // Binarni aryfmetychni operatsiyi
    VectorFloat operator+(const VectorFloat& other) const {
        VectorFloat result(size);
        if (size != other.size) {
            result.setError(2);
            return result;
        }
        for (int i = 0; i < size; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    VectorFloat operator-(const VectorFloat& other) const {
        VectorFloat result(size);
        if (size != other.size) {
            result.setError(2);
            return result;
        }
        for (int i = 0; i < size; i++)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    VectorFloat operator*(float scalar) const {
        VectorFloat result(size);
        for (int i = 0; i < size; i++)
            result.data[i] = data[i] * scalar;
        return result;
    }

    VectorFloat operator/(float scalar) const {
        VectorFloat result(size);
        if (scalar == 0) {
            result.setError(3);
            return result;
        }
        for (int i = 0; i < size; i++)
            result.data[i] = data[i] / scalar;
        return result;
    }

    VectorFloat operator%(int scalar) const {
        VectorFloat result(size);
        if (scalar == 0) {
            result.setError(3);
            return result;
        }
        for (int i = 0; i < size; i++)
            result.data[i] = fmod(data[i], scalar);
        return result;
    }

    // Operatsiyi porivnyannya
    bool operator==(const VectorFloat& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorFloat& other) const {
        return !(*this == other);
    }

    bool operator>(const VectorFloat& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] <= other.data[i]) return false;
        return true;
    }

    bool operator>=(const VectorFloat& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] < other.data[i]) return false;
        return true;
    }

    bool operator<(const VectorFloat& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] >= other.data[i]) return false;
        return true;
    }

    bool operator<=(const VectorFloat& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] > other.data[i]) return false;
        return true;
    }

    // Operatsiya indeksatsiyi []
    float& operator[](int index) {
        if (index < 0 || index >= size) {
            setError(4);
            return data[size - 1];
        }
        return data[index];
    }

    const float& operator[](int index) const {
        if (index < 0 || index >= size) {
            const_cast<VectorFloat*>(this)->setError(4);
            return data[size - 1];
        }
        return data[index];
    }

    // Operator vyklyku funktsiyi ()
    float operator()(int index) const {
        if (index < 0 || index >= size) {
            return 0;
        }
        return data[index];
    }

    // Druzhni operatory vvedennya/vyvedennya
    friend istream& operator>>(istream& is, VectorFloat& v);
    friend ostream& operator<<(ostream& os, const VectorFloat& v);

    // Operatory new/delete
    void* operator new(size_t size) {
        void* ptr = malloc(size);
        if (!ptr) throw bad_alloc();
        return ptr;
    }

    void operator delete(void* ptr) {
        free(ptr);
    }
};

int VectorFloat::objectCount = 0;

istream& operator>>(istream& is, VectorFloat& v) {
    cout << "Vvedit " << v.size << " elementiv: ";
    for (int i = 0; i < v.size; i++)
        is >> v.data[i];
    return is;
}

ostream& operator<<(ostream& os, const VectorFloat& v) {
    os << "[";
    for (int i = 0; i < v.size; i++) {
        os << v.data[i];
        if (i < v.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

// ========================= ZAVDANNYa 2.2 =========================
// Asotsiatyvnyj masyv: krayina -> stolytsya

class CountryCapitalMap {
private:
    string* countries;
    string* capitals;
    int capacity;
    int count;
    int codeError;

    int findCountry(const string& country) const {
        for (int i = 0; i < count; i++)
            if (countries[i] == country)
                return i;
        return -1;
    }

public:
    CountryCapitalMap(int cap = 100) : capacity(cap), count(0), codeError(0) {
        countries = new string[capacity];
        capitals = new string[capacity];
    }

    ~CountryCapitalMap() {
        delete[] countries;
        delete[] capitals;
    }

    void add(const string& country, const string& capital) {
        if (count >= capacity) {
            codeError = 1;
            return;
        }
        int idx = findCountry(country);
        if (idx != -1) {
            capitals[idx] = capital;
        }
        else {
            countries[count] = country;
            capitals[count] = capital;
            count++;
        }
    }

    // Operator [] za krayinoyu (poverataye stolytsyu)
    string operator[](const string& country) {
        int idx = findCountry(country);
        if (idx == -1) {
            codeError = 2;
            return "ERROR: Not found";
        }
        return capitals[idx];
    }

    // Operator () - alternatyvnyj dostup
    string operator()(const string& country) {
        return (*this)[country];
    }

    void remove(const string& country) {
        int idx = findCountry(country);
        if (idx == -1) {
            codeError = 2;
            return;
        }
        for (int i = idx; i < count - 1; i++) {
            countries[i] = countries[i + 1];
            capitals[i] = capitals[i + 1];
        }
        count--;
    }

    bool contains(const string& country) const {
        return findCountry(country) != -1;
    }

    int getCount() const { return count; }
    int getError() const { return codeError; }
    void clearError() { codeError = 0; }

    void displayAll() const {
        cout << "\n=== KRAYINY TA STOLYTSI ===\n";
        for (int i = 0; i < count; i++) {
            cout << countries[i] << " -> " << capitals[i] << endl;
        }
        cout << "============================\n";
    }

    // Druzhni operatory vvedennya/vyvedennya
    friend istream& operator>>(istream& is, CountryCapitalMap& m);
    friend ostream& operator<<(ostream& os, const CountryCapitalMap& m);
};

istream& operator>>(istream& is, CountryCapitalMap& m) {
    string country, capital;
    cout << "Vvedit krayinu ta stolytsyu: ";
    is >> country >> capital;
    m.add(country, capital);
    return is;
}

ostream& operator<<(ostream& os, const CountryCapitalMap& m) {
    for (int i = 0; i < m.count; i++) {
        os << m.countries[i] << " -> " << m.capitals[i] << endl;
    }
    return os;
}

// ========================= TESTOVI FUNKTSIYi =========================

void testVectorFloat() {
    cout << "\n========== TESTUVANNYa VectorFloat ==========\n\n";

    cout << "1. Konstruktory:\n";
    VectorFloat v1;
    VectorFloat v2(5);
    VectorFloat v3(4, 3.14f);

    cout << "   v1: " << v1 << endl;
    cout << "   v2: " << v2 << endl;
    cout << "   v3: " << v3 << endl;
    cout << "   Kilkist ob'yektiv: " << VectorFloat::getObjectCount() << endl;

    cout << "\n2. Vvedennya z klaviatury:\n";
    VectorFloat v4(3);
    cin >> v4;
    cout << "   Vvedenyj vektor: " << v4 << endl;

    cout << "\n3. Unarni operatsiyi:\n";
    VectorFloat v5(3, 1.0f);
    cout << "   Pochatkovyj: " << v5 << endl;
    cout << "   Prefiksnyj ++: " << ++v5 << endl;
    cout << "   Postfiksnyj --: " << v5-- << " (pislya: " << v5 << ")" << endl;
    cout << "   Unarnyj minus: " << -v5 << endl;
    cout << "   Lohichne !: " << (!v5 ? "true" : "false") << endl;

    cout << "\n4. Aryfmetychni operatsiyi:\n";
    VectorFloat a(3, 5.0f);
    VectorFloat b(3, 3.0f);
    cout << "   a = " << a << ", b = " << b << endl;
    cout << "   a + b = " << a + b << endl;
    cout << "   a - b = " << a - b << endl;
    cout << "   a * 2 = " << a * 2 << endl;
    cout << "   a / 2 = " << a / 2 << endl;

    cout << "\n5. Operatsiyi prysvoyennya:\n";
    VectorFloat c(3, 2.0f);
    VectorFloat d(3, 1.0f);
    c += d;
    cout << "   c += d: " << c << endl;
    c *= 2;
    cout << "   c *= 2: " << c << endl;

    cout << "\n6. Operator indeksatsiyi []:\n";
    VectorFloat e(3, 10.0f);
    cout << "   e = " << e << endl;
    cout << "   e[0] = " << e[0] << endl;
    e[1] = 99;
    cout << "   Pislya e[1] = 99: " << e << endl;
    cout << "   e[10] (pomylkovyj indeks): " << e[10] << " (kod pomylky: " << e.getError() << ")" << endl;

    cout << "\n7. Operator vyklyku ():\n";
    cout << "   e(0) = " << e(0) << ", e(1) = " << e(1) << ", e(2) = " << e(2) << endl;

    cout << "\n8. Operatsiyi porivnyannya:\n";
    VectorFloat f(3, 5.0f);
    VectorFloat g(3, 5.0f);
    VectorFloat h(3, 3.0f);
    cout << "   f = " << f << ", g = " << g << ", h = " << h << endl;
    cout << "   f == g: " << (f == g ? "true" : "false") << endl;
    cout << "   f != h: " << (f != h ? "true" : "false") << endl;
    cout << "   f > h: " << (f > h ? "true" : "false") << endl;

    cout << "\n9. Skladnyj vyraz (5+ operatsij):\n";
    VectorFloat x(3, 2.0f);
    VectorFloat y(3, 4.0f);
    VectorFloat z(3, 1.0f);
    cout << "   x = " << x << ", y = " << y << ", z = " << z << endl;
    VectorFloat result = (x * 3 + y) - z * 2;
    cout << "   (x * 3 + y) - z * 2 = " << result << endl;
    VectorFloat result2 = (x + y) * 2 - (z * 3) + x / 2;
    cout << "   (x + y) * 2 - (z * 3) + x / 2 = " << result2 << endl;

    cout << "\n10. Vypadkovyj vektor:\n";
    VectorFloat random(5);
    srand(time(nullptr));
    for (int i = 0; i < random.getSize(); i++) {
        random[i] = (float)(rand() % 100) / 10.0f;
    }
    cout << "    Vypadkovyj vektor: " << random << endl;

    cout << "\n========== ZAVERSHENNYa TESTU ==========\n";
}

void testCountryCapitalMap() {
    cout << "\n========== TESTUVANNYa CountryCapitalMap ==========\n\n";

    CountryCapitalMap map;

    map.add("Ukraine", "Kyiv");
    map.add("USA", "Washington");
    map.add("France", "Paris");
    map.add("Germany", "Berlin");
    map.add("Italy", "Rome");
    map.add("Japan", "Tokyo");

    map.displayAll();

    cout << "\n2. Operator []:\n";
    cout << "   Stolytsya Ukrayiny: " << map["Ukraine"] << endl;
    cout << "   Stolytsya Frantsiyi: " << map["France"] << endl;
    cout << "   Neisnuyucha krayina: " << map["XYZ"] << " (kod pomylky: " << map.getError() << ")" << endl;
    map.clearError();

    cout << "\n3. Operator () :\n";
    cout << "   map(\"Germany\") = " << map("Germany") << endl;

    cout << "\n4. Perevirka nayavnosti:\n";
    cout << "   Mistyt Ukraine? " << (map.contains("Ukraine") ? "Tak" : "Ni") << endl;
    cout << "   Mistyt Brazil? " << (map.contains("Brazil") ? "Tak" : "Ni") << endl;

    cout << "\n5. Vydalennya:\n";
    map.remove("Italy");
    cout << "   Pislya vydalennya Italy:\n";
    map.displayAll();

    cout << "\n6. Operator << :\n";
    cout << map;

    cout << "\n7. Vvedennya novoyi krayiny (format: krayina stolytsya):\n";
    cin >> map;
    cout << "\n   Onovlenyj spysok:\n";
    map.displayAll();

    cout << "\n========== ZAVERSHENNYa TESTU ==========\n";
}

// ========================= HOLOVNE MENU =========================

void showMenu() {
    cout << "\n========================================\n";
    cout << "        LABORATORNA ROBOTA No4\n";
    cout << "            VARIANT 2\n";
    cout << "========================================\n";
    cout << "1. Testuvannya VectorFloat (Zavdannya 1.2)\n";
    cout << "2. Testuvannya CountryCapitalMap (Zavdannya 2.2)\n";
    cout << "3. Testuvannya obokh zavdan\n";
    cout << "0. Vyhid\n";
    cout << "----------------------------------------\n";
    cout << "Vash vybir: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            testVectorFloat();
            break;
        case 2:
            testCountryCapitalMap();
            break;
        case 3:
            testVectorFloat();
            testCountryCapitalMap();
            break;
        case 0:
            cout << "Do pobachennya!\n";
            break;
        default:
            cout << "Nevirnyj vybir. Sprobujte shche raz.\n";
        }
    } while (choice != 0);

    return 0;
}