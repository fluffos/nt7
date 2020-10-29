// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("操操[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "ddd[2;37;0m
它是慕容贾的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dupengdcc");
        set("owner_name", "慕容贾");
        set_temp("owner", "dupengdcc");
        set_temp("owner_name", "慕容贾");
        ::setup();
}
