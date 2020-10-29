// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m骑马舞[2;37;0m[2;37;0m", ({"greenpet"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是绿叶的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "greenleaf");
        set("owner_name", "绿叶");
        set_temp("owner", "greenleaf");
        set_temp("owner_name", "绿叶");
        ::setup();
}
