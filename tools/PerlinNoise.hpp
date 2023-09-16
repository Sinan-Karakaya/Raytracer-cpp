/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** PerlinNoise
*/

#ifndef PERLINNOISE_HPP_
    #define PERLINNOISE_HPP_

    #include "Tools.hpp"

namespace Math {
    class PerlinNoise {
        public:
            PerlinNoise()
            {
                RayTracer::Tools toolBox;

                // Generate the POINT_COUNT random unit vectors
                ranVec = new Vector3D[POINT_COUNT];
                for (int i = 0; i < POINT_COUNT; ++i)
                    ranVec[i] = toolBox.randomVector(-1, 1).unitVector();

                // Generate the perm_x, perm_y and perm_z
                perm_x = perlin_generate_perm();
                perm_y = perlin_generate_perm();
                perm_z = perlin_generate_perm();
            }

            ~PerlinNoise()
            {
                if (ranVec)
                    delete[] ranVec;
                if (perm_x)
                    delete[] perm_x;
                if (perm_y)
                    delete[] perm_y;
                if (perm_z)
                    delete[] perm_z;
            }

            /**
             * @brief Compute the perlin noise
             *
             * @param p
             * @return double
             */
            double noise(const Vector3D &p) const
            {
                // Get the fractional part of the point
                double u = p.x - std::floor(p.x);
                double v = p.y - std::floor(p.y);
                double w = p.z - std::floor(p.z);

                // Get the integer part of the point
                u = u * u * (3 - 2 * u);
                v = v * v * (3 - 2 * v);
                w = w * w * (3 - 2 * w);

                // Get the integer part of the point
                int i = static_cast<int>(std::floor(p.x));
                int j = static_cast<int>(std::floor(p.y));
                int k = static_cast<int>(std::floor(p.z));

                // Create a 3D array of vectors
                Vector3D c[2][2][2];

                // Fill the array with the value from 0 to 1
                for (int di = 0; di < 2; di++) {
                    for (int dj = 0; dj < 2; dj++) {
                        for (int dk = 0; dk < 2; dk++) {
                            c[di][dj][dk] = ranVec[
                                perm_x[(i + di) & 255] ^
                                perm_y[(j + dj) & 255] ^
                                perm_z[(k + dk) & 255]
                            ];
                        }
                    }
                }
                return perlin_interp(c, u, v, w);
            }

            /**
             * @brief Compute the perlin interpolation
             *
             * @param p
             * @param depth
             * @return double
             */
            double turb(const Vector3D &p, int depth = 7) const
            {
                Vector3D temp_p = p;
                double accum = 0.0f;
                double weight = 1.0f;

                for (int i = 0; i < depth; i++) {
                    accum += weight * noise(temp_p);
                    weight *= 0.5f;
                    temp_p *= 2;
                }
                return fabs(accum);
            }

        private:
            /**
             * @brief Generate the permutation table
             *
             * @return int*
             */
            static int *perlin_generate_perm()
            {
                // Generate the permutation table
                int *p = new int[POINT_COUNT];

                // Fill the table with the value from 0 to POINT_COUNT
                for (int i = 0; i < PerlinNoise::POINT_COUNT; ++i)
                    p[i] = i;

                // Permute the table
                permute(p, POINT_COUNT);
                return p;
            }

            /**
             * @brief Permute the table
             *
             * @param p
             * @param n
             */
            static void permute(int *p, int n)
            {
                int target = 0;
                int tmp = 0;

                for (int i = n - 1; i > 0; i--) {
                    target = int(drand48() * (i + 1));
                    tmp = p[i];
                    p[i] = p[target];
                    p[target] = tmp;
                }
            }

            /**
             * @brief Interpolate the value of the point
             *
             * @param c
             * @param u
             * @param v
             * @param w
             * @return double
             */
            static double perlin_interp(Vector3D c[2][2][2], double u, double v, double w)
            {
                // Get the fractional part of the point
                double uu = u * u * (3 - 2 * u);
                double vv = v * v * (3 - 2 * v);
                double ww = w * w * (3 - 2 * w);
                double accum = 0.0f;

                // Get the integer part of the point
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < 2; k++) {
                            // Create a weight vector
                            Vector3D weight_v(u - i, v - j, w - k);

                            // Get the dot product of the random vector and the weight vector
                            accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww)) * c[i][j][k].dot(weight_v);
                        }
                    }
                }
                return accum;
            }

        // DEFINE value for perlin noise
        private:
            // The number of point in the perlin noise
            static const int POINT_COUNT = 256;

        private:
            // The list of random vectors of size POINT_COUNT
            Vector3D *ranVec;

            // The permutation table
            int *perm_x;
            int *perm_y;
            int *perm_z;
    };
};

#endif /* !PERLINNOISE_HPP_ */
