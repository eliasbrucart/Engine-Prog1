#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../Vector3/vector3.h"
#include "../Vector4/Vector4.h"
#include "../Quaternion/Quaternion.h"
#include "../Matrix4x4/Matrix4x4.h"

namespace My
{
	struct Transform {
	private:
		Matrix4x4 model;
		Matrix4x4 translate;
		Matrix4x4 rotate;
		Matrix4x4 scale;

	protected:
		void UpdateModel();

	public:
		Vector3 position;
		Quaternion rotation;
		Vector3 localScale;

		Transform();
		void Rotate(float x, float y, float z, float w);
		void Rotate(Quaternion quaternion);
		void Translate(float x, float y, float z);
		void Translate(My::Vector3 vector);
		void Scale(float x, float y, float z);
	};
}

#endif // !TRANSFORM_H
