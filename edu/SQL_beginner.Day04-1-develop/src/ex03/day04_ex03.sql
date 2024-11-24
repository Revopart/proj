SELECT generated_date AS missing_date
FROM v_generated_dates
WHERE v_generated_dates.generated_date NOT IN (SELECT person_visits.visit_date FROM person_visits);