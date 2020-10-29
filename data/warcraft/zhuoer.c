// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小应声虫[2;37;0m[2;37;0m", ({"answerbug"}));        
        set("gender", "男性");                
        set("long", "千金一应，一应千金！！！[2;37;0m
它是卓大航的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zhuoer");
        set("owner_name", "卓大航");
        set_temp("owner", "zhuoer");
        set_temp("owner_name", "卓大航");
        ::setup();
}
