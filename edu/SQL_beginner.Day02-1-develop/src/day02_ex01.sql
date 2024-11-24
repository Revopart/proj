SELECT date::date as missing_date
FROM (SELECT GENERATE_SERIES('2022-01-01'::timestamp, '2022-01-10', '1 day') AS date) AS new_table
LEFT JOIN (SELECT visit_date FROM person_visits WHERE (person_id = 1 OR person_id = 2)) ON visit_date = date::date
WHERE visit_date IS NULL
ORDER BY visit_date ASC;