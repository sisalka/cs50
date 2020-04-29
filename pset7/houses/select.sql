select first, last, birth from students where house = argv[1] group by last order by first

select first, middle, last, birth from students where house = house group by last order by first

