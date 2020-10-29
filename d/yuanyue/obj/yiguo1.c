// This program is a part of NITAN MudLIB

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("异果", ({ "yiguo"}) );
        set_weight(50);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("prep", "on");
                set("unit", "个");
                set("long", "一种你从未见过的奇异果子。\n");
                set("value", 1);
                set("food_remaining", 1);
                set("food_supply", 16);
        }
        setup();
}  
void init()
{
        add_action("do_eat","eat");
}

int do_eat(string arg)
{       
        mapping my; 
        object me = this_player();

        my = me->query_entire_dbase(); 

        if(arg=="yiguo"||arg=="异果") {
                message_vision("$N感到快美异常，仿佛吃了什么灵丹妙药！！\n", me);
                set("food", me->max_food_capacity(), me);
                set("water", me->max_water_capacity(), me);
                my["jing"]     = my["max_jing"];
                my["qi"]       = my["max_qi"];
                my["eff_jing"] = my["max_jing"];
                my["eff_qi"]   = my["max_qi"];
                my["neili"]    = my["max_neili"];
                my["jingli"]   = my["max_jingli"];

                destruct(this_object());  
                return 1; 
        }        
        return 0;
}
         
           