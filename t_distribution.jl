
import openturns
ot = openturns


function test_distribution(dist)
    @show ot.getDimension(dist)
    @show ot.repr(ot.getRealization(dist))
    @show ot.repr(ot.getSample(dist, 5))
    x = ot.getMean(dist)
    @show ot.computePDF(dist, x)
    @show ot.computeCDF(dist, x)
    @show ot.repr(ot.getMean(dist))
    @show ot.repr(ot.getSkewness(dist))
    @show ot.repr(ot.getKurtosis(dist))
end


normal = ot.Normal(5.0, 3.0)
arcsine = ot.Arcsine()

test_distribution(arcsine)
test_distribution(normal)



