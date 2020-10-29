// xiaobao.c 小宝

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "小宝" NOR, ({ "xiao bao", "bao", "xiaobao" }) );
        set_weight(200);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一颗金灿灿的丹药，据说可以养血美颜。\n");
                set("value", 20000);
                set("unit", "颗");
                set("per",5);
                set("time",864000);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        if( query("have_meirong_dan", me) )
        {
                tell_object(me, "你已经服用过类似的药品，药力尚未消失，不适宜继续服用！\n");
                return 1;
        }
        
        log_file("static/using", sprintf("%s(%s) eat 小宝 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
                       "。\n", me);

        message("vision", "你似乎感觉" + me->name() + "的面容渐渐模糊起来，不由吓了一大跳！\n",
                          environment(me), ({ me }));

        tell_object(me, HIY "你周身的皮肤痒痒的似乎要崩裂开来，"
                        "好在一会儿就停了下来，浑身上下轻松很多。\n" NOR);

        set("have_meirong_dan",query("per",  this_object()), me);
        set("meirong_time", time()+query("time", this_object()), me);
        addn_temp("apply/per",query("per",  this_object()), me);
        set_temp("meirong_dan_used", 1, me);
        
        destruct(this_object());
        return 1;
}
int query_autoload() { return 1; } 