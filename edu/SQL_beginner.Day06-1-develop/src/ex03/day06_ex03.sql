create unique index idx_person_discounts_unique on person_discounts using btree (person_id, pizzeria_id);

SET ENABLE_SEQSCAN = off;
explain analyze
SELECT *
FROM person_discounts
WHERE person_id = 4