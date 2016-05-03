function is_lic = check_lic(toolbox_name)

% function check_lic_dct() checks for license for a toolbox toolbox_name
% e.g., is_lic = check_lis('distrib_computing_toolbox')

S = license('inuse');
is_lic = false;
for j = 1:numel(S)
    if strcmpi(S(j).feature, toolbox_name)
        is_lic = true;
        break;
    end
end
