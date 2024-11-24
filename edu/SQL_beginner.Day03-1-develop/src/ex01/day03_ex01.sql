SELECT id 
FROM menu
AS menu_id
WHERE menu_id.id NOT IN (SELECT menu_id FROM person_order)
ORDER BY 1