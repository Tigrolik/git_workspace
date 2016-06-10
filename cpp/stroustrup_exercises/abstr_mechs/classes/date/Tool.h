#ifndef TOOL_H
#define TOOL_H

class Tool {
public:
    constexpr Tool() { }
    constexpr Tool(const int s, const char t): s_{s}, t_{t} { }

    // default copy and move ctors
    constexpr Tool(const Tool&) = default;
    constexpr Tool(Tool&&) = default;

    // default copy and move assignments
    Tool& operator=(const Tool&) = default;
    Tool& operator=(Tool&&) = default;

    // default dtor
    ~Tool() = default;

    constexpr int strength() const { return s_; }
    constexpr char type() const { return t_; }

private:
    int s_ {0};  // strength
    char t_ {'0'}; // type
};

#endif /* end of include guard: TOOL_H */
