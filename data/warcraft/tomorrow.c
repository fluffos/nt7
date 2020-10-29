// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红毯[2;37;0m[2;37;0m", ({"hongtan"}));        
        set("gender", "女性");                
        set("long", "一条红色毯子，不过会飞哦......[2;37;0m
它是明玉婉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tomorrow");
        set("owner_name", "明玉婉");
        set_temp("owner", "tomorrow");
        set_temp("owner_name", "明玉婉");
        ::setup();
}
