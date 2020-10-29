// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m小灰灰[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "一只小朱雀[2;37;0m
它是云舒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuns");
        set("owner_name", "云舒");
        set_temp("owner", "yuns");
        set_temp("owner_name", "云舒");
        ::setup();
}
