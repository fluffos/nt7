#include <weapon.h>
#include <ansi.h> 
inherit BLADE;

void create()
{
        set_name(HIY"精灵刀"NOR, ({ "spirit blade", "blade" })); 
        set("long", "精灵的宝物，拥有精灵的力量。\n");
        set("no_get",1);
        set("no_give",1);
        set("no_steal",1);
        set("no_sell",1);
        set("no_put",1);
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("value", 0);
                set("material", "iron");
                set("wield_msg", HIC"$N"+HIC"右手结印，垂目默念咒语。一点光芒在$N"+HIC"掌中逐渐亮起，$n"NOR+HIC"渐渐成形。\n"NOR);
                set("unwield_msg", "$n"+HIC"从$N"+HIC"手中一跃而起，化为一道清风。\n"NOR); 
            set("skill", ([
                "name": "spirit-blade",    // name of the skill
                "exp_required": 1000,    // minimum combat experience required
                "jing_cost":    2,    // jing cost every time study this
                "difficulty":   10,    // the base int to learn this skill
                "max_skill":   160,    // the maximum level you can learn to
            ]) );
        }
        init_blade(120);
        setup();
}

void owner_is_killed()
{
        write(HIY"只觉一阵清风吹过，好象是……\n"NOR);
       destruct(this_object());
}
/*
int query_autoload()
{
        write(HIG"一阵清风拂过身侧，仿佛在呢喃什么咒语。\n"NOR);
       return 1;
}
*/
void init()
{
    add_action("do_back","back"); 
    add_action("do_nopoison","nopoison"); 
    add_action("do_change","change");    add_action("do_summons","summons");
}
 
int do_back(string arg)
{
    string name;
    name=query("name", this_player());
    if( query("jing", this_player())<20 )
                return notify_fail("你的精神无法集中！\n");
    if( !arg ) return notify_fail("你要回哪里? \n");
    {
        if ( arg == "spirit" )
        {
            message_vision(HIG"$N默念咒语，手中"NOR+HIY"精灵刀"NOR+HIG"化为一阵清风，盘旋飞舞。\n"NOR,this_player() );
            this_player()->receive_damage("jing",10);
            tell_room(environment(this_player()),
                 name+"的身影消失在清风中。\n",this_player() );
            tell_room("/d/city/spirit",
                 name+"的身影出现在一阵清风中。\n",this_player() );
            this_player()->move("/d/city/spirit");
         }
     }
     return 1;
}
 
int do_nopoison(string arg)
{     
        object me;
        me = this_player(); 
        if( query("jing", me)<20 )
                return notify_fail("你的精神无法集中！\n");
        if( !arg )
                return notify_fail("你要为谁疗毒？\n");
        if ( arg == "spirit" )
          {        me->receive_damage("jing",10);
                        message_vision(HIC"$N双掌合十，捧着"NOR+HIY"精灵刀"NOR+HIC"，默念咒语。\n"NOR, me);
        me->clear_condition();  
               write("你成功驱除了体内毒素！\n");
        return 1;  
          }
}
 
int do_summons(string arg)
{
  object me = this_player ();
        object ob;
 
        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能召唤精灵！\n");
        if( query("jing", me)<40 )
                return notify_fail("你的精神无法集中！\n");

        message_vision(HIY"$N"+HIY"将精灵刀一挥，喃喃地念了几句咒语。\n"NOR, me);

         me->receive_damage("jing", 30);
        ob = new("/quest/tulong/npc/spirit");
        ob->move(environment(me));
        ob->invocation(me); 
                return 1;
} 

int do_change(string arg)
{     
        object me = this_player();   
        object ob = this_object();
        object obj;
        if( query("jing", me)<20 )
                return notify_fail("你的精神无法集中！\n");
        if( arg == "sword")
        { 
       me->receive_damage("jing",10);
                        message_vision(HIC"$N手中"NOR+HIY"精灵刀"NOR+HIC"轻轻一晃，变出了一把剑。\n"NOR, me); 
        obj=new("quest/tulong/obj/sword");
        obj->move(me);   
        destruct(ob);
        return 1;  
        }
      return 0;
}