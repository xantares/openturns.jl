
#include "openturns_julia.hpp"

#include <string>
#include <openturns/Arcsine.hxx>
#include <openturns/Normal.hxx>
using namespace OT;

template <typename T>
void define_repr(jlcxx::Module& mod)
{
  mod.method("repr", [] (const T & p) { return p.__repr__();});
}

template <typename T>
void define_distribution(jlcxx::TypeWrapper<T> distribution_type)
{
  distribution_type
    .method("getDimension", &T::getDimension)
    .method("getRealization", &T::getRealization)
    .method("getSample", [] (const T& n, const int_t size) { return n.getSample(size); } )
    .method("computePDF", [] (const T& n, const Point & x) { return n.computePDF(x); } )
    .method("computeCDF", [] (const T& n, const Point & x) { return n.computeCDF(x); } )
    .method("getMean", &T::getMean)
    .method("getSkewness", &T::getSkewness)
    .method("getKurtosis", &T::getKurtosis);
}

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  mod.add_type<Point>("Point")
    .constructor<const int_t, const Scalar>()
    .method("norm", &Point::norm)
    .method("resize", &Point::resize)
    .method("getDimension", &Point::getDimension)
    .method("getindex", [] (const Point& n, const int_t i) { return n[i]; })
    .method("setindex!", [] (Point& n, const double x, const int_t i) { n[i] = x; });
  define_repr<Point>(mod);

  mod.add_type<Sample>("Sample")
    .constructor<const int_t, const int_t>()
    .method("getindex", [] (const Sample& n, const int_t i) { return Point(n[i]); })
    .method("setindex!", [] (Sample& n, const Point & x, const int_t i) { n[i] = x; })
    .method("getSize", &Sample::getSize)
    .method("computeMean", &Sample::computeMean);
  define_repr<Sample>(mod);

  jlcxx::TypeWrapper<Arcsine> arcsine(mod.add_type<Arcsine>("Arcsine").constructor<const Scalar, const Scalar>());
  define_distribution(arcsine);
  define_repr<Arcsine>(mod);
  jlcxx::TypeWrapper<Normal> normal(mod.add_type<Normal>("Normal").constructor<const Scalar, const Scalar>());
  define_distribution(normal);
  define_repr<Normal>(mod);
}

