// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "小鸟[2;37;0m
它是无语的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jjs");
        set("owner_name", "无语");
        set_temp("owner", "jjs");
        set_temp("owner_name", "无语");
        ::setup();
}
