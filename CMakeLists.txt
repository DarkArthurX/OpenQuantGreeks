cmake_minimum_required(VERSION 3.15)
project(GreeksCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    include(ProcessorCount)
    ProcessorCount(N)
    if(NOT N EQUAL 0)
        set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
    endif()
endif()

add_library(greeks STATIC
    src/math/cdf.cpp
    src/math/pdf.cpp
    src/math/d1.cpp
    src/math/d2.cpp
    src/math/maths.cpp
    src/math/common.cpp
    src/bsm/validation.cpp
    src/bsm/price.cpp
    src/bsm/impliedvol.cpp
    src/bsm/full.cpp
    src/diffs.cpp
    src/1stOrder/price.cpp
    src/1stOrder/delta.cpp
    src/1stOrder/vega.cpp
    src/1stOrder/theta.cpp
    src/1stOrder/rho.cpp
    src/1stOrder/lambda.cpp
    src/1stOrder/epsilon.cpp
    src/2ndOrder/gamma.cpp
    src/2ndOrder/vanna.cpp
    src/2ndOrder/charm.cpp
    src/2ndOrder/volga.cpp
    src/2ndOrder/veta.cpp
    src/2ndOrder/vera.cpp
    src/2ndOrder/dualrho.cpp
    src/3rdOrder/speed.cpp
    src/3rdOrder/zomma.cpp
    src/3rdOrder/color.cpp
    src/3rdOrder/ultima.cpp
    src/3rdOrder/dvannadvol.cpp
    src/4thOrder/snap.cpp
    src/4thOrder/zedzeta.cpp
    src/4thOrder/crackle.cpp
    src/4thOrder/pop.cpp
    src/5thOrder/jounce.cpp
    src/5thOrder/quintema.cpp
    src/5thOrder/mixed5th.cpp
    src/6thOrder/pounce.cpp
    src/6thOrder/hexema.cpp
    src/6thOrder/mixed6th.cpp
    src/all.cpp
)

target_include_directories(greeks PUBLIC src)

find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
        include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(greeks_tests
    tests/main.cpp
    tests/test_price.cpp
    tests/test_greeks.cpp
    tests/test_impliedvol.cpp
    tests/test_numerical.cpp
)

target_link_libraries(greeks_tests PRIVATE greeks Catch2::Catch2WithMain)

target_include_directories(greeks_tests PRIVATE src ${Catch2_SOURCE_DIR}/src)

enable_testing()
add_test(NAME GreeksTests COMMAND greeks_tests)