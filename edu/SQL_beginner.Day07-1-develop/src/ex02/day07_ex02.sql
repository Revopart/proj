WITH count_visits AS
(SELECT pizzeria.name,
COUNT(pizzeria_id) AS count,
'visit' AS action_type
FROM person_visits
JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
GROUP BY pizzeria.name
ORDER BY count DESC
LIMIT 3),
	
count_order AS
(SELECT pizzeria.name,
COUNT(pizzeria_id) AS count,
'order' AS action_type
FROM pizzeria
JOIN menu ON pizzeria.id = menu.pizzeria_id
JOIN person_order ON person_order.menu_id = menu.id
GROUP BY pizzeria.name
ORDER BY count DESC
LIMIT 3)

SELECT *
FROM count_visits
UNION
SELECT *
FROM count_order
ORDER BY action_type ASC, count DESC;