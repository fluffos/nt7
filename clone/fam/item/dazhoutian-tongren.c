// 铜人

#include <ansi.h>

inherit ITEM;

#define TONGREN_D        "/adm/daemons/tongrend2"

int is_wmtongren() { return 1; };

void create()
{
        set_name(HIY "大周天铜人" NOR, ({ "dazhoutian tongren" }) );
        set_weight(50);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "这是一个破旧的铜人，上面绘制了一些图案，但是已经无法辩识。\n" HIG
                                "使用指令 kg dazhoutian tongren 鉴定冲穴铜人。\n" NOR);
                set("value", 1);
                set("unit", "个");
                set("skill", ([
                        "name" : "jingluo-xue",
                        "exp_required" : 50000,
                        "jing_cost"  : 20,
                        "difficulty" : 80,
                        "max_skill"  : 120,
                        "min_skill"  : 0,                        
                ]));

        }

        setup();
}

void init()
{
        add_action("do_kg", "kg");        
}

int do_kg(string arg)
{
        object ob, me;
        
        me = this_player();
        
        if (! me)return 0;
        
        if (! arg || arg != "dazhoutian tongren")
                return notify_fail("你要对什么进行开光鉴定。\n");
                
        if (! objectp(ob = present("dazhoutian tongren", me)))
                return notify_fail("你身上没有这样物品。\n");        
                
        TONGREN_D->open_tongren(me, ob);
        
        return 1;                        
}

int query_autoload()
{
         return 1;
}