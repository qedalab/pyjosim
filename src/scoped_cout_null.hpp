#include <iostream>

class null_buffer : public std::streambuf
{
  public:
    inline int overflow(int c)
    {
        return c;
    }
};

class scoped_cout_null
{
    null_buffer null_buffer_;
    std::streambuf *cache_;

  public:
    inline scoped_cout_null()
    {
        cache_ = std::cout.rdbuf();
        std::cout.rdbuf(std::addressof(null_buffer_));
    }

    inline ~scoped_cout_null()
    {
        std::cout.rdbuf(cache_);
    }
};
