#!/usr/bin/env python3
try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

setup(name="eddington",
      version="0.0",
      author="Paul Egeler",
      url="https://github.com/pegeler/eddington2/",
      license="GPL-3",
      package_dir = {"eddington": "src"},
      packages = ["eddington"],
      keywords = [
          "cycling",
          "h-index",
          "Durfee square",
          "algorithms",
          ]
      )
