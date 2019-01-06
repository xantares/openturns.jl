
import openturns
ot = openturns

p = ot.Point()
p = ot.Point(3, 2.0)
@show ot.repr(p)
@show ot.norm(p)

s = ot.Sample()
s = ot.Sample(4, 8)
@show ot.getSize(s)
@show ot.repr(ot.computeMean(s))
