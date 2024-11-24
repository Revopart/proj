WITH count_visits AS
(SELECT pizzeria.name,
COUNT(pizzeria_id) AS total_count_demo
FROM person_visits
JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
GROUP BY pizzeria.name
ORDER BY total_count_demo DESC),
	
count_order AS
(SELECT pizzeria.name,
COUNT(pizzeria_id) AS total_count_demo
FROM pizzeria
JOIN menu ON pizzeria.id = menu.pizzeria_id
JOIN person_order ON person_order.menu_id = menu.id
GROUP BY pizzeria.name
ORDER BY total_count_demo DESC),

table_visits_order AS
(SELECT *
FROM count_visits
UNION ALL
SELECT *
FROM count_order)

SELECT name, SUM(total_count_demo) AS total_count
FROM table_visits_order
GROUP BY name
ORDER BY total_count DESC, name ASC;