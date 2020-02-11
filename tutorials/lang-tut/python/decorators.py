import functools

def split_string(function):
    @functools.wraps(function)
    def wrapper():
        func = function()
        splitted_string = func.split()
        return splitted_string

    return wrapper

def uppercase_decorator(function):
    @functools.wraps(function)
    def wrapper():
        func = function()
        make_uppercase = func.upper()
        return make_uppercase

    return wrapper

@split_string
@uppercase_decorator
def say_hi():
    "Mondd hogy hello"
    return 'hello there'

# print(say_hi())


def decorator_with_arguments(function):
    def wrapper_accepting_arguments(arg1, arg2):
        print("My arguments are: {0}, {1}".format(arg1,arg2))
        function(arg1, arg2)
    return wrapper_accepting_arguments


@decorator_with_arguments
def cities(city_one, city_two):
    print("Cities I love are {0} and {1}".format(city_one, city_two))

# cities("Nairobi", "Accra")

def a_decorator_passing_arbitrary_arguments(function_to_decorate):
    def a_wrapper_accepting_arbitrary_arguments(*args,**kwargs):
        print('The positional arguments are', args)
        print('The keyword arguments are', kwargs)
        function_to_decorate(*args, **kwargs)
    return a_wrapper_accepting_arbitrary_arguments

@a_decorator_passing_arbitrary_arguments
def function_blabla(*args, **kwargs):
    print("args: {}, kwargs: {}".format(args, kwargs))

# function_blabla("geri", 8, game='tennis')

def func(*args, **kwargs):
    def func2(*args, **kwargs):
        print("args:{}, kwargs:{}".format(args, kwargs))
    func2(*args, **kwargs)

# func("geri", 5, game="foci", puska="ak")

def decorator_maker_with_arguments(decorator_arg1, decorator_arg2, decorator_arg3):
    "This is the decorator_maker_with_arguments function"
    print("first lev")
    def decorator(func):
        "This is the decorator function"
        print("second lev ", func.__doc__)
        @functools.wraps(func)
        def wrapper(function_arg1, function_arg2, function_arg3) :
            "This is the wrapper function"
            print("The wrapper can access all the variables\n"
                  "\t- from the decorator maker: {0} {1} {2}\n"
                  "\t- from the function call: {3} {4} {5}\n"
                  "and pass them to the decorated function"
                  .format(decorator_arg1, decorator_arg2,decorator_arg3,
                          function_arg1, function_arg2,function_arg3))
            return func(function_arg1, function_arg2,function_arg3)

        print("returning created wrapper:", wrapper.__name__)
        return wrapper
    print("returning created decorator:", decorator.__name__)
    return decorator

pandas = "Pandas"
@decorator_maker_with_arguments(pandas, "Numpy", "Scikit-learn")
def decorated_function_with_arguments(function_arg1, function_arg2,function_arg3):
    "This is the decorated_function_with_arguments function"
    print("This is the decorated function and it only knows about its arguments: {0}"
           " {1}" " {2}".format(function_arg1, function_arg2,function_arg3))

print("Firing function...:", decorated_function_with_arguments.__doc__, ". name:", decorated_function_with_arguments.__name__)
decorated_function_with_arguments(pandas, "Science", "Tools")



