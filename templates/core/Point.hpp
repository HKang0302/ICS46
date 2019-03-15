// Point.hpp
//
// ICS 46 Winter 2019
// Code Example
//
// This header file contains both a declaration and a definition of a class
// template called Point.  Point objects represent a particular point in a
// three-dimensional space, and are made up of three coordinates named "x",
// "y", and "z".

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>



// It might seem a bit odd for a class as simple as Point to be a class
// template.  Why would we ever need different kinds of points?  All they have
// are three coordinates; what could be simpler than that?
//
// Whether or not something should be a template is not a matter of whether
// it's simple or complex, though.  Templates are about flexibility; a
// class template provides the flexibility for users of that class to
// configure it for different uses in different scenarios.  And there are
// potentially different scenarios here:
//
// * We might want our coordinates to be type "double", because we want a
//   fair amount of floating-point precision
// * We might want our coordinates to be type "float", because it's more
//   important to us that they take less memory or that operations on them
//   are fast (e.g., on some hardware where 32-bit floating point operations
//   are faster than 64-bit)
// * We might want our coordinates to be type "int", because we're dealing
//   with a discrete space instead of a (more or less) continuous one
// * We might want our coordinates to be some custom type, like an arbitrary-
//   precision decimal or integer type
//
// So rather than making this decision wholesale, limiting our ability
// to reuse this class in cases where that decision is the wrong one, we'll
// instead leave it up to users of our class to decide.  For example, if
// they want a Point where the coordinates are doubles, all they need to
// do is ask:
//
//     Point<double> p1{3.5, 7.75, -6.25};
//
// whereas a Point where the coordinates are ints instead is available
// similarly:
//
//     Point<int> p2{5, -7, 4};
//
// It's important to realize that while Point<double> and Point<int> are
// classes that have been built from the same template, they're actually
// different classes; they're distinct types that are incompatible with
// each other (unless we set them up to be compatible; more on that a
// little later in the example).


// When we want to write a template, we begin with the word "template"
// and follow it with template parameters surrounded by angle brackets.
// In this case, we want a class template, so we put the "template <...>"
// in front of the word "class" (and, traditionally, we write it on a
// separate line, though this is not a requirement in C++).
//
// It should be noted that it is also legal to say this instead:
//
//     template <class CoordinateType>
//
// and that it would have the same meaning; either "typename" or "class"
// means "I would like this to be a type."  However, the use of "class"
// here is somewhat old-school; the "typename" keyword was added to C++
// in the first standardization process in the mid-to-late 1990s, and is
// now the typical way to specify a template, though old habits die hard,
// so you still see a lot of code that uses "class" instead of "typename".
//
// Also, from a naming perspective, I should point out that a lot of
// template-writers use single-lettered names for their type parameters
// -- quite often, T.  This is especially done when there is no limitation
// on what the type can be, so T is a shorthand for "any type."  However,
// I'm a fan of naming type parameters to make clear what their purpose
// is, so I like names like CoordinateType, ElementType, Iterator, etc.,
// that make clear what's actually going on.  (I do sometimes use something
// simple like T, but only when there's nothing interesting I can say about
// the type, like in a swap function template.)  You spend a lot more time
// reading code than you do writing it, so the act of spending a little
// extra time typing a complete name for something pays you back later when
// you (or others) are trying to understand what you wrote.


template <typename CoordinateType>
class Point
{
public:
    // Constructing a Point requires specifying its x-, y-, and z-
    // coordinates.  Because there is a range of possibilities
    // for the CoordinateType, and because some of those might be
    // expensive to copy, we'll accept them by reference.
    Point(
        const CoordinateType& x, const CoordinateType& y,
        const CoordinateType& z);


