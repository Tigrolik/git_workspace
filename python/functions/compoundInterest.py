def future_value(present_value, annual_rate, periods_per_year, years):
    return present_value * (1 + annual_rate / periods_per_year) ** (periods_per_year * years)

pv = 1000
ar = 0.02
py = 365
yr = 3
dn = 4
print '$' + str(pv),'at', str(ar * 100) + '% compounded daily for', str(yr), 'years yields $' + str(round(future_value(pv, ar, py, yr), dn))
