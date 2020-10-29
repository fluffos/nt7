// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zhu"}));        
        set("gender", "女性");                
        set("long", "你中奖了.[2;37;0m
它是落花吹血的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kof");
        set("owner_name", "落花吹血");
        set_temp("owner", "kof");
        set_temp("owner_name", "落花吹血");
        ::setup();
}
