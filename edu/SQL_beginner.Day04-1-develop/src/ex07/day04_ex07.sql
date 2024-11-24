insert into person_visits values ((SELECT max(id)+1 FROM person_visits),
								  (SELECT id FROM person
								  WHERE name = 'Dmitriy'),
								  (SELECT pizzeria_id FROM menu
								  WHERE price < 800 LIMIT 1), 
								  '2022-01-08');

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;