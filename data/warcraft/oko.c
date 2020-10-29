// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("穆庆龙[2;37;0m[2;37;0m", ({"yyoo"}));        
        set("gender", "男性");                
        set("long", "好看的[2;37;0m
它是慕容茜茜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "oko");
        set("owner_name", "慕容茜茜");
        set_temp("owner", "oko");
        set_temp("owner_name", "慕容茜茜");
        ::setup();
}
