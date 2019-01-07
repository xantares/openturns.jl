
import openturns
ot = openturns



dists= [ot.Normal(5.0, 3.0), ot.Arcsine()]
for dist in dists
    @show ot.getDimension(dist)
    @show ot.getRealization(dist)
    @show ot.getSample(dist, 5)
    x = ot.getMean(dist)
    @show ot.computePDF(dist, x)
    @show ot.computeCDF(dist, x)
    @show ot.getMean(dist)
    @show ot.getSkewness(dist)
    @show ot.getKurtosis(dist)
end
