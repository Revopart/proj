INSERT INTO person_order
SELECT
  generate_series((select max(id) + 1 from person_order),
          (select max(id) from person_order) + (select count(*) from person)),
  (generate_series((select min(id) from person),
           (select max(id) from person))),
  (select id from menu where pizza_name = 'greek pizza'),
  '2022-02-25';