import starry
from starry import Map, utils, elliptic
import numpy as np

assert starry.__version__ == '0.0.1'

# Check elliptic integrals
assert np.allclose(elliptic.K(0.5), 1.854074677301372)
assert np.allclose(elliptic.E(0.5), 1.350643881047675)
assert np.allclose(elliptic.PI(0.25, 0.5), 2.167619360766556)

# Check factorials
assert np.allclose(utils.factorial(5), 120.)
assert np.allclose(utils.half_factorial(-1), np.sqrt(np.pi))

# Check square roots
assert np.allclose(utils.sqrt_int(25), 5.)
assert np.allclose(utils.invsqrt_int(25), 0.2)

# Check the Map class
m = Map([0, 0, 1, 0])
assert np.allclose(m.y, np.array([0, 0, 1, 0]))

# Rotations
m.rotate([1, 0, 0], -np.pi / 2)
assert np.allclose(m.y, np.array([0, 1, 0, 0]))
m.rotate([0, 0, 1], -np.pi / 2)
assert np.allclose(m.y, np.array([0, 0, 0, 1]))
m.rotate([0, 1, 0], -np.pi / 2)
assert np.allclose(m.y, np.array([0, 0, 1, 0]))

# Evaluation
