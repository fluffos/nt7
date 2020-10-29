// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤焰[2;37;0m[2;37;0m", ({"chiyn"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是沈不醒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "buxing");
        set("owner_name", "沈不醒");
        set_temp("owner", "buxing");
        set_temp("owner_name", "沈不醒");
        ::setup();
}
