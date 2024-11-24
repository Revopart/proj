SELECT DISTINCT  pizzeria.name
FROM person_visits
JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
JOIN person p ON p.id = person_visits.person_id
LEFT JOIN person_order po ON p.id = po.person_id
WHERE p.name = 'Andrey' and person_visits.visit_date != po.order_date