inherit ITEM;

void init();
void do_eat();

void create()
{
        set_name("巫山云茶",({"tea", "cha", "yuncha"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一杯热茶，夜辰亲手采摘巫山茉莉花叶，龙泉山茶花瓣，紫竹林竹芯，再调和晨露，芳香无比！\n");
                set("unit", "杯");
                set("value", 1000);
        set("remaining", 20);
        set("drink_supply", 25);
        }
        
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}


int do_drink(string arg)
{
        int heal, recover, jing, e_jing, m_jing;
        recover = 5;

        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你上一个动作还没有完成。\n");
        if( query("water", this_player() )
           >= (int)this_player()->max_water_capacity() )
                return notify_fail("你已经喝太多了，再也灌不下一滴水了。\n");

        set("value", 0);
        addn("water", (int)query("drink_supply"), this_player());
        jing=query("jing", this_player());
        e_jing=query("eff_jing", this_player());
        m_jing=query("max_jing", this_player());

//      if ( e_jing < m_jing )
//      {       
//              if ( (e_jing + heal) >= m_jing )
//              {
//                      this_player()->set("eff_jing", m_jing);
//              } else
//              {       
//                      this_player()->set("eff_jing", e_jing+heal);
//              }       
//      } 
//      if (jing < e_jing )
//      {
//              if ( (jing + recover) >= e_jing )
//              {
//                      this_player()->set("jing", e_jing);
//              } else
//              {   
//                      this_player()->set("jing", jing+recover);
//              }
//      }

        if( this_player()->is_fighting() ) this_player()->start_busy(2);
        addn("remaining", -1);
        if ( query("remaining") )
        {
                message_vision("$N端起杯巫山云茶，有滋有味地品了几口。\n"+
                "一股香气直入心脾，$N精神大振。\n", this_player());
        } else 
        { 
                message_vision("$N将巫山云茶一饮而尽，意犹未尽。\n", this_player());
                destruct(this_object());
        }
        return 1;
}