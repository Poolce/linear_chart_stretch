#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Buffer
{
protected:
    T *buf = nullptr;
    int n;

public:
    Buffer(int n) : n(n)
    {
        buf = new T[n];
    };
    Buffer(const Buffer<T> &tbd)
    {
        cout << "copy\n";
        buf = new T[tbd.n];
        for (int i = 0; i < tbd.n; i++)
        {
            buf[i] = tbd.buf[i];
        }
        n = tbd.n;
    }
    Buffer &operator=(const Buffer<T> &tbd)
    {
        cout << "copy\n";
        if (this = &tbd)
            return *this;
        buf = new T[tbd.n];
        for (int i = 0; i < tbd.n; i++)
        {
            buf[i] = tbd.buf[i];
        }
        return *this;
    }
    Buffer(Buffer<T> &&tbd) noexcept : buf(tbd.buf), n(tbd.n) { tbd.buf = nullptr; tbd.n = 0;};
    Buffer &operator=(Buffer<T> &&tbd) noexcept
    {
        cout << "copyjjjj";

        n = tbd.n;
        buf = tbd.buf;
        tbd.buf = nullptr;
        tbd.n = 0;
        return *this;
    };
    ~Buffer()
    {
        delete[] buf;
    };
    void out()
    {
        if (buf == nullptr)
        {
            cout << "uncorrect\n";
            return;
        }
        for (int i = 0; i < n; i++)
        {
            cout << " " << buf[i];
        }
        cout << endl;
    }
};

template <typename T>
class Buffer<T *>
{
protected:
    int n, m;
    T **buf = nullptr;
public:
    Buffer(int n = 0, int m = 0) : n(n), m(m)
    {
        cout << "const";
        buf = new T *[n];
        for (int i = 0; i < n; i++)
        {
            buf[i] = new T[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                buf[i][j] = rand() % 30 + 129;
            }
        }
    };
    Buffer(const Buffer<T *> &tbd)
    {
        cout << "copy";
        buf = new T *[tbd.n];
        for (int i = 0; i < tbd.n; i++)
            buf[i] = new T[tbd.m];

        for (int i = 0; i < tbd.n; i++)
        {
            for (int j = 0; j < tbd.m; j++)
            {
                buf[i][j] = tbd.buf[i][j];
            }
        }
        n = tbd.n;
        m = tbd.m;
    }
    Buffer &operator=(const Buffer<T *> &tbd)
    {
        cout << "copy=";
        buf = new T *[tbd.n];
        for (int i = 0; i < tbd.n; i++)
            buf[i] = new T[tbd.m];

        for (int i = 0; i < tbd.n; i++)
        {
            for (int j = 0; j < tbd.m; j++)
            {
                buf[i][j] = tbd.buf[i][j];
            }
        }
        n = tbd.n;
        m = tbd.m;
        return *this;
    }
    Buffer<T *> &operator=(Buffer<T *> &&tbd) noexcept
    {
        cout << "moverererere=";
        this->n = tbd.n;
        this->m = tbd.m;
        this->buf = tbd.buf;
        tbd.buf = nullptr;
        tbd.m = 0;
        tbd.n = 0;
        return *this;
    };
    Buffer<T *>(Buffer<T *> &&tbd) noexcept : buf(tbd.buf), n(tbd.n), m(tbd.m)
    {
        cout << "move";
        tbd.buf = nullptr;
        tbd.m = 0;
        tbd.n = 0;
    };
    ~Buffer<T *>()
    {
        for (int j = 0; j < n; j++)
            delete[] buf[j];
        delete[] buf;
    }
};

class pixelBuf:protected Buffer<int*>
{
protected:
    int leftColorLimit;
    int rightColorLimit;
public:
    pixelBuf(int n = 0, int m = 0):Buffer<int *>(n,m)
    {
        int min = 255, max = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (buf[i][j] < min)
                    min = buf[i][j];
                if (buf[i][j] > max)
                    max = buf[i][j];
            }
        }
        leftColorLimit = min;
        rightColorLimit = max;
    };
    void seqContrast()
    {
        if (leftColorLimit == rightColorLimit)
        {
            int col = (leftColorLimit >= 128) ? 255 : 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    buf[i][j] = col;
                }
            }
            return;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                buf[i][j] = (buf[i][j] - leftColorLimit) * 255 / (rightColorLimit - leftColorLimit);
            }
        }
    }
    void outBuf()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << buf[i][j] << " ";
            }
            cout << endl;
        }
    }
    int width(){
        return n;
    }
    int height(){
        return m;
    }
    void set(int i, int j, int val);
};
