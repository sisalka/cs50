select title from movies join
stars on movies.id=stars.movie_id join
people on stars.person_id=people.id
where name = "Johnny Depp" OR name = "Helena Bonham Carter"
group by movies.id
having count(movies.id)>1;