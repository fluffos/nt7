// 面具：为隐藏身份所佩带

#include <armor.h>
#include <ansi.h>

inherit MYMASK;
 
void create()
{
        string *sname = ({
                "天煞孤星",
                "无名孤星",
                "夙世孤星",
                "六道孤星",
                "天命孤星",
                "夜影孤星",                
        });

        set_name(HIW "孤星面具" NOR, ({ "guxing mianju", "guxing", "mianju" }) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("material", "tian jing");
                set("unit", "只");
                set("long", HIW "这是一只面具，面具上绘着一颗奇特的星形图案。戴上后便没人知道你的真实身份了。\n" NOR);
                set("value", 1000000);
                /*
                set("armor_prop/mask_name", sname[random(sizeof(sname))]);
                set("armor_prop/mask_id",  ({ "masker guxing", "masker", "guxing"}) );
                set("armor_prop/mask_long", "此人佩带着孤星面具，难以看出其真实身份。\n");
                set("armor_prop/mask_flag", 1);
                */
        }
        setup();
}

void init()
{
        add_action("do_exit", "exit");
        add_action("do_exit", "quit");
        add_action("do_exit", "save");
}

int do_exit()
{
        if (this_player()->query_temp("apply/mask_flag"))
        {
                return notify_fail("请取下面具后再进行该操作。\n");
        }
}

int query_autoload()
{
        return 1;
}

