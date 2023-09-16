/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Matrix
*/

#ifndef MATRIX_HPP_
    #define MATRIX_HPP_

    #include "Vector3D.hpp"

    #include <vector>
    #include <iostream>

namespace Math {
    class Matrix {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Matrix object
             *
             * @param width The width of the matrix
             * @param height The height of the matrix
             */
            Matrix(int width, int height) : _width(width), _height(height)
            {
                // Malloc the values
                _values = new double[width * height];

                // Set all the values to 0
                for (int i = 0; i < (width * height); i++)
                    _values[i] = 0.0f;
            }

            /**
             * @brief Construct a new Matrix object
             *
             * @param width The width of the matrix
             * @param height The height of the matrix
             * @param values The values of the matrix
             */
            Matrix(int width, int height, std::vector<double> values) : _width(width), _height(height)
            {
                // Malloc the values
                _values = new double[width * height];

                // Check if the size of the values is the same as the size of the matrix
                std::vector<double>::size_type matrixSize = width * height;

                // TODO: Add the error handling
                //if (matrixSize != values.size())
                //    throw Error::Matrix::InvalidSize();
                if (matrixSize != values.size()) {
                    std::cerr << "ERROR: The matrix have a invalid size " << std::endl;
                    return;
                }

                // Set all the values
                for (int i = 0; i < (width * height); i++)
                    _values[i] = values[i];
            }

            /**
             * @brief Copy Constructor of Matrix
             *
             * @param matrix The matrix to copy
             */
            Matrix(const Matrix &matrix) : _width(matrix._width), _height(matrix._height)
            {
                // Malloc the values
                _values = new double[_width * _height];

                // Set all the values
                for (int i = 0; i < (_width * _height); i++)
                    _values[i] = matrix._values[i];
            }

            /**
             * @brief Destroy the Matrix object
             *
             */
            ~Matrix()
            {
                if (_values)
                    delete[] _values;
            }

            ///////////////
            // Operators //
            ///////////////

            /**
             * @brief Operator = of Matrix
             * Copy the matrix
             * @param matrix The matrix to copy
             * @return Matrix& The matrix copied
             */
            Matrix &operator=(const Matrix &matrix)
            {
                // Check for self-assignment
                if (this == &matrix)
                    return *this;
                // Change the Matrix size if the given one is different
                if (_width != matrix._width || _height != matrix._height) {
                    _width = matrix._width;
                    _height = matrix._height;

                    if (_values)
                        delete[] _values;

                    _values = new double[_width * _height];
                }

                for (int i = 0; i < (_width * _height); i++)
                    _values[i] = matrix._values[i];
                return *this;
            }

            /**
             * @brief Operator () of Matrix
             * Get the value of the matrix at the given row and col
             * @param row The row of the matrix
             * @param col The col of the matrix
             * @return double The value of the matrix at the given row and col
             */
            double operator()(const int &row, const int &col) const
            {
                return _values[row * _height + col];
            }

            ///////////////////////
            // Setters & Getters //
            ///////////////////////

            /**
             * @brief Set the Value of the matrix at the given row and col
             *
             * @param value The value to set
             * @param row The row of the matrix
             * @param col The col of the matrix
             */
            void setValue(double value, const int &row, const int &col)
            {
                _values[row * _height + col] = value;
            }

            /**
             * @brief Get the Width of the Matrix
             *
             * @return int The width of the Matrix
             */
            int getWidth() const
            {
                return _width;
            }

            /**
             * @brief Get the Height of the Matrix
             *
             * @return int The height of the Matrix
             */
            int getHeight() const
            {
                return _height;
            }

            /////////////
            // Methods //
            /////////////

            /**
             * @brief Transpose the matrix
             *
             * @return Matrix The transposed matrix
             */
            Matrix transpose()
            {
                Matrix transposedMatrix(_height, _width);

                for (int row = 0; row < _height; row++)
                    for (int col = 0; col < _width; col++)
                        transposedMatrix.setValue(this->operator()(row, col), col, row);
                return transposedMatrix;
            }

