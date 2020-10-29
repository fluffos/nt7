// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一道彩虹[1;31m[2;37;0m[2;37;0m", ({"caihong"}));        
        set("gender", "女性");                
        set("long", "一道彩虹[2;37;0m
它是淡淡幽情的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yoq");
        set("owner_name", "淡淡幽情");
        set_temp("owner", "yoq");
        set_temp("owner_name", "淡淡幽情");
        ::setup();
}
