CREATE INDEX idx_person_name ON person (UPPER(person.name));

SET enable_seqscan TO OFF;

EXPLAIN ANALYZE SELECT *
FROM person
WHERE UPPER(name) = 'ANNA'