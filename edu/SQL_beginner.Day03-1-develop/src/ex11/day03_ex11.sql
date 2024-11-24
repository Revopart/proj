UPDATE menu
SET price = CAST(800*0.9 AS int)
WHERE pizza_name = 'greek pizza';