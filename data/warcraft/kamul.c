// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("毛头[2;37;0m[2;37;0m", ({"help_nick"}));        
        set("gender", "女性");                
        set("long", "长得很难看[2;37;0m
它是西门捶血的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kamul");
        set("owner_name", "西门捶血");
        set_temp("owner", "kamul");
        set_temp("owner_name", "西门捶血");
        ::setup();
}
