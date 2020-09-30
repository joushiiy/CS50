SELECT title, rating
FROM ratings
LEFT JOIN movies ON ratings.movie_id = movies.id
WHERE EXISTS
(SELECT rating FROM ratings WHERE year = 2010)
ORDER BY  rating DESC, title ASC