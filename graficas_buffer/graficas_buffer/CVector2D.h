#pragma once
#include <cmath>
#include <iostream>

/*!
\class CVector2D "CVector2D.h"
\brief This class will be used for 2d vector math 
NOTE : all operator with '=' alter the current vector example: += -= *= 
*/

class CVector2D
{
public:// constructors 
	CVector2D();
	CVector2D(float x, float y);
	~CVector2D();
public:// functions

	//! multiplying two 2D vectors give a scalar.
	float DotProduct(CVector2D &OtherVector);
	//! return the theoretical component Z axis 
	float CrossProduct(CVector2D &OtherVector);
	/*! creates a new vector */
	CVector2D Add(CVector2D &OtherVector);
	/*! creates a new vector and can be used the tell distance*/
	CVector2D Subtract(const CVector2D &OtherVector) const;
	/*! crates a new vector */
	CVector2D ScalarMultiplation(float Scalar);
	/*! Returns a unit vector */
	CVector2D Normalize();
	/*! how long a vector is */
	float Magnitude();
	/*! can be used to tell the RELATIVE distance*/
	float SquaredMagnitude();

	float InvserSqaredRoot();
	/*! used to get the angle of the current vector */
	float Angle();

	float AngleBetweenTwoVectors(CVector2D &OtherVector);

	float GetX() const;
	float GetY() const;

	void SetX(float value);
	void SetY(float value);

	CVector2D operator+(const CVector2D &OtherVector) const;
	CVector2D	operator-(const CVector2D &OtherVector) const;
	// !the same as DotProduct
	CVector2D operator*(const CVector2D &OtherVector);

	/* alters the vector */
	CVector2D& operator+= (const CVector2D &OtherVector);
	/*!Return the Current ofter operation vector */
	CVector2D& operator-= (const CVector2D &OtherVector);
	/*!alters this vector and returns the result of multiplication */
	CVector2D& operator*= (const CVector2D &OtherVector);
	/*! multiples the current vector by a scalar*/
	CVector2D& operator*= (float Scalar);
	//!return a new vector 
	CVector2D operator*(const float &Scalar);

	CVector2D& operator=(const CVector2D &OtherVector);

	bool operator==(const CVector2D &OtherVector);

private://variables 

	float Y;
	float X;

};

