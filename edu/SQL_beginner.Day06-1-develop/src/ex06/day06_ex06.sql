CREATE SEQUENCE seq_person_discounts;
SELECT SETVAL('seq_person_discounts', (SELECT COUNT(*) FROM person_discounts));
ALTER TABLE person_discounts
    ALTER COLUMN id SET DEFAULT NEXTVAL('seq_person_discounts');