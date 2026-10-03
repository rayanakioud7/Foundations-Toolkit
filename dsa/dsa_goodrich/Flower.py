class Flower:
    def __init__(self, name_flower, petal_nbr, price):
        self._name_flower = name_flower
        self._petal_nbr = petal_nbr
        self._price = price

    def nameSetter(self, name_flower):
        self._name_flower = name_flower

    def petalSetter(self, petal_nbr):
        self._petal_nbr = petal_nbr

    def priceSetter(self, price):
        self._price = price

    def name_getter(self):
        return self._name_flower

    def petal_getter(self):
        return self._petal_nbr

    def get_price(self):
        return self._price
    
        
if __name__ == '__main__':
    setosa = Flower("setosa", 4 , 35.8)

    print(f"setosa's number of petal is {setosa.petal_getter()}")