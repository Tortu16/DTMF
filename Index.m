function retval = Index (i, A)
retval = 0;
if (nargin !=2)
usage ("Index: expects index value and array");
endif
retval = A(i);
endfunction 