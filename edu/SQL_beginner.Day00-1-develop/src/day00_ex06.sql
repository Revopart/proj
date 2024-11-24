SELECT 
    (SELECT name
    FROM person
    WHERE person.id = person_order.person_id) AS NAME,
    (SELECT name = 'Denis' 
    FROM person 
    WHERE person_order.person_id  = person.id) AS check_name
FROM person_order
WHERE person_order.order_date = '2022-01-07' vAND  (menu_id = '13' OR menu_id = '14' OR menu_id = '18');