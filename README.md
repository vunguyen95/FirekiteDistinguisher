# Firekite Distinguisher (LF2-style)

## About this project



Firekite is a synchronous stream cipher that utilized a **LPN**-based Pseudo-Random-Number generator. It was proposed by  Bogos, Korolija, Locher, and Vaudenay recently. It remains one of a few LPN-based symmetric cryptographic construction. Details on the Firekite cipher can be found in the following papers

Bogos, S., Korolija, D., Locher, T. and Vaudenay, S., 2021, June. Towards Efficient LPN-Based Symmetric Encryption. In *International Conference on Applied Cryptography and Network Security* (pp. 208-230). Springer, Cham.

</https://infoscience.epfl.ch/record/287977/files/paper_29.pdf>

This project serves as a simple implementation of the Firekite distinguisher. We provided both a 4-sum and 8-sum distinguisher for a **small set of Firekite parameters**. Specifically, the parameters are: 
$$
n = 256, m = 52, k = 4
$$
The parameters are adjusted in the spirit of Firekite's designers. However, readers can also use their own selections of parameters. We recommend testing different parameters up to `n = 512` (the ratio n/k should be the same) and `m < 120`. 

## Pre-requisites

The project utilized mostly standard C++ library such as: 

* `unordered_map`
* `algorithm`
* `cstdlib`
* ...

We also used the *hash functional* in the `boost library`, specifically, found at:

*  `boost/functional/hash.hpp`

Headers:

* `encodingerror.h` (processing Firekite output)
* `matrix.h` (XOR operations, matrix multiplication, key generator, Firekite, ...)
* `misc.h` (miscellaneous, printing)

## Using the distinguishers

## 4-sum Distinguisher

```
g++ -o 4sumbkw 4sumbkw.cc encodingerror.cc matrix.cc misc.cc

./4sumbkw
```

## 8-sum Distinguisher

```
g++ -o 8sumbkw 8sumbkw.cc encodingerror.cc matrix.cc misc.cc
./8sumbkw
```

## Using different parameters

Firekite parameters can be changed in the driver codes `4sumbkw.cc` or `8sumbkw.cc`. The parameters `c` is named as `cancel` should also be modified correspondingly (as specified in the submission *Attacks on the Firekite cipher* Sect. 4.)



