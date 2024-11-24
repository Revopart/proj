SELECT menu.pizza_name AS pizza_name, menu.price, pizzeria.name 
FROM menu
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE menu.id NOT IN (SELECT menu_id from person_order)
ORDER BY 1,2;