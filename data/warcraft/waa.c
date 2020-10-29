// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坏掉了[2;37;0m[2;37;0m", ({"waw"}));        
        set("gender", "男性");                
        set("long", "就坏掉了[2;37;0m
它是高潮肾寒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "waa");
        set("owner_name", "高潮肾寒");
        set_temp("owner", "waa");
        set_temp("owner_name", "高潮肾寒");
        ::setup();
}
