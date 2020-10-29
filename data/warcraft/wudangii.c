// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞鸟[2;37;0m[2;37;0m", ({"flybird"}));        
        set("gender", "女性");                
        set("long", "飞鸟[2;37;0m
它是武当三侠的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wudangii");
        set("owner_name", "武当三侠");
        set_temp("owner", "wudangii");
        set_temp("owner_name", "武当三侠");
        ::setup();
}
