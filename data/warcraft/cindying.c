// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("炮弹[2;37;0m[2;37;0m", ({"ook"}));        
        set("gender", "男性");                
        set("long", "炮弹[2;37;0m
它是火龙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cindying");
        set("owner_name", "火龙");
        set_temp("owner", "cindying");
        set_temp("owner_name", "火龙");
        ::setup();
}
