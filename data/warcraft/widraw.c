// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一只朱雀[2;37;0m[2;37;0m", ({"filter"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是陈宏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "widraw");
        set("owner_name", "陈宏");
        set_temp("owner", "widraw");
        set_temp("owner_name", "陈宏");
        ::setup();
}
