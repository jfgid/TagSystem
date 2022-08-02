include_directories(../src)

# Generate sequence using range for the 3-tag system defined by E. Post
add_executable(genPostTagSeq
    ../src/prodRules.cpp
    genPostTagSeq.cpp)

set_property(TARGET genPostTagSeq PROPERTY CXX_STANDARD 20)