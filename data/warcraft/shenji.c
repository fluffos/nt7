// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m南方朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "南方朱雀[2;37;0m
它是梦神机的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shenji");
        set("owner_name", "梦神机");
        set_temp("owner", "shenji");
        set_temp("owner_name", "梦神机");
        ::setup();
}