            /**
             * @brief Get the determinant of the matrix
             * The determinant is the value of the matrix
             * @return double
             */
            double determinant() const
            {
                if (_width == 2)
                    return this->operator()(0, 0) * this->operator()(1, 1) - this->operator()(1, 0) * this->operator()(0, 1);
                double determiant = 0.0f;

                for (int col = 0; col < _width; col++)
                    determiant += this->operator()(0, col) * cofactor(0, col);
                return determiant;
            }

            /**
             * @brief Remove the row and col of the matrix
             *
             * @param row The row to remove
             * @param col The col to remove
             * @return Matrix The submatrix
             */
            Matrix subMatrix(int row, int col) const
            {
                Matrix subedMatrix = Matrix(_height - 1, _width - 1);
                int nx = 0;
                int ny = 0;

                for (int y = 0; y < _height; y++) {
                    nx = 0;
                    if (y == row)
                        continue;
                    for (int x = 0; x < _width; x++) {
                        if (x != col) {
                            subedMatrix.setValue(this->operator()(y, x), ny, nx);
                            nx++;
                        }
                    }
                    ny++;
                }
                return subedMatrix;
            }

            /**
             * @brief Get the minor of the matrix
             * The minor is the determinant of the submatrix
             * @param row
             * @param col
             * @return double The minor of the matrix
             */
            double minor(int row, int col) const
            {
                return subMatrix(row, col).determinant();
            }

            /**
             * @brief Get the cofactor of the matrix
             * The cofactor is the minor with the sign
             * @param row
             * @param col
             * @return double
             */
            double cofactor(int row, int col) const
            {
                double min = minor(row, col);

                if ((row + col) % 2 == 1)
                    return -min;
                return min;
            }

            /**
             * @brief Check if the matrix is invertible
             *
             * @return true
             * @return false
             */
            bool isInvertible() const
            {
                return determinant() != 0;
            }

            /**
             * @brief Get the inverse of the matrix
             *
             * @return Matrix The inverse of the matrix
             */
            Matrix inverse() const
            {
                Matrix inversedMatrix = Matrix(_height, _width);
                double deter = determinant();

                for (int row = 0; row < _height; row++) {
                    for (int col = 0; col < _width; col++) {
                        double cof = cofactor(row, col);

                        inversedMatrix.setValue(cof / deter, col, row);
                    }
                }
                return inversedMatrix;
            }

            /**
             * @brief Generate a identity matrix
             * A identity matrix is a matrix with 1 on the diagonal and 0 everywhere else
             * @param dimension The dimension of the matrix
             * @return Matrix The identity matrix
             */
            Matrix identityMatrix(int dimension)
            {
                Matrix identityMatrix = Matrix(dimension, dimension);

                for (int i = 0; i < dimension; ++i)
                    identityMatrix.setValue(1, i, i);
                return identityMatrix;
            }

            ////////////////////
            // Transformation //
            ////////////////////

            /**
             * @brief Translate the matrix
             *
             * @param movement The movement to apply
             * @return Matrix The translated matrix
             */
            Matrix translation(Math::Vector3D movement)
            {
                Matrix translatedMatrix = identityMatrix(4);

                translatedMatrix.setValue(movement.x, 0, 3);
                translatedMatrix.setValue(movement.y, 1, 3);
                translatedMatrix.setValue(movement.z, 2, 3);
                return translatedMatrix;
            }

