
#include <ansi.h>

inherit ITEM;

void setup()
{

        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_rideto", 1);   // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_obsend", 1);
        set("no_paimai", 1);
        set("skybook14", 1);

        ::setup();
        set_heart_beat(60);

}

void create()
{
        set_name(HIG "华山之颠" NOR, ({ "huashan zhidian" }));
        set_weight(200000);
        set_max_encumbrance(2000000000);

        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                set("long",
                "这里是华山之颠，平时似乎很少有人到这里来，四周云雾深锁，山风呼呼地在\n"
                "耳边吹着，似乎成为这空旷的山谷中唯一的旋律。\n");
                set("unit", "处");
                set("material", "air");
                set("no_rideto", 1);
                set("no_flyto", 1); 
                set("exits", ([ "out" : "/d/city/wumiao" ]));
             
                set("no_get", "!@#$!@#%%^@!^\n");
        }
        setup();
}

void heart_beat()
{
        // 1小时后清除该副本
        if (time() - query("create_time") > 1 * 3600)
                destruct(this_object());
}

int valid_leave(object me, string arg)
{
        return 1;
}
