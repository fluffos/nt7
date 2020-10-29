#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(NOR + YEL "童男童女符" NOR, ({"tntn fu", "fu"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "这是一张道符，上面画着两个小娃，一个男一个女，形态十分逼真。\n"
                                      "*在蛇精洞扔出此符（reng fu）可引出蛇精。\n\n" NOR);
                set("unit", "张");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "reng");       
}

int do_use(string arg)
{
        object me, ob;
        
        me = this_player();
        
        if(! objectp(present("tntn fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                 
        ob = environment(me);
        
        if (base_name(ob) != "/d/shenlong/shejingdong")
                return notify_fail("此符只能在蛇精洞使用。\n");

        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                        return notify_fail("蛇精已经出现了，不需要再使用符。\n");
        }

        // 正在清场则不能扔
        ob = environment(me);
        if( query("doing", ob) )
        {
                return notify_fail("这里刚战斗完，正在清场，你还是等下次吧！\n");
        }
        
        // 使用描述
        message_sort(HIY + "\n$N" HIY "扔出童男童女符，猛然间，地动山摇，远处传来嗖~~嗖"
                     "声，似乎是蛇精在朝这边移动，一时间，空气几乎凝固 ……\n" NOR, me);

        me->start_busy(5);
        
        // 召唤出九头蛇精
        remove_call_out("summon_shejing");
        call_out("summon_shejing", 5, me);



        return 1;
}

void summon_shejing(object me)
{
        object ob;
        
        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                {
                        write("蛇精已经出现了，不需要再使用符，你赶紧将符收起。\n");
                        return;                        
                }
        }        

        ob = new("/d/shenlong/npc/shejing");
        
        message_sort(HIR + "\n猛然间，一阵摄人心魄的叫声打破了寂静，只见一只巨大的毒蛇出现在"
                           "蛇精洞内，此蛇已化身人形，修炼成精，有九头，形状甚是可怕。\n" NOR, me);
        
        ob->move("/d/shenlong/shejingdong");
        set("life_time", time(), ob);
        
        // 摧毁符
        destruct(this_object());
        
        return;        
}