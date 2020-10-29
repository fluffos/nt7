// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "一只黑白相间的老虎[2;37;0m
它是张三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wdgold");
        set("owner_name", "张三");
        set_temp("owner", "wdgold");
        set_temp("owner_name", "张三");
        ::setup();
}
