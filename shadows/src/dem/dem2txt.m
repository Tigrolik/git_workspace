function dem2txt(fn)

dot_ind = regexp(fn, '\.');
img = readdem(fn);
fname = [fn(1:dot_ind(end)) 'txt'];
img2txt(img, fname);
