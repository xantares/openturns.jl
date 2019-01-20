
import openturns
ot = openturns




f = ot.SymbolicFunction("x", "sin(x)")
@show f
@show ot.getInputDimension(f)
@show ot.getOutputDimension(f)
@show ot.call(f, [3.14159])

function jlfunc2(X)
    x=X[1]
    y=X[2]
   z = x+y
   return [z]
end
@show jlfunc2([4., 8.])

f = ot.JuliaFunction(2, 1, jlfunc2)
@show f
@show ot.getInputDimension(f)
@show ot.getOutputDimension(f)

@show methods(jlfunc2)
@show methods(f)
# jlfunc2()
@show ot.call(f, [4., 8.])
@show ot.getCallsNumber(f)


