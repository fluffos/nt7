// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m泡泡泡沫[2;37;0m[2;37;0m", ({"pao"}));        
        set("gender", "男性");                
        set("long", "我爱胡莉莉[2;37;0m
它是十尽的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ten");
        set("owner_name", "十尽");
        set_temp("owner", "ten");
        set_temp("owner_name", "十尽");
        ::setup();
}
