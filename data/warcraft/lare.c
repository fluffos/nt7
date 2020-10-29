// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m银色螳螂[2;37;0m[2;37;0m", ({"lares"}));        
        set("gender", "男性");                
        set("long", "我的宠物[2;37;0m
它是里缘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lare");
        set("owner_name", "里缘");
        set_temp("owner", "lare");
        set_temp("owner_name", "里缘");
        ::setup();
}
