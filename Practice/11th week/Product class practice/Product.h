#include <string.h>

using namespace std;

enum ProductQuality
{
    First,
    Second,
    Third,
    Undefined
};

#pragma region Product class definition
class Product
{
    private:
        double _purchasePrice, _salePrice;
        short _amountInStock;
        string _name;
        ProductQuality _quality;
    
    public:
        Product();

        Product(const double, const double, const short, const string&, const ProductQuality);

        ~Product()
        {
        }

        bool doesProductGenerateProfit();

        double calculateProfit();

        double getPurchasePrice();

        double getSalePrice();

        float calculateDiscountFromSalePrice();

        short getAmountInStock();

        string getName();

        ProductQuality getQuality();
        
        void setAmountInStock(const short);

        void setName(const string&);

        void setPurchasePrice(const double);

        void setQuality(const ProductQuality);

        void setSalePrice(const double);

        void updateSalePrice();
};

Product::Product()
{
    _purchasePrice = 0.0;
    _salePrice = 0.0;
    _amountInStock = 0;
    _name = "";
    _quality = ProductQuality::Undefined;
}

Product::Product(const double purchasePrice, const double salePrice, const short amountInStock,
                 const string& name, const ProductQuality quality)
{
    _purchasePrice = purchasePrice;
    _salePrice = salePrice;
    _amountInStock = amountInStock;
    _name = name;
    _quality = quality;
}

bool Product::doesProductGenerateProfit()
{
    return calculateProfit() > 0;
}

double Product::calculateProfit()
{
    double purchasePrice = getPurchasePrice(), salePrice = getSalePrice();

    return salePrice - purchasePrice;
}

double Product::getPurchasePrice()
{
    return _purchasePrice;
}

double Product::getSalePrice()
{
    return _salePrice;
}

float Product::calculateDiscountFromSalePrice()
{
    short amountInStock = getAmountInStock();
    ProductQuality quality = getQuality();

    float discount = amountInStock <= 100 ? 0.1 : amountInStock < 200 ? 0.07 : 0.03;

    if (quality == ProductQuality::Second || quality == ProductQuality::Third)
    {
        discount += 0.3;
    }

    return getSalePrice() * discount;
}

short Product::getAmountInStock()
{
    return _amountInStock;
}

string Product::getName()
{
    return _name;
}

ProductQuality Product::getQuality()
{
    return _quality;
}

void Product::setAmountInStock(const short amountInStock)
{
    _amountInStock = amountInStock;
}

void Product::setName(const string& name)
{
    _name = name;
}

void Product::setPurchasePrice(const double purchasePrice)
{
    _purchasePrice = purchasePrice;
}

void Product::setQuality(const ProductQuality quality)
{
    _quality = quality;
}

void Product::setSalePrice(const double salePrice)
{
    _salePrice = salePrice;
}

void Product::updateSalePrice()
{
    float tax;

    double salePrice = getSalePrice();
    salePrice -= calculateDiscountFromSalePrice();
    tax = salePrice * 0.13;
    cout << "El impuesto es: " << tax;
    salePrice += tax;

    setSalePrice(salePrice);
}
#pragma endregion Product class definition