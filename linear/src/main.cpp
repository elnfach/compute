#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

#include <glm/glm.hpp>

static void gauss(const glm::mat4 mat);
static void gaussSeidel(const glm::mat3& A, const glm::vec3& b, float tolerance = 0.01);

int main()
{
	setlocale(LC_ALL, "Ru");
	std::cout.setf(std::ios_base::fixed);

	glm::mat3x4 extended_matrix = {
		2, 0, -1, -3,
		-1, 3, 1, 2,
		1, -1, 4, 3
	};

    glm::mat3 matrix = {
        2, 0, -1,
        -1, 3, 1,
        1, -1, 4
    };

    glm::vec3 b = {
        -3,
        2,
        3
    };

    std::cout << "Метод Гаусса:" << std::endl;
	gauss(extended_matrix);
    std::cout << std::endl;

    std::string ans;
    bool is_runnings = true;
    while (is_runnings)
    {
        std::cout << "Метод Гаусса-Зейделя:" << std::endl;
        std::cout << "Введите E:";
        float eps;
        std::cin >> eps;
        gaussSeidel(matrix, b, eps);
        std::cout << "Закончить? y/n\n";
        std::cin >> ans;
        if (ans == "y") is_runnings = false;
    }

	return 0;
}

void gauss(const glm::mat4 mat) {
    glm::mat4 matrix = mat;
    glm::vec3 result = glm::vec3(0.0f);

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            float ratio = matrix[j][i] / matrix[i][i];
            for (int k = 0; k < 4; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }
    }

    for (int i = 2; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            float ratio = matrix[j][i] / matrix[i][i];
            for (int k = 0; k < 4; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        float temp = matrix[i][i];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = matrix[i][j] / temp;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        std::cout << matrix[i][3] << " ";
    }
}

void gaussSeidel(const glm::mat3& A, const glm::vec3& b, float tolerance) {
    glm::vec3 x = glm::vec3(0.0f);
    glm::vec3 x_new = x;
    int maxIterations = 1000;
    float error = tolerance + 1.0f;
    int iterations = 0;

    while (error > tolerance && iterations < maxIterations) {
        x = x_new;
        for (int i = 0; i < 3; i++) {
            float sigma = 0.0f;
            for (int j = 0; j < 3; j++) {
                if (j != i) {
                    sigma += A[i][j] * x_new[j];
                }
            }
            x_new[i] = (b[i] - sigma) / A[i][i];
        }
        error = glm::length(x_new - x);
        iterations++;
    }

    for (int i = 0; i < x_new.length(); i++)
    {
        std::cout << x_new[i] << " ";
    }
    std::cout << "Количество итераций: " << iterations << std::endl;
}