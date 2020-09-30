SELECT name
FROM people
LEFT JOIN stars ON people.id = stars.person_id
LEFT JOIN movies ON movies.id = stars.movie_id
WHERE title == "Toy Story";