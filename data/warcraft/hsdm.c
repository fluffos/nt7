// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "女性");                
        set("long", "四大神兽之一的青龙[2;37;0m
它是明玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hsdm");
        set("owner_name", "明玉");
        set_temp("owner", "hsdm");
        set_temp("owner_name", "明玉");
        ::setup();
}
