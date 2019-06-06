.. image:: https://travis-ci.org/openturns/openturns.jl.svg?branch=master
    :target: https://travis-ci.org/openturns/openturns.jl

=======================
Julia language bindings
=======================

Experimental OpenTURNS bindings for the Julia language (https://julialang.org/)

Requirements:

- cmake
- OpenTURNS
- libcxxwrap-julia (https://github.com/JuliaInterop/libcxxwrap-julia)
- CxxWrap.jl (https://github.com/JuliaInterop/CxxWrap.jl)


Quickstart
----------
::

    git clone https://github.com/openturns/openturns.jl.git
    cd openturns.jl
    mkdir build && cd build
    cmake ..
    make
    JULIA_LOAD_PATH=$PWD/..: LD_LIBRARY_PATH=$PWD julia -e 'import openturns'

Example::

    import openturns
    ot = openturns
    normal = ot.Normal(5.0, 3.0)
    @show ot.getRealization(normal)
