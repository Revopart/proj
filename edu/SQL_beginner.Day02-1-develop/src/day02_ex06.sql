SELECT menu.pizza_name,
	pizzeria.name
FROM person_order
JOIN person ON person_order.person_id = person.id
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE person.name IN('Anna', 'Denis')
ORDER BY 1, 2;