    // We'd also like to be able to copy Point objects.  Ordinarily, we
    // wouldn't have to do anything special to ensure this, because we
    // would automatically be given a copy constructor and an assignment
    // operator that do a member-by-member copy of the member variables
    // (x_, y_, and z_).  However, there's a useful twist here that we
    // should consider.  Why shouldn't this be legal?
    //
    //     Point<float> p1{3.5, 2.75, -0.5};
    //     Point<double> p2 = p1;
    //
    // If that seems strange, think about it this way: It would be legal
    // to assign the individual floats into doubles, so why shouldn't it
    // be legal to assign a Point<float> into a Point<double>?
    //
    // Granted, I can see an opposite side to this argument, but for the
    // purposes of showing you something new, let's consider how we'd
    // achieve our goal.
    //
    // What we would need is a separate copy constructor for every type
    // that we'd like to copy from.  That might be a lot of copy constructors,
    // and, what's worse, a different set depending on what CoordinateType is.
    // But there's a workaround for all of that: member functions can be
    // themselves templates, which means that you're asking for a potentially
    // infinite set (but, in practice, limited only to the ones you use) of
    // member functions that are similar.
    //
    // Declaring these copy constructors can be done like this.  The
    // implementation -- which constraints what OtherCoordinateType can
    // be -- appears below.
    template <typename OtherCoordinateType>
    Point(const Point<OtherCoordinateType>& other);


    // We'd also like to be able to do that with the assignment operator.
    template <typename OtherCoordinateType>
    Point& operator=(const Point<OtherCoordinateType>& other);


    // x() returns the x-coordinate associated with some point.  The
    // coordinate is returned by reference, so that it can be modified,
    // though the "const" overload (the one that would be called if you
    // call this member function on a const Point) instead returns a
    // const reference instead.
    CoordinateType& x() noexcept;
    const CoordinateType& x() const noexcept;


    // y() returns the y-coordinate associated with some point.
    CoordinateType& y() noexcept;
    const CoordinateType& y() const noexcept;


    // z() returns the z-coordinate associated with some point.
    CoordinateType& z() noexcept;
    const CoordinateType& z() const noexcept;


    // Calculates the distance this point is from another point, with the
    // result reported as a double, which is a reasonably good choice in
    // most cases.  (Note that it's reasonable to imagine that we might
    // sometimes want result types other than doubles, or that we might
    // like to be able to compare Points with different coordinate types,
    // so we could make this a member function template, too, but I'll
    // leave that detail out of this example for simplicity.
    double distanceFrom(const Point<CoordinateType>& p) const;


private:
    // Here, we have member variables for the three coordinates.  The
    // appropriate type for these is whatever the CoordinateType is for
    // a particular Point.
    //
    // Note the naming convention here.  Because I want the member variables
    // to have the same name as the member functions used to access them,
    // but because that's not legal in C++, I'm adopting the convention of
    // adding an underscore to the end of their names to differentiate.
    // I don't normally like to use stray underscores like this -- I'm
    // opposed to the idea that all member variables should have their own
    // special naming convention -- but this, to me, is better than trying
    // to come up with a different name.
    CoordinateType x_;
    CoordinateType y_;
    CoordinateType z_;
};



// A class declaration contains, at minimum, a list of all of the members
// of the class, so that the compiler will know what member variables are
// contained in objects of that class, and will also know what member
// functions can be called on objects of that class.
//
// The class template declaration above plays much the same role, but
// remember that it declares a *set* of possible classes.  Still, the idea
// is the same: a class template declaration, at minimum, lists all of the
// members that should be in all of the classes in the set, in terms of the
// template's parmaeters (CoordinateType, in this example).
//
// Now we need an analogue for the definitions of the class' member functions.
// The problem is this: C++ doesn't actually compile a function template --
// or a member function of a template class -- until it is instantiated.  So,
// until you declare a Point<double> variable somewhere, there's no such class
// as Point<double>.  But, at the point where you declare a Point<double>
// variable, a C++ compiler will now need to stop and compile the Point<double>
// class declaration, as well as any of the member functions that are
// subsequently called on that Point<double> variable.  In order to compile
// them wherever used, the full source code needs to be made available in
// the header file.  So, we'll need to define all of the member functions
// right here in the header file.



