// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马车[2;37;0m[2;37;0m", ({"ttttt"}));        
        set("gender", "男性");                
        set("long", "小马车[2;37;0m
它是田雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tyj");
        set("owner_name", "田雨");
        set_temp("owner", "tyj");
        set_temp("owner_name", "田雨");
        ::setup();
}
