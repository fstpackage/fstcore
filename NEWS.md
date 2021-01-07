
# fstcore 0.9.7 (in development)

## Library updates

## Enhancements

## Bugs


# fstcore 0.9.6 (2021-01-05)

With version 0.9.6, the license of `fstcore` changes from AGPL version 3 to MPL version 2. This allows for less
restrictive use of the `fstcore` package. In particular, closed-source (commercial) solutions can now use `fstcore`
(call it's API), as was impossible under AGPL (under AGPL, products can only use `fstcore` if they make the products
source code available under AGPL or more restrictive license).

## Library updates

* `ZSTD` has been updated to version 1.4.5
* `fstlib` has been updated to version 0.1.6

## Enhancements

* Numeric values can now be used to select a row range, including values larger than 2^31 to select a subset from
long vector columns (thanks @dipterix for reporting)
* The random seed is not initialized anymore when `fstcore` is loaded (see [fst#251](https://github.com/fstpackage/fst/issues/251), thanks @mlell for investigating and @riccardoporreca for providing the solution)


# fstcore 0.9.4 (2020-05-04)

R package`fstcore`contains the R bindings to the C++ fstlib library needed to interface with _fst_ files as well as
the LZ4 and ZSTD sources. It was developed as a package separate from the fst package to facilitate independent
updates to the fstlib, LZ4 and ZSTD libraries.
