SELECT person.name,
	COUNT(person_visits.pizzeria_id) AS count_of_visits
FROM person
JOIN person_visits ON person.id = person_visits.person_id
GROUP BY person.name
HAVING COUNT(person_visits.pizzeria_id) > 3;