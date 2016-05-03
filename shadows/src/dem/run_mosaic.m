% simple mosaicking test

% close all; clear all

format long G

% set directory where DEM files are stored (parameter fs represent slash or
% backslash, depending on OS)
fs = filesep;
dirpath = ['..' fs '..' fs 'images' fs 'DEM' fs];

fn1 = [dirpath 'HGT' fs 'N28E084_SM_56.60_48.49.png'];
I1 = imread(fn1);
fn2 = [dirpath 'HGT' fs 'N28E085_SM_56.60_48.49.png'];
I2 = imread(fn2);
fn3 = [dirpath 'HGT' fs 'N28E086_SM_56.60_48.49.png'];
I3 = imread(fn3);
fn4 = [dirpath 'HGT' fs 'N27E084_SM_56.60_48.49.png'];
I4 = imread(fn4);
fn5 = [dirpath 'HGT' fs 'N27E085_SM_56.60_48.49.png'];
I5 = imread(fn5);
fn6 = [dirpath 'HGT' fs 'N27E086_SM_56.60_48.49.png'];
I6 = imread(fn6);
fn7 = [dirpath 'HGT' fs 'N26E084_SM_56.60_48.49.png'];
I7 = imread(fn7);
fn8 = [dirpath 'HGT' fs 'N26E085_SM_56.60_48.49.png'];
I8 = imread(fn8);
fn9 = [dirpath 'HGT' fs 'N26E086_SM_56.60_48.49.png'];
I9 = imread(fn9);


[s1, s2] = size(I1);
h = s1 * 3;
w = s2 * 3;

I = ones(h, w);

I(1:s1, 1:s2) = I1;
I(1:s1, s2+1:2*s2) = I2;
I(1:s1, 2*s2+1:w) = I3;

I(s1+1:2*s1, 1:s2) = I4;
I(s1+1:2*s1, s2+1:2*s2) = I5;
I(s1+1:2*s1, 2*s2+1:w) = I6;

I(2*s1+1:h, 1:s2) = I7;
I(2*s1+1:h, s2+1:2*s2) = I8;
I(2*s1+1:h, 2*s2+1:w) = I9;

figure(); imshow(I); zoom on
