from dataclasses import dataclass, field


@dataclass(order=True)
class Country:
    name: str
    population: int
    area: float = field(repr=False, compare=False)
    coastline: float = 0

    def beach_per_person(self):
        """Meters of coastline per person"""
        return (self.coastline * 1000) / self.population

c = Country("England", 3000, 456.2, 34567)
print(c)
print(c.beach_per_person())

c1 = Country("Germany", 2000, 156.2, 34167)
print(c1)
print(c1.beach_per_person())



