/**
Compute the linear Ylm model. Default / Spectral specialization.

*/
template <
    typename U=S, 
    typename=IsDefaultOrSpectral<U>, 
    typename=IsEmitted<U>
>
inline void computeLinearModel (
    const Vector<Scalar>& theta, 
    const Vector<Scalar>& xo, 
    const Vector<Scalar>& yo, 
    const Vector<Scalar>& zo, 
    const Vector<Scalar>& ro, 
    RowMatrix<Scalar>& A
) {
    computeLinearModelInternal(theta, xo, yo, zo, ro, A);
}

/**
Compute the linear Ylm model and its gradient. Default / Spectral specialization.

*/
template <
    typename U=S, 
    typename=IsDefaultOrSpectral<U>, 
    typename=IsEmitted<U>
>
inline void computeLinearModel (
    const Vector<Scalar>& theta, 
    const Vector<Scalar>& xo, 
    const Vector<Scalar>& yo, 
    const Vector<Scalar>& zo, 
    const Vector<Scalar>& ro, 
    RowMatrix<Scalar>& A,
    RowMatrix<Scalar>& Dtheta,
    RowMatrix<Scalar>& Dxo,
    RowMatrix<Scalar>& Dyo,
    RowMatrix<Scalar>& Dro
) {
    computeLinearModelInternal(theta, xo, yo, zo, ro, A, Dtheta, Dxo, Dyo, Dro);
}