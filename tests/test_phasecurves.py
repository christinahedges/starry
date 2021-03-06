"""Test phase curves."""
from starry import Map
import numpy as np
from scipy.integrate import dblquad
np.random.seed(1234)


def NumericalFlux(map, theta):
    """Compute the flux by numerical integration of the surface integral."""
    # Lower integration limit
    def y1(x):
        return -np.sqrt(1 - x ** 2)

    # Upper integration limit
    def y2(x):
        return np.sqrt(1 - x ** 2)

    # Specific intensity map
    def I(y, x):
        return map(theta=theta, x=x, y=y)

    # Compute the total flux
    flux, _ = dblquad(I, -1, 1, y1, y2, epsabs=1e-2, epsrel=1e-2)
    return flux


def test_phasecurves():
    """Test transit light curve generation."""
    # Let's do the l = 3 Earth
    map = Map(3)
    map.load_image('earth')

    # Compute the starry phase curve about a random axis
    ux = np.random.random()
    uy = np.random.random() * (1 - ux)
    uz = np.sqrt(1 - ux ** 2 - uy ** 2)
    map.axis = [ux, uy, uz]
    theta = np.linspace(0, 360, 25, endpoint=False)
    sF = map.flux(theta=theta)

    # Compute the flux numerically
    nF = [NumericalFlux(map, t) for t in theta]

    # Compute the error
    error = np.max(np.abs((sF - nF) / sF))

    # We're computing the numerical integral at very low precision
    # so that this test doesn't take forever, so let's be lenient here!
    assert error < 1e-4


if __name__ == "__main__":
    test_phasecurves()
