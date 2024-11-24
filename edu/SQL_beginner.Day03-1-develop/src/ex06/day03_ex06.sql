SELECT    
    m1.pizza_name AS pizza_name,    
    p1.name  AS pizzeria_name_1,    
    p2.name  AS pizzeria_name_2,   
    m1.price AS price
FROM menu AS m1
JOIN menu AS m2 
    ON m1.pizza_name = m2.pizza_name AND m1.price = m2.price AND m1.pizzeria_id < m2.pizzeria_id
    JOIN pizzeria AS p1 ON m1.pizzeria_id = p1.id 
    JOIN pizzeria AS p2 ON m2.pizzeria_id = p2.id 
ORDER BY m1.pizza_name;