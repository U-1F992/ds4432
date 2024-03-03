import typing


e12 = sum(
    [
        [
            r_base * (10**i)
            for r_base in [1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2]
        ]
        for i in range(10)
    ],
    typing.cast(list[float], []),
)

r_pot_r_fs = [
    (r_pot, (0.997 / (16 * i_fs)) * 127)
    for (r_pot, i_fs) in [
        (r_pot, i_fs)
        for (r_pot, i_fs) in [(r, 3.3 / r) for r in e12]
        if 0.00005 <= i_fs <= 0.0002
    ]
]

print(r_pot_r_fs)

# (47000.0, 112710.09469696971)
