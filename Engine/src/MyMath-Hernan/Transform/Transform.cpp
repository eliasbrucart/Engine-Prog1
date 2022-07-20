#include "Transform.h"
using namespace My;

Transform::Transform() {
	model = My::Matrix4x4::zero;
	translate = My::Matrix4x4::zero;
	rotate = My::Matrix4x4::zero;
	scale = My::Matrix4x4::zero;

	position = My::Vector3::zero;
	rotation = My::Quaternion::identity;
	localScale = My::Vector3::one;
}
void Transform::Rotate(float x, float y, float z, float w) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	rotation.w = w;

	rotate = My::Matrix4x4::Rotate(rotate, rotation);
	UpdateModel();
}
void Transform::Rotate(Quaternion quaternion) {
	rotation.x = quaternion.x;
	rotation.y = quaternion.y;
	rotation.z = quaternion.z;
	rotation.w = quaternion.w;

	rotate = My::Matrix4x4::Rotate(rotate, rotation);
	UpdateModel();
}
void Transform::Translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;

	translate = My::Matrix4x4::Translate(translate, position);
	UpdateModel();
}
void Transform::Translate(My::Vector3 vector) {
	position.x += vector.x;
	position.y += vector.y;
	position.z += vector.z;

	translate = My::Matrix4x4::Translate(translate, position);
	UpdateModel();
}
void Transform::Scale(float x, float y, float z) {
	localScale.x = x;
	localScale.y = y;
	localScale.z = z;

	scale = My::Matrix4x4::Scale(scale, localScale);
	UpdateModel();
}
void Transform::UpdateModel() {
	My::Matrix4x4::TRS(model, translate, rotate, scale);
}