-- Create a temporary view
create temporary view rides (
  ride_date Date,
  ride_length Float
) using csv
options (
  path 'rides.csv',
  header true
);

-- Perform the query
select max(row_num) as eddington_number
from (
  select sum_len, row_number() over (order by sum_len desc) as row_num
  from (
    select ride_date, sum(ride_length) as sum_len
    from rides
    group by ride_date
  ) as a
) as b
where b.sum_len >= b.row_num;
