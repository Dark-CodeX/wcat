/**
 * @file out/out.hh
 * @author Tushar Chaurasia (Dark-CodeX)
 * @brief The header file is a part of https://github.com/Dark-CodeX/wcat.git, written for managing I/O.
 * @copyright Copyright (c) 2023 - Tushar Chaurasia
 * @license GNU General Public License v3.0
 */

#ifndef OUT_DEFINED
#define OUT_DEFINED

#include <openutils/sstring/sstring.hh>
#include <openutils/vector/vector.hh>
#include <sys/stat.h>

class out
{
  private:
    openutils::u8sstring content;
    openutils::vector_t<openutils::sstring> locations;
    std::size_t file_iterator;

  public:
    out(const char **argv)
    {
        if (!argv)
        {
            std::fprintf(stderr, "err: argv cannot be (null)\r\n");
            std::exit(EXIT_FAILURE);
        }
        while (*argv)
        {
            this->locations.add(*argv);
            argv++;
        }
        this->file_iterator = 0;
    }

    openutils::u8sstring &read_next()
    {
        this->content.clear();
        if (!this->content.open(this->locations[this->file_iterator]))
        {
            std::fprintf(stderr, "err: could not open file `%s`\r\n", this->locations[this->file_iterator].c_str());
            std::fflush(stdout);
            std::exit(EXIT_FAILURE);
        }
        this->file_iterator++;
        return this->content;
    }

    openutils::sstring &loc_N(const std::size_t &nth)
    {
        return this->locations[nth];
    }

    std::size_t length() const
    {
        return this->locations.length();
    }

    static inline bool is_file(const openutils::sstring &loc)
    {
        if (loc.is_null())
            return false;
        struct stat buffer = {};
        return (stat(loc.c_str(), &buffer) == 0);
    }

    // deleted functions and operators
    out() = delete;
    out(const out &o) = delete;
    out(out &&o) noexcept = delete;
    out &operator=(const out &o) = delete;
    out &operator=(out &&o) noexcept = delete;
    // deleted functions and operators

    ~out()
    {
        this->file_iterator = 0;
    }
};

#endif