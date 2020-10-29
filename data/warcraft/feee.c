// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m檬薜闹[2;37;0m[2;37;0m", ({"xxbook"}));        
        set("gender", "男性");                
        set("long", "一只檬薜闹[2;37;0m
它是菲燕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "feee");
        set("owner_name", "菲燕");
        set_temp("owner", "feee");
        set_temp("owner_name", "菲燕");
        ::setup();
}
