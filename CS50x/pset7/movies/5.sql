SELECT title, year
FROM movies
WHERE title REGEXP "^Harry Potter"
ORDER BY year;