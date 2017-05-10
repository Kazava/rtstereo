#ifndef DATUM_3D_HPP
#define DATUM_3D_HPP

// If the user needs his own variables, he can inherit the op::Datum struct and add them
// UserDatum can be directly used by the OpenPose wrapper because it inherits from op::Datum, just define Wrapper<UserDatum> instead of Wrapper<op::Datum>
struct Datum3D : public op::Datum
{
    op::Array<float> poseKeyPoints3D;

    Datum3D(){}
};

#endif // DATUM_3D_HPP