// One more thing to think about: how do we implement the member functions?
// A class template is a blueprint for a set of classes.  When you declare a
// member function in a class template, you're actually declaring a set of
// functions, one for each instantiation of the class template.  So, when you
// declare a constructor in the Point template above, you've actually declared
// a set of Point constructors.  What we need now is a definition for the
// whole set of Point constructors.  The good news is that we already know
// how to do that: make a function template that specifies all of the
// possible Point constructors at once.
//
// Notice the syntax below; it's a bit tricky.  First of all, since we're
// declaring a function template, we start with the "template" keyword and
// a list of the type parameters.  Then we specify the return type (but a
// constructor has no return type, so I've left it out of the constructor,
// though you'll see it on other member functions), then the name of the
// function.  The name of the function is listed as:
//
//     Point<CoordinateType>::Point
//
// The reason for this bizarre-looking piece of syntax is this: you need
// to name the class "Point<CoordinateType>" explicitly, because that's
// the thing that makes the various functions in the set different from
// each other.  But once you've said "Point<CoordinateType>::", that puts
// you in the scope of Point<CoordinateType>, so any subsequent use of
// the word "Point" is assumed to be "Point<CoordinateType>".


template <typename CoordinateType>
Point<CoordinateType>::Point(
    const CoordinateType& x, const CoordinateType& y,
    const CoordinateType& z)
    : x_{x}, y_{y}, z_{z}
{
}


// Notice the syntax here for implementing a member function template.
// This is a template that has inside of it another template.  As mind-
// bending as that sounds at first, there's a sensible reason for it:
// The outer template is the one that generates each Point<T> class.
// The inner template is the one that, for each of those Point<T> classes,
// generates all of its possibly copy constructors.
//
// The same thing appears again when we implement the assignment operator.
//
// One more interesting wrinkle here.  Notice that I said "other.x()"
// instead of "other.x_".  That's actually a necessity, because the x_
// member variable is private, which makes it private *to each
// instantiation of Point<CoordinateType>*, so that it can't be accessed
// by code in a different instantiation.

template <typename CoordinateType>
template <typename OtherCoordinateType>
Point<CoordinateType>::Point(const Point<OtherCoordinateType>& other)
    : x_{other.x()}, y_{other.y()}, z_{other.z()}
{
}


template <typename CoordinateType>
template <typename OtherCoordinateType>
Point<CoordinateType>& Point<CoordinateType>::operator=(const Point<OtherCoordinateType>& other)
{
    // Memberwise self-assignment should be safe here, so no need to do
    // the self-assignment check.
    x_ = other.x();
    y_ = other.y();
    z_ = other.z();
    return *this;
}


template <typename CoordinateType>
CoordinateType& Point<CoordinateType>::x() noexcept
{
    return x_;
}


template <typename CoordinateType>
const CoordinateType& Point<CoordinateType>::x() const noexcept
{
    return x_;
}


template <typename CoordinateType>
CoordinateType& Point<CoordinateType>::y() noexcept
{
    return y_;
}


template <typename CoordinateType>
const CoordinateType& Point<CoordinateType>::y() const noexcept
{
    return y_;
}


template <typename CoordinateType>
CoordinateType& Point<CoordinateType>::z() noexcept
{
    return z_;
}


template <typename CoordinateType>
const CoordinateType& Point<CoordinateType>::z() const noexcept
{
    return z_;
}



// Were it not for this member function, it would be possible to use any
// type as a CoordinateType.  Even Point<std::string> would be legal.  And,
// in fact, a Point<std::string> is actually legal still -- *unless* we
// call this distanceFrom() function on one, in which case our attempts to
// multiply and subtract coordinate values from one another will cause
// compile-time errors, because you can neither subtract nor multiply
// std::string objects in C++.
//
// Note that std::sqrt() can throw an exception, so we can't declare this
// member function to be "noexcept".

template <typename CoordinateType>
double Point<CoordinateType>::distanceFrom(const Point<CoordinateType>& other) const
{
    return std::sqrt(
        (x_ - other.x_) * (x_ - other.x_)
        + (y_ - other.y_) * (y_ - other.y_)
        + (z_ - other.z_) * (z_ - other.z_));
}



#endif // POINT_HPP
