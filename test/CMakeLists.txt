include_directories(../src)

# Generate a sequence using range for the 3-tag system defined by E. Post
add_executable(genPostTagRange
    ../src/prodRules.cpp
    genPostTagRange.cpp)

set_property(TARGET genPostTagRange PROPERTY CXX_STANDARD 20)

# Generate a sequence with a handwritten loop for the 3-tag system defined by E. Post
add_executable(genPostTagLoop
    ../src/prodRules.cpp
    genPostTagLoop.cpp)