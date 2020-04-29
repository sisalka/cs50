select distinct name from people join
stars on people.id = stars.person_id
where movie_id IN (select movie_id from stars join
people on people.id=stars.person_id
where name = "Kevin Bacon" AND birth = 1958)
AND name <> "Kevin Bacon";