            /**
             * @brief Rotate the matrix on X axis
             *
             * @param radians The angle in radians
             * @return Matrix The rotated matrix
             */
            Matrix RotationX(double radians)
            {
                Matrix rotationMatrix = Matrix(4, 4);
                double cos_r = std::cos(radians);
                double sin_r = std::sin(radians);

                rotationMatrix.setValue(cos_r, 1, 1);
                rotationMatrix.setValue(-sin_r, 1, 2);
                rotationMatrix.setValue(sin_r, 2, 1);
                rotationMatrix.setValue(cos_r, 2, 2);
                rotationMatrix.setValue(1, 3, 3);
                return rotationMatrix;
            }

            /**
             * @brief Rotate the matrix on Y axis
             *
             * @param radians The angle in radians
             * @return Matrix The rotated matrix
             */
            Matrix RotationY(double radians)
            {
                Matrix rotationMatrix = Matrix(4, 4);
                double cos_r = std::cos(radians);
                double sin_r = std::sin(radians);

                rotationMatrix.setValue(cos_r, 0, 0);
                rotationMatrix.setValue(sin_r, 0, 2);
                rotationMatrix.setValue(1, 1, 0);
                rotationMatrix.setValue(-sin_r, 2, 0);
                rotationMatrix.setValue(cos_r, 2, 2);
                rotationMatrix.setValue(1, 3, 3);
                return rotationMatrix;
            }

            /**
             * @brief Rotate the matrix on Z axis
             *
             * @param radians The angle in radians
             * @return Matrix The rotated matrix
             */
            Matrix RotationZ(double radians)
            {
                Matrix rotationMatrix = Matrix(4, 4);
                double cos_r = std::cos(radians);
                double sin_r = std::sin(radians);

                rotationMatrix.setValue(cos_r, 0, 0);
                rotationMatrix.setValue(-sin_r, 0, 1);
                rotationMatrix.setValue(sin_r, 1, 0);
                rotationMatrix.setValue(cos_r, 1, 1);
                rotationMatrix.setValue(1, 2, 2);
                rotationMatrix.setValue(1, 3, 3);
                return rotationMatrix;
            }

            /**
             * @brief Scale the matrix
             *
             * @param scale The scale to apply
             * @return Matrix The scaled matrix
             */
            Matrix Scaling(Math::Vector3D scale)
            {
                Matrix scaledMatrix = Matrix(4, 4);

                scaledMatrix.setValue(scale.x, 0, 0);
                scaledMatrix.setValue(scale.y, 1, 1);
                scaledMatrix.setValue(scale.z, 2, 2);
                scaledMatrix.setValue(1, 3, 3);
                return scaledMatrix;
            }

            /**
             * @brief Shear the matrix
             *
             * @param x_y // x on y axis
             * @param x_z // x on z axis
             * @param y_x // y on x axis
             * @param y_z // y on z axis
             * @param z_x // z on x axis
             * @param z_y // z on y axis
             * @return Matrix
             */
            Matrix Shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
            {
                Matrix shearedMatrix = identityMatrix(4);

                shearedMatrix.setValue(x_y, 0, 1);
                shearedMatrix.setValue(x_z, 0, 2);
                shearedMatrix.setValue(y_x, 1, 0);
                shearedMatrix.setValue(y_z, 1, 2);
                shearedMatrix.setValue(z_x, 2, 0);
                shearedMatrix.setValue(z_y, 2, 1);
                return shearedMatrix;
            }

        private:
            // The width of the Matrix
            int _width;
            // The height of the Matrix
            int _height;
            // The values of the Matrix
            double *_values;
    };

    /**
     * @brief Multiply a matrix by a vector
     *
     * @param matrix The matrix
     * @param vector The vector
     * @return const Vector3D The result of the multiplication
     */
    inline const Vector3D operator*(const Matrix matrix, const Vector3D vector)
    {
        return Vector3D(
            matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3) * vector.w,
            matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3) * vector.w,
            matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3) * vector.w,
            matrix(3, 0) * vector.x + matrix(3, 1) * vector.y + matrix(3, 2) * vector.z + matrix(3, 3) * vector.w
        );
    }
};

#endif /* !MATRIX_HPP_ */
