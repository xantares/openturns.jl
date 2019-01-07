
import openturns
ot = openturns


dists= [ot.Normal(5.0, 3.0), ot.Arcsine(5.2, 11.6), ot.Beta(2.0, 5.0, -1.0, 2.0)]
for dist in dists
    @show dist
    @show ot.getDimension(dist)
    @show ot.getRealization(dist)
    @show ot.getSample(dist, 5)
    x = ot.getMean(dist)
    @show ot.computePDF(dist, x)
    @show ot.computeCDF(dist, x)
    @show ot.computeQuantile(dist, 0.5)
    @show ot.getMean(dist)
    @show ot.getSkewness(dist)
    @show ot.getKurtosis(dist)
end
