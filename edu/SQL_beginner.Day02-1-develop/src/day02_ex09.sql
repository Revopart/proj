SELECT DISTINCT person.name
FROM person
JOIN person_order po1 ON person.id = po1.person_id
JOIN menu m1 ON po1.menu_id = m1.id AND m1.pizza_name = 'pepperoni pizza'
JOIN person_order po2 ON person.id = po2.person_id
JOIN menu m2 ON po2.menu_id = m2.id AND m2.pizza_name = 'cheese pizza'
WHERE person.gender = 'female'
ORDER BY 1;