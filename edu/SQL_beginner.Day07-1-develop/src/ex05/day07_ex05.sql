SELECT DISTINCT person.name
FROM person
JOIN person_order ON person_order.person_id = person.id
ORDER BY name;