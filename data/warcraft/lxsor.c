// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m玄[1;32m丶[1;33m武[2;37;0m[2;37;0m", ({"asa"}));        
        set("gender", "女性");                
        set("long", "一只表情呆萌的小龟[2;37;0m
它是魔术师的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lxsor");
        set("owner_name", "魔术师");
        set_temp("owner", "lxsor");
        set_temp("owner_name", "魔术师");
        ::setup();
}
