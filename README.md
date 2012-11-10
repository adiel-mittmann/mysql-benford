# MySQL-Benford

By Adiel Mittmann

## About

MySQL-Benford is a MySQL plugin that provides functions that you can use to test
how close data conform to
[Benford's distribution](http://en.wikipedia.org/wiki/Benford's law).

The functions are:

1. `BENFORD_CHISQ`: conducts a _χ²_ test with a 0.001 significance
level. Returns 1 if the null hypothesis is rejected, that is, the numbers don't
follow the Benford distribution; returns 0 otherwise.

2. `BENFORD_MSTAR`: conducts an _m*_ test with a 0.01 significance level. The
return value has the same meaning as with the previous function. See also
[Morrow's article](http://jmorrow.net/projects/benford/benfordMain.pdf).

3. `BERFORD_MAX`: returns the maximum difference between the observed frequency
and the expected frequency.

## Example

Using data from the [USDA](http://sourceforge.net/projects/usdanutr/), you can
run queries like this:

```mysql
SELECT Tagname, ROUND(BENF_MAX(Nutr_Val), 2) AS Max
FROM NUT_DATA JOIN NUTR_DEF ON NUT_DATA.Nutr_No = NUTR_DEF.Nutr_No
GROUP BY NUT_DATA.Nutr_No HAVING COUNT(*) >= 1000
ORDER BY BENF_MAX(Nutr_Val) DESC LIMIT 10;
```

In order to produce these results:

    +---------+------+
    | Tagname | Max  |
    +---------+------+
    | WATER   | 0.23 |
    | ARG_G   | 0.21 |
    | ALA_G   | 0.21 |
    | MG      | 0.18 |
    | CYS_G   | 0.17 |
    | ASP_G   | 0.16 |
    | GLY_G   | 0.16 |
    | VAL_G   | 0.15 |
    | VITD    | 0.15 |
    | LYS_G   | 0.14 |
    +---------+------+

## Installation

Installing the plugin means building the shared object and copying it to MySQL's
plugin directory. In Linux:

```bash
mkdir build && cd build
cmake .. && make
cp benford.so /usr/lib/mysql/plugin
```

In order to use the plugin, you must first register the functions with MySQL by
issuing the following commands:

```mysql    
CREATE AGGREGATE FUNCTION BENF_CHISQ RETURNS INTEGER SONAME 'benford.so';
CREATE AGGREGATE FUNCTION BENF_MSTAR RETURNS INTEGER SONAME 'benford.so';
CREATE AGGREGATE FUNCTION BENF_MAX   RETURNS REAL    SONAME 'benford.so';
```