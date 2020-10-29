// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "男性");                
        set("long", "不死的化身[2;37;0m
它是啤酒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "justlosea");
        set("owner_name", "啤酒");
        set_temp("owner", "justlosea");
        set_temp("owner_name", "啤酒");
        ::setup();
}
