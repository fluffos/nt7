// tea.c 香茶

inherit ITEM;

void init();
void do_eat();

int decayed = 0;
void create()
{
        set_name("香茶",({"tea", "cha"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一杯香茶，悠悠地冒着热气～～～\n");
                set("unit", "杯");
                set("value", 1000);
        set("remaining", 2);
        set("drink_supply", 35);
                set("can_fulan",1);
    }
        
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}


int do_drink(string arg)
{

        int /*heal,*/ recover, jing, e_jing, m_jing;
        
        recover = 5;
        
    if( !this_object()->id(arg) ) return 0;
    if( this_player()->is_busy() )
        return notify_fail("你上一个动作还没有完成。\n");
    if( query("water", this_player() )
       >= (int)this_player()->max_water_capacity() )
     return notify_fail("你已经喝太多了，再也灌不下一滴水了。\n");

        set("value", 0);
    addn("water", query("drink_supply"), this_player());
    jing=query("jing", this_player());
    e_jing=query("eff_jing", this_player());
    m_jing=query("max_jing", this_player());

// No heal effect for 香茶
/***

    if ( e_jing < m_jing )
        {         
                if ( (e_jing + heal) >= m_jing )
                {
                        set("eff_jing", m_jing, this_player());
                } else
                {        
                        set("eff_jing", e_jing+heal, this_player());
                }        
        } 
***/

        if (jing < e_jing )
        {
        if ( (jing + recover) >= e_jing )
        {
            set("jing", e_jing, this_player());
        } else
        {   
            set("jing", jing+recover, this_player());
        }   
        }

    if( this_player()->is_fighting() ) this_player()->start_busy(2);

    addn("remaining", -1);
        if ( query("remaining") )
        {
                    message_vision("$N端起杯香茶，有滋有味地品了几口。\n"+
                      "一股香气直入心脾，$N觉得精神好多了。\n", this_player());
        } else 
        { 
                    message_vision("$N端起雕花小杯，把剩下的香茶一饮而尽。\n"+
                      "一股香气直入心脾，$N觉得精神好多了。\n", this_player());
                
                destruct(this_object());
        }

        return 1;
}
void decay(int phase) 
{
        string msg;
        object env;
        env = environment();
        decayed = phase;
        set("on_fulan",1);
        set("value",0);
        set("food_remaining",0);
        switch(phase)
        {
                case 1:
                        msg =  name(1) + "开始变质了，发出一股难闻的馊味。\n";
                        set("old_name",name(1));
                        set_name("变质的" + query("old_name"),({ query("id") }));
                        call_out("decay", 120, phase + 1);
                        break;
                case 2:
                        msg = name(1) + "开始腐烂了，上面长出许多绿毛，发出难闻的臭味。\n";
                        set_name("腐烂的" + query("old_name"),({ query("id") }));
                        call_out("decay", 60, phase + 1);
                        break;
                case 3:
                        msg = "一阵风吹过，把" + name(1) + "化成灰吹散了。\n";
                        if( env )
                                all_inventory(this_object())->move(env);
                        tell_room(env, msg);
                        destruct(this_object());
                        return;
        }
        while (env && env->is_character())
                env = environment(env);
        if (env) tell_room(env, msg); 
}