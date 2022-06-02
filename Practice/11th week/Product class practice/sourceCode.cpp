#include <iostream>
#include "Product.h"

using namespace std;

Product bagOfRice(1500, 2000, 20, "Bolsa de arroz Tio Pelon 99% 1.8 kg", ProductQuality::First);
Product bottleOfWater(325, 650, 50, "Botella de agua San Angel 800 ml", ProductQuality::Undefined);

Product products[] = { bagOfRice, bottleOfWater };

int main()
{
    for (Product product : products)
    {
        string qualityAsString;

        product.updateSalePrice();

        cout << "Product:" << "\n* Name: " << product.getName() << "\n* Purchase price: " << product.getPurchasePrice()
             << "\n* Sale price: " << product.getSalePrice() << "\n* Amount in stock: " << product.getAmountInStock();

        switch (product.getQuality())
        {
            case ProductQuality::First:
                qualityAsString = "Primera";
                break;
            case ProductQuality::Second:
                qualityAsString = "Segunda";
                break;
            case ProductQuality::Third:
                qualityAsString = "Tercera";
                break;
            case ProductQuality::Undefined:
                qualityAsString = "Sin definir";
                break;
        }
             
        cout << "\n* Quality: " << qualityAsString << "\n* Discount: " << product.calculateDiscountFromSalePrice() << "\n\n";
    }

    return 0;
}