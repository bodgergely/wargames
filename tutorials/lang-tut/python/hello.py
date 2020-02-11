class Celsius(object):
    def __init__(self, value=0.0):
        self.value = float(value)
    def __get__(self, instance, owner):
        return instance.temp if instance.temp else self.value
    def __set__(self, instance, value):
        instance.temp = float(value)


class Temperature(object):
    celsius = Celsius()
    def __init__(self):
        self.temp = None


temp = Temperature()
print(temp.celsius)
temp.celsius = 9

temp2 = Temperature()
print(temp2.celsius)
temp2.celsius = 23

print(temp.celsius)
print(temp2.celsius)

def function(name):
    return jozska
