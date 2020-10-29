// guest.c 进香客

inherit NPC;

string *first_name = ({ "赵","孙","李","周","吴","郑","王","张","陈","柳","风","刘","林", }); 
string *man_name_words = ({ "青","顺","风","峰","建","明","铭","战","冠", });
string *woman_name_words = ({ "莲","燕","娜","妮","芳","香","仙","芊","芡", });
string *xing = ({ "男性","女性", });

void create()
{
	int age;
	string name,xingbie;
		age = 20 + random(40);
		xingbie = xing[random(sizeof(xing))];
        name = first_name[random(sizeof(first_name))];
        if (xingbie !="男性")
		{
		name += woman_name_words[random(sizeof(woman_name_words))]; 
        } else { name += man_name_words[random(sizeof(man_name_words))]; }
 

	set_name(name, ({ "guest" }));
    set("title", "进香客");
    set("gender", xingbie);
	set("age", age);
	set_skill("unarmed", random(40));
	set_skill("dodge", random(40));
	set("apply/attack", 15);
	set("apply/defense", 15);
	set("apply/damage", 5);
	set("combat_exp", 150+age*10);
	set("shen_type", 1);
		 set("chat_chance", 2);

	 set("chat_msg", ({
	 "进香客低声吟道：一切有为法，如梦幻泡影\n",
	 "进香客闭目合什：南无阿弥陀佛 \n",
	 "进香客朗声说道：有法无法，皆是虚妄\n",
	 "进香客说道：南无救苦救难广大灵感观世音菩萨！\n",
	     (: random_move :)
        }) );
	setup();
	add_money("coin", 10+age/10);
}
	
