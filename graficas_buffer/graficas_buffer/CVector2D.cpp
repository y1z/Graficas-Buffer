#include "CVector2D.h"

CVector2D::CVector2D()
	:X(0), Y(0)
{}

CVector2D::CVector2D(float x, float y)
	: X(x), Y(y)
{}

CVector2D::~CVector2D()
{}

float CVector2D::DotProduct(CVector2D & OtherVector)
{
	float Result = (this->X * OtherVector.X) + (this->Y * OtherVector.Y);
	return Result;
}

float CVector2D::CrossProduct(CVector2D & OtherVector)
{

	return (this->X * OtherVector.Y) - (this->Y * OtherVector.X);
}

CVector2D CVector2D::Add(CVector2D & OtherVector)
{
	return CVector2D(this->X + OtherVector.X, this->Y + OtherVector.Y);
}

CVector2D CVector2D::Subtract(const CVector2D & OtherVector) const
{
	return CVector2D(this->X - OtherVector.X, this->Y - OtherVector.Y);
}

CVector2D CVector2D::Normalize()
{
	//get current magnitude
	float magnitude = this->Magnitude();
	CVector2D UnitVector;
	if (this->X > 0 || this->X < 0)
	{
		UnitVector.SetX(this->X / magnitude);
	}
	else
	{
		UnitVector.SetX(0.01f);
	}

	if (this->Y > 0 || this->Y < 0)
	{
		UnitVector.SetY(this->Y / magnitude);
	}
	else
	{
		UnitVector.SetY(0.01f);
	}

	return UnitVector;
}

CVector2D CVector2D::ScalarMultiplation(float Scalar)
{
	return CVector2D(this->X *Scalar, this->Y * Scalar);
}

float CVector2D::Magnitude()
{
	float SqaredMagnatude = (this->X * this->X) + (this->Y * this->Y);

	return sqrt(SqaredMagnatude);
}

float CVector2D::SquaredMagnitude()
{
	return (this->X * this->X) + (this->Y * this->Y);
}

float CVector2D::InvserSqaredRoot()
{
	return 1 / SquaredMagnitude();
}

float CVector2D::GetX() const
{
	return this->X;
}

float CVector2D::GetY() const
{
	return this->Y;
}

void CVector2D::SetX(float value)
{
	this->X = value;
}

void CVector2D::SetY(float value)
{
	this->Y = value;
}

float CVector2D::Angle()
{
	return std::atan2(Y, X);
}

float CVector2D::AngleBetweenTwoVectors(CVector2D & OtherVector)
{
	float Product = this->DotProduct(OtherVector);
	float ThisVectorsMagnitude = this->Magnitude();
	float OtherVectorMagnitude = OtherVector.Magnitude();

	return acos(Product / (ThisVectorsMagnitude * OtherVectorMagnitude));
}

CVector2D CVector2D::operator+(const CVector2D & OtherVector) const
{
	return CVector2D(this->X + OtherVector.X, this->Y + OtherVector.Y);;
}

CVector2D CVector2D::operator-(const CVector2D & OtherVector) const
{
	return CVector2D(this->X - OtherVector.X, this->Y - OtherVector.Y);
}

CVector2D CVector2D::operator*(const CVector2D & OtherVector)
{
	CVector2D Result(this->X * OtherVector.X, this->Y * OtherVector.Y);
	return Result;
}

CVector2D CVector2D::operator*(const float & Scalar)
{
	return CVector2D((this->X * Scalar), (this->Y * Scalar));
}

CVector2D& CVector2D::operator=(const CVector2D & OtherVector)
{
	this->X = OtherVector.X;
	this->Y = OtherVector.Y;
	return *this;
}

bool CVector2D::operator==(const CVector2D & OtherVector)
{
	if (this->X > OtherVector.X || this->X < OtherVector.X)
		return false;
	if (this->Y > OtherVector.Y || this->Y < OtherVector.Y)
		return false;

	return true;
}

CVector2D& CVector2D::operator+=(const CVector2D & OtherVector)
{
	this->X = this->X + OtherVector.X;
	this->Y = this->Y + OtherVector.Y;

	return *this;
}

CVector2D& CVector2D::operator-=(const CVector2D & OtherVector)
{
	this->X = this->X - OtherVector.X;
	this->Y = this->Y - OtherVector.Y;

	return *this;
}

CVector2D& CVector2D::operator*=(const CVector2D & OtherVector)
{
	this->X = this->X * OtherVector.X;
	this->Y = this->Y * OtherVector.Y;

	return *this;
}

CVector2D& CVector2D::operator*=(float Scalar)
{
	this->X = this->X * Scalar;
	this->Y = this->Y * Scalar;

	return *this;
}
