from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        'filter',  # назва модуля
        ['filter.cpp'],  # вихідний файл
        include_dirs=[pybind11.get_include()],
        language='c++',
    ),
]

setup(
    name='filter',
    version='0.1',
    ext_modules=ext_modules,
)