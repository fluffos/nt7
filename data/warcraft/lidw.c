// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidva"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星瓦的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidw");
        set("owner_name", "星瓦");
        set_temp("owner", "lidw");
        set_temp("owner_name", "星瓦");
        ::setup();
}
