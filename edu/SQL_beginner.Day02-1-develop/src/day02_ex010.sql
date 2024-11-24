select person2.name as person_name1, person1.name as person_name2, person1.address as common_address
from person person1,
     person person2
where person2 != person1
  and person1.address = person2.address and person1.id<person2.id
order by person_name1, person_name2, common_address