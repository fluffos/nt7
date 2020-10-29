// tu.c BY YUCHANG

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
void create()
{
        set_name(HIB"藏宝图"NOR, ({"bao tu","baotu"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_sell", 1);
//        set("no_get", 1);
        set("no_drop","哇？藏宝图都想丢掉,小心遭天谴。\n\n");
        set("long",@LONG
此乃当年雄霸留下的宝藏图,快看看(kan)吧！
LONG );
        /*if( clonep() )
                        set_default_object(__FILE__);
        else*/
       {
                set("unit", "本");
                set("material", "unknow");
        }
}

void init()
{
        add_action( "kan_tu", "kan tu" );
}

int query_autoload()
{
        return 1;
}
//介绍
int kan_tu()
{
        object me;
        me=this_player();
        tell_object(me,
    "传说中的绝世好剑就在五当山上！\n");
        return 1;
}



