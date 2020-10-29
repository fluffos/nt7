// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小白[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "小白[2;37;0m
它是玉蝶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dou");
        set("owner_name", "玉蝶");
        set_temp("owner", "dou");
        set_temp("owner_name", "玉蝶");
        ::setup();
}
