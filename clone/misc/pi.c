// pi.c 绊人摔跤的香蕉皮
// By Alf, Last Update 2002.0915

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIY"香蕉皮"NOR,({"xiangjiao pi","pi"}));
    set_weight(200);
    /*if(clonep())
        set_default_object(__FILE__);
    else*/
    {
        set("unit","块");
        set("long","一块香蕉皮。\n");
        set("no_get","一块香蕉皮，都给人踩烂了，你也不嫌恶心？\n");
        set("value",1);
        set("env/invisible",1);
        set("pi_gone",10+random(10));
    }
    setup();
}
 

void init()
{
    int chance,age;
    object me,ob;
    string msg;
    me = this_player();
    ob = this_object();

    age=60-query("age", me);
    if (age < 0) age = 0;
    chance = (me->query_dex() + age)/2;
    
    if(interactive(me) && living(me) && random(chance) == 1) 
    {
        msg = HIY""+me->name()+"不小心踩在香蕉皮上，“咕咚”一声摔了个大马趴";
        me->start_busy(2);
        
        if( query("pi_gone", ob) <= 0 )
        {
            msg += "，香蕉皮却不知飞哪去了。\n";
            tell_room(environment(me),msg);
            destruct(ob);
        }
        else
        {
            set("long", "一块香蕉皮，不知道是谁丢的。\n", ob);
            set("env/invisible", 0, ob);
            addn("pi_gone", -1, ob);
            msg += "。\n"+me->name()+"站起身来，拍了拍屁股，一脸的杀气：“奶奶的到底是谁干的？”\n"NOR;
            tell_room(environment(me),msg);
        }
    }
}