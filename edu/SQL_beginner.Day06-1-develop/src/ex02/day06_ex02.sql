SELECT
	pp.name, 
    menu.pizza_name, 
    menu.price, 
    round(menu.price * (1 -  discount/100), 2) as discount_price, 
    pz.name as pizzeria_name
from 
	person_order po
    join person pp on po.person_id = pp.id
    join menu on po.menu_id = menu.id
    join pizzeria pz on menu.pizzeria_id = pz.id
    join person_discounts pd on po.person_id = pd.person_id and menu.pizzeria_id = pd.pizzeria_id
order by 1,2