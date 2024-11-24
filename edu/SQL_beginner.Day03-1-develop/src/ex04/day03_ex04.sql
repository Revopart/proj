WITH people AS (
    SELECT DISTINCT pizzeria.name AS pizzeria_name, p.gender
    FROM person_order po
    JOIN person p ON po.person_id = p.id
    JOIN menu m ON po.menu_id = m.id
    JOIN pizzeria ON m.pizzeria_id = pizzeria.id
)

SELECT DISTINCT pizzeria_name
FROM people
WHERE (gender = 'female' AND pizzeria_name NOT IN (
        SELECT pizzeria_name
        FROM people
        where gender = 'male'
    ))
   OR (gender = 'male' AND pizzeria_name NOT IN (
        SELECT pizzeria_name
        FROM people
        WHERE gender = 'female'
    ))
ORDER BY pizzeria_name;