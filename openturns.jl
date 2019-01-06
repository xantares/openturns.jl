module openturns

using CxxWrap
@wrapmodule("openturns_julia")

function __init__()
  @initcxx
end

end
