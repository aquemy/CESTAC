# CESTAC Method

The CESTAC method stands for Control and Stochastic Estimation of Rounding Errors (from french ; Contrôle et Estimation STochastique des Arrondis de Calculs) and aims to quantify the propagation of error due to floating point arithmetic.

Created by Vignes and La Porte in the middle of the 70's, the principle of CESTAC is to randomly perturbate the result of any floating point operation in order to evaluate the number of significant numbers thanks a Student test.

This approach is based on stochastic arithmetic and leads to better estimations, i.e. less loose, than classic interval-based methods.

## What is in this implementation

This C++14 implementation only contains the core method:

- Basic manipulation of IEEE 754 compliant double precision type (previous, next, increment and decrement, taking into account NaN and denormalized).
- Perturbation function based on the previous functions.
- Stochastic Double type maintaining a sample size of 3 and interfaced with POD equivalent.
- Significant figure calculation using a precomputed Student test [To be improved to handle any sample size by compile-time calculation of "magic constants"].
- Helpers in DEBUG to display binary representation of a Stochastic Double.

## What is **not** in this implementation

CESTAC relies on some hypothesis that should always be controlled. In particular, it assumes the second-order error terms in multiplications and divisions are negligeable, which is not always the case. This implementation does not have any check on this assumption.

No branching instability detection is included (despite it would be easy to implement).

This implementation is **not** made to go on production. For production-ready library, take a look at [CADNA](http://www-pequan.lip6.fr/cadna/index.php) (C and Fortran).

For more information about CESTAC:

- [CADNA Team bibliography](http://www-pequan.lip6.fr/cadna/Bibliography.php).
- Lecture on [Stochastic arithmetic](http://www.lix.polytechnique.fr/Labo/Sylvie.Putot/NSV3/Slides/Graillat.pdf) by  F. Jézéquel and Y. Zhu.
- [Contrôler la propagation des erreurs de calculs numériques](https://zestedesavoir.com/contenus/963/controler-la-propagation-des-erreurs-de-calculs-numeriques/) (french) by myself.

# Installing an using the library

```
mkdir build && cd build
cmake ..
make
```

This will build the library and the example in DEBUG.

To compile the library in RELEASE mode, remove the flat DEBUG in the CMakeLists.txt file at the root of the repository.

Sample output (first using POD and second with Stochastic Double):

```
aquemy@prd-linux:~/cestac/build$ ./example
iteration 0 - 1.0000000000004547
iteration 1 - 1.0000000018630999
iteration 2 - 1.0000076314440776
iteration 3 - 1.0312591580864137
iteration 4 - 129.04063743775941

iteration 0 - 0.999999999999242 (11.6277779884407)
x[0] = 0.99999999999954525264911353588104248046875 - 0 01111111110 1111111111111111111111111111111111111111000000000000
x[1] = 0.999999999998181010596454143524169921875 - 0 01111111110 1111111111111111111111111111111111111100000000000000
x[2] = 1.0000000000000002220446049250313080847263336181640625 - 0 01111111111 0000000000000000000000000000000000000000000000000001

iteration 1 - 0.999999996895743 (8.01532833532439)
x[0] = 0.99999999813690010341815650463104248046875 - 0 01111111110 1111111111111111111111111110111111111111000000000000
x[1] = 0.9999999925485099083743989467620849609375 - 0 01111111110 1111111111111111111111111011111111111110000000000000
x[2] = 1.000000000001818989403545856475830078125 - 0 01111111111 0000000000000000000000000000000000000010000000000000

iteration 2 - 0.999987284651828 (4.40295225454564)
x[0] = 0.99999236855592243955470621585845947265625 - 0 01111111110 1111111111111110111111111110111001100101000000000000
x[1] = 0.99996947794988966240481431668740697205066680908203125 - 0 01111111110 1111111111111011111111111101100110010110000000000001
x[2] = 1.0000000074496713242666601217933930456638336181640625 - 0 01111111111 0000000000000000000000000001111111111111000000000001

iteration 3 non significant result - exit
```

