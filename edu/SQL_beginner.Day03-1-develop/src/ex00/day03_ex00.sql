select m.pizza_name as pizza_name, m.price as price,
       pi.name as pizzeria_name, pv.visit_date as visit_date
       from person p
    join person_visits pv on p.id = pv.person_id
    join pizzeria pi on pv.pizzeria_id = pi.id
    join menu m on pi.id = m.pizzeria_id
    where p.name = 'Kate' and m.price between 800 and 1000
order by pizza_name, price,pizzeria_name;