SELECT pizza_name, pizzeria.name AS pizzeria_name, price
FROM menu
INNER JOIN pizzeria ON pizzeria_id = pizzeria.id
WHERE  pizza_name in ('mushroom pizza', 'pepperoni pizza')
ORDER BY pizza_name, pizzeria_name;