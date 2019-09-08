create schema eddington2;
use eddington2;

create table rides (
  i int,
  ride decimal(5,2)
);

set @row_num := 0;

load data local infile '../mock-data/rides.dat'
into table rides (ride)
set i=@row_num := @row_num + 1;
