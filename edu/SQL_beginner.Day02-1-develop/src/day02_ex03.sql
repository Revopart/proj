SELECT COALESCE(f.name, '-') AS person_name, f.visit_date, COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM (
    SELECT person.name, pizzeria_id, visit_date
    FROM person
    LEFT JOIN (SELECT visit_date, pizzeria_id, person_id
    FROM person_visits
    WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS PV ON person.id = PV.person_id
) AS f
FULL JOIN pizzeria ON pizzeria.id = f.pizzeria_id
ORDER BY person_name,f.visit_date,pizzeria_name;