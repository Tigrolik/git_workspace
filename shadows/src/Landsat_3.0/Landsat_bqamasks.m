function [cloud_m, snow_m] = Landsat_bqamasks(bqa)

cloud_m = (bqa == 61440) | (bqa == 59424) | (bqa == 57344) | ...
    (bqa == 56320) | (bqa == 53248) | (bqa == 31744) | (bqa == 28672);

snow_m = (bqa == 56320) | (bqa == 39936) | (bqa == 31744) | ...
    (bqa == 28590) | (bqa == 23552);
