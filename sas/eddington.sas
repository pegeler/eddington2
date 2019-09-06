%macro Eddington(data, ride_var);

proc sort data=&data out=&data._rsorted;
by descending &ride_var;
run;

data _null_;
set &data._rsorted;

if &ride_var lt _n_ then do;
  E = _n_ - 1;
  put E=;
  stop;
end;

run;

%mend Eddington;