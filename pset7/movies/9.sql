select name from (select distinct people.id, name from people join
stars on people.id=stars.person_id join
movies on stars.movie_id=movies.id
where year = 2004
order by birth desc);