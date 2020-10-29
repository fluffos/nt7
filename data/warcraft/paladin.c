// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m店小二[2;37;0m[2;37;0m", ({"xiaoer"}));        
        set("gender", "男性");                
        set("long", "店小二[2;37;0m
它是剑某的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "paladin");
        set("owner_name", "剑某");
        set_temp("owner", "paladin");
        set_temp("owner_name", "剑某");
        ::setup();
}
