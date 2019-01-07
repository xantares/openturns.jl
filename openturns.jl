module openturns

using CxxWrap
@wrapmodule("openturns_julia")

function __init__()
  @initcxx
end

for _type in [Point, Sample, Normal, Arcsine]
    Base.show(io::IO, x::_type) = print(io, repr(x))
end

end
