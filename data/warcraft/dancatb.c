// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m大鹏[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "大鹏[2;37;0m
它是弹弹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dancatb");
        set("owner_name", "弹弹");
        set_temp("owner", "dancatb");
        set_temp("owner_name", "弹弹");
        ::setup();
}
