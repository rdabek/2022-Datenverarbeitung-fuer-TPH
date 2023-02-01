#pragma once

#include <memory>
#include <string>
#include <vector>

namespace geometric {

    // Interface for figure functionality
    class Figure {
        public:
            virtual ~Figure() = default;
            virtual auto cloneFigure() const -> std::unique_ptr<Figure> = 0;
            virtual auto setName(const std::string& name) -> void = 0;
            virtual auto getName() -> std::string = 0;

            virtual auto move(double dx, double dy) -> void = 0;
            virtual auto show() -> void = 0;
    };

    class Kreis : public Figure {
        public:
            Kreis(const std::string& name, double x, double y, double r);

            auto cloneFigure() const -> std::unique_ptr<Figure>;

            auto setName(const std::string& name) -> void override;

            auto getName() -> std::string override;

            auto move(double dx, double dy) -> void override;

            auto show() -> void override;

        private:
            std::string name;
            double x, y, r;
    };

    class Stern : public Figure {
        public:
            Stern(const std::string& name, double x, double y, double d);

            auto cloneFigure() const -> std::unique_ptr<Figure> override;

            auto setName(const std::string& name) -> void override;

            auto getName() -> std::string override;

            auto move(double dx, double dy) -> void override;

            auto show() -> void override;

        private:
            std::string name;
            double x, y, d;
    };

    class nEck : public Figure {
        public:
            nEck(const std::string& name, const std::vector<std::pair<double, double>>& vec);

            auto cloneFigure() const -> std::unique_ptr<Figure> override;

            auto setName(const std::string& name) -> void override;

            auto getName() -> std::string override;

            auto move(double dx, double dy) -> void override;

            auto show() -> void override;

            

        private:
            std::string name;
            std::vector<std::pair<double, double>> coords;
    };

}