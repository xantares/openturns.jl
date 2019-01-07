
import openturns
ot = openturns

p = ot.Point()
p = ot.Point(3, 2.0)
p[1] = 8.0
@show p[1]
@show p
@show ot.norm(p)

# s = ot.Sample()
s = ot.Sample(4, 8)
@show s[1]
# s[1] = ot.Point(4, 42.0)
@show ot.getSize(s)
repr(s)
@show ot.computeMean(s)
