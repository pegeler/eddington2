use eddington2;

set @row_num := 0;

select max(row_num) as E
from (
  select (@row_num := @row_num + 1) as row_num, ride
  from rides
  order by ride desc
) as a
where ride >= row_num;

