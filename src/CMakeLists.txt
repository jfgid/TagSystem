# Implementation using an infinite range
add_executable(genTagSequence
    prodRules.cpp
    genTagSequence.cpp)

set_property(TARGET genTagSequence PROPERTY CXX_STANDARD 20)

# Implementation using the Accumulate algorithm
add_executable(genTagSeqAccu
    prodRules.cpp
    genTagSeqAccu.cpp)

    # Recursive implementation
add_executable(genTagSeqRec
    prodRules.cpp
    genTagSeqRec.cpp)

# Handwritten loop implementation
add_executable(genTagSeqLoop
    prodRules.cpp
    genTagSeqLoop.cpp)