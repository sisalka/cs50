select title from movies join
stars on movies.id=stars.movie_id join
ratings on stars.movie_id=ratings.movie_id join
people on stars.person_id=people.id
where name = "Chadwick Boseman"
order by rating desc
limit 5;

select name from people join stars on people.id = stars.person_id where movie_id = 4154756;