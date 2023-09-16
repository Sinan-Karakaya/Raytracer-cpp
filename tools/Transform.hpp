/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
    #define TRANSFORM_HPP_

    #include "PrimitiveList.hpp"

    #define TO_RADIANS (M_PI / 180.0f)

namespace RayTracer::Geometry {
    class Translate : public APrimitive {
        public:
            Translate(IPrimitive *object, const Math::Vector3D &movement) : _object(object), _offset(movement) {};
            ~Translate()
            {
                //if (_object)
                //    delete _object;
            };

            /**
             * @brief Did the function hit of a Primitives after a translation.
             *
             * @param ray
             * @param t_min
             * @param t_max
             * @param rec
             * @return true
             * @return false
             */
            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
            {
                Ray movedRay(ray.getOrigin() - _offset, ray.getDirection(), ray.getTime());

                if (_object->hit(movedRay, t_min, t_max, rec) == false)
                    return false;
                rec.point += _offset;
                rec.setFaceNormal(movedRay, rec.normal);
                return true;
            }

            /**
             * @brief Did the function bounding_box of a Primitives after a translation.
             *
             * @param time0
             * @param time1
             * @param box
             * @return true
             * @return false
             */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override
            {
                if (_object->bounding_box(time0, time1, box) == false)
                    return false;
                box = Math::AABB(box.getMin() + _offset, box.getMax() + _offset);
                return true;
            }

            void builder(const libconfig::Setting &setting) {};

        private:
            IPrimitive *_object;
            Math::Vector3D _offset;
    };

    class Rotate : public APrimitive {
        public:
            Rotate(IPrimitive *object, double angle) : _object(object)
            {
                double radians = angle * TO_RADIANS;

                _sinTheta = std::sin(radians);
                _cosTheta = std::cos(radians);
                _hasBox = _object->bounding_box(0, 1, _box);

                Math::Vector3D min(MAXFLOAT, MAXFLOAT, MAXFLOAT);
                Math::Vector3D max(-MAXFLOAT, -MAXFLOAT, -MAXFLOAT);

                double x = 0.0f;
                double y = 0.0f;
                double z = 0.0f;
                for (size_t i = 0; i < 2; i++) {
                    for (size_t j = 0; j < 2; j++) {
                        for (size_t k = 0; k < 2; k++) {
                            x = i * _box.getMax().x + (1 - i) * _box.getMin().x;
                            y = j * _box.getMax().y + (1 - j) * _box.getMin().y;
                            z = k * _box.getMax().z + (1 - k) * _box.getMin().z;

                            double newX = _cosTheta * x + _sinTheta * z;
                            double newZ = -_sinTheta * x + _cosTheta * z;

                            Math::Vector3D tester(newX, y, newZ);

                            for (size_t c = 0; c < 3; c++) {
                                min[c] = fmin(min[c], tester[c]);
                                max[c] = fmax(max[c], tester[c]);
                            }
                        }
                    }
                }

                _box = Math::AABB(min, max);
            }

            ~Rotate()
            {
                //if (_object)
                //    delete _object;
            }

            /**
             * @brief Did the function hit of a Primitives after a rotation.
             *
             * @param ray
             * @param t_min
             * @param t_max
             * @param rec
             * @return true
             * @return false
             */
            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
            {
                Math::Vector3D origin = ray.getOrigin();
                Math::Vector3D direction = ray.getDirection();

                origin[0] = _cosTheta * ray.getOrigin()[0] - _sinTheta * ray.getOrigin()[2];
                origin[2] = _sinTheta * ray.getOrigin()[0] + _cosTheta * ray.getOrigin()[2];

                direction[0] = _cosTheta * ray.getDirection()[0] - _sinTheta * ray.getDirection()[2];
                direction[2] = _sinTheta * ray.getDirection()[0] + _cosTheta * ray.getDirection()[2];

                Ray rotatedRay(origin, direction, ray.getTime());

                if (_object->hit(rotatedRay, t_min, t_max, rec) == false)
                    return false;
                Math::Vector3D point = rec.point;
                Math::Vector3D normal = rec.normal;

                point[0] = _cosTheta * rec.point[0] + _sinTheta * rec.point[2];
                point[2] = -_sinTheta * rec.point[0] + _cosTheta * rec.point[2];

                normal[0] = _cosTheta * rec.normal[0] + _sinTheta * rec.normal[2];
                normal[2] = -_sinTheta * rec.normal[0] + _cosTheta * rec.normal[2];

                rec.point = point;
                rec.setFaceNormal(rotatedRay, normal);
                return true;
            }

            /**
             * @brief Did the function bounding_box of a Primitives after a rotation.
             *
             * @param time0
             * @param time1
             * @param box
             * @return true
             * @return false
             */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override
            {
                box = _box;
                return _hasBox;
            }

            void builder(const libconfig::Setting &setting) {};

        private:
            IPrimitive *_object;
            Math::AABB _box;
            double _sinTheta;
            double _cosTheta;
            bool _hasBox;
    };

    class FlipFace : public APrimitive {
        public:
            FlipFace(IPrimitive *object) : _object(object) {};

            ~FlipFace()
            {
                //if (_object)
                  //  delete _object;
            }

            /**
             * @brief Did the function hit of a Primitives after a flip face.
             *
             * @param ray
             * @param t_min
             * @param t_max
             * @param rec
             * @return true
             * @return false
             */
            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
            {
                if (_object->hit(ray, t_min, t_max, rec) == false)
                    return false;

                rec.frontFace = !rec.frontFace;
                return true;
            }

            /**
             * @brief Did the function bounding_box of a Primitives after a flip face.
             *
             * @param time0
             * @param time1
             * @param box
             * @return true
             * @return false
             */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override
            {
                return _object->bounding_box(time0, time1, box);
            }

            void builder(const libconfig::Setting &setting) {};

        private:
            IPrimitive *_object;
    };

    class Scale : public APrimitive {
        public:
            Scale(IPrimitive *object, const Math::Vector3D &scale) : _object(object), _scale(scale) {};

            ~Scale() {};

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
            {
                Ray scaledRay(ray.getOrigin() / _scale, ray.getDirection() / _scale, ray.getTime());

                if (_object->hit(scaledRay, t_min, t_max, rec) == false)
                    return false;

                rec.point *= _scale;
                rec.setFaceNormal(scaledRay, rec.normal);
                return true;
            }

            bool bounding_box(double time0, double time1, Math::AABB &box) const override
            {
                if (_object->bounding_box(time0, time1, box) == false)
                    return false;

                box = Math::AABB(box.getMin() * _scale, box.getMax() * _scale);
                return true;
            }

        private:
            IPrimitive *_object;
            Math::Vector3D _scale;
    };
};

#endif /* !TRANSFORM_HPP_ */
