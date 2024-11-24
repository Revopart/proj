SELECT person.address,
	pizzeria.name,
	COUNT(menu.pizzeria_id) AS count_of_orders
FROM pizzeria
JOIN menu ON menu.pizzeria_id = pizzeria.id
JOIN person_order ON person_order.menu_id = menu.id
JOIN person ON person_order.person_id = person.id
GROUP BY person.address, pizzeria.name
ORDER BY person.address, pizzeria.name;