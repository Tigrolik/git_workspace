function f_new = example(b, varargin)
numel(varargin)
for j = 1:numel(varargin)
    varargin{j}
    if iscell(varargin{j})
        varargin{j}{1}
        (varargin{j}{2})
    end
end
