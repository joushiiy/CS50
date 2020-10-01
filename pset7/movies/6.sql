--In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
--Your query should output a table with a single column and a single row (plus optional header) containing the average rating.

SELECT AVG(rating)
FROM ratings
LEFT JOIN movies ON ratings.movie_id = movies.id
WHERE year == 2012;
