SELECT pizzeria.name
FROM pizzeria
LEFT JOIN person_visits po ON pizzeria.id = po.pizzeria_id
LEFT JOIN person ON po.person_id = person.id
WHERE po.pizzeria_id IS NOT NULL
GROUP BY pizzeria.name
HAVING COUNT(CASE WHEN person.gender = 'female' THEN 1 END) !=
       COUNT(CASE WHEN person.gender = 'male' THEN 1 END)
ORDER BY 1